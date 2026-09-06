#include "DepthFirstIterator.h"
#include "IncompleteTaskIterator.h"
#include "structureVersion.h"
#include "workComponent.h"
#include "workGroup.h"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class TestTask : public WorkComponent {
public:
    TestTask(const std::string& id, bool incomplete)
        : WorkComponent(id, id), incomplete(incomplete) {}

    void setIncomplete(bool value) { incomplete = value; }

    virtual double estimatedCost() const { return 0.0; }
    virtual int priorityScore() const { return 0; }
    virtual std::string summary() const { return getId(); }
    virtual bool isIncompleteWork() const { return incomplete; }
    virtual std::size_t iteratorChildCount() const { return 0; }
    virtual WorkComponent* iteratorChildAt(std::size_t) const { return NULL; }

private:
    bool incomplete;
};

std::vector<std::string> collect(WorkIterator& iterator) {
    std::vector<std::string> ids;
    iterator.first();

    while (!iterator.isDone()) {
        WorkComponent* component = iterator.current();
        assert(component != NULL);
        ids.push_back(component->getId());
        iterator.next();
    }

    return ids;
}

void assertOrder(const std::vector<std::string>& actual,
                 const char* const expected[],
                 std::size_t expectedCount) {
    assert(actual.size() == expectedCount);

    for (std::size_t i = 0; i < expectedCount; ++i) {
        assert(actual[i] == expected[i]);
    }
}

void testDepthFirstOrderAndReset() {
    StructureVersion version;
    WorkGroup root("root", "Root");
    root.setStructureVersion(&version);

    WorkGroup* group = new WorkGroup("group", "Group");
    WorkGroup* nested = new WorkGroup("nested", "Nested");
    assert(root.addChild(new TestTask("leaf-a", true)));
    assert(root.addChild(group));
    assert(group->addChild(new TestTask("leaf-b", true)));
    assert(group->addChild(nested));
    assert(nested->addChild(new TestTask("leaf-c", true)));

    DepthFirstIterator iterator(&root, &version);
    assert(iterator.isDone());
    assert(iterator.isValid());

    const std::vector<std::string> actual = collect(iterator);
    const char* const expected[] = {
        "root", "leaf-a", "group", "leaf-b", "nested", "leaf-c"
    };
    assertOrder(actual, expected, sizeof(expected) / sizeof(expected[0]));

    iterator.first();
    assert(iterator.current() == &root);
    iterator.next();
    assert(iterator.current()->getId() == "leaf-a");
    iterator.first();
    assert(iterator.current() == &root);
}

void testIndependentDepthFirstIterators() {
    StructureVersion version;
    WorkGroup root("root", "Root");
    root.setStructureVersion(&version);
    assert(root.addChild(new TestTask("first", true)));
    assert(root.addChild(new TestTask("second", true)));

    DepthFirstIterator first(&root, &version);
    DepthFirstIterator second(&root, &version);
    first.first();
    second.first();

    first.next();
    assert(first.current()->getId() == "first");
    assert(second.current() == &root);

    first.next();
    assert(first.current()->getId() == "second");
    second.next();
    assert(second.current()->getId() == "first");
}

void testStructuralInvalidation() {
    StructureVersion version;
    WorkGroup root("root", "Root");
    root.setStructureVersion(&version);

    TestTask* currentTask = new TestTask("current", true);
    assert(root.addChild(currentTask));

    DepthFirstIterator first(&root, &version);
    DepthFirstIterator second(&root, &version);
    first.first();
    second.first();
    first.next();
    assert(first.current() == currentTask);

    const unsigned long beforeStateChange = version.current();
    currentTask->setIncomplete(false);
    assert(version.current() == beforeStateChange);
    assert(first.isValid());
    assert(second.isValid());

    assert(root.addChild(new TestTask("added", true)));
    assert(!first.isValid());
    assert(!second.isValid());
    assert(first.current() == NULL);
    assert(second.current() == NULL);
    assert(first.isDone());
    assert(second.isDone());

    first.first();
    first.next();
    assert(first.current() == currentTask);
    assert(root.removeChild("current"));
    assert(!first.isValid());
    assert(first.current() == NULL);

    second.first();
    second.next();
    WorkComponent* detached = root.detachChild("added");
    assert(detached != NULL);
    assert(detached->getStructureVersion() == NULL);
    assert(!second.isValid());
    assert(second.current() == NULL);
    delete detached;

    second.first();
    assert(second.isValid());
    assert(second.current() == &root);
}

void testIncompleteFilteringAndIndependence() {
    StructureVersion version;
    WorkGroup root("root", "Root");
    root.setStructureVersion(&version);

    WorkGroup* group = new WorkGroup("group", "Group");
    WorkGroup* nested = new WorkGroup("nested", "Nested");
    assert(root.addChild(new TestTask("completed-a", false)));
    assert(root.addChild(group));
    assert(group->addChild(new TestTask("incomplete-a", true)));
    assert(group->addChild(nested));
    assert(nested->addChild(new TestTask("completed-b", false)));
    assert(nested->addChild(new TestTask("incomplete-b", true)));

    IncompleteTaskIterator first(&root, &version);
    IncompleteTaskIterator second(&root, &version);
    first.first();
    second.first();

    assert(first.current()->getId() == "incomplete-a");
    assert(second.current()->getId() == "incomplete-a");
    first.next();
    assert(first.current()->getId() == "incomplete-b");
    assert(second.current()->getId() == "incomplete-a");
    first.next();
    assert(first.isDone());

    const std::vector<std::string> actual = collect(second);
    const char* const expected[] = {"incomplete-a", "incomplete-b"};
    assertOrder(actual, expected, sizeof(expected) / sizeof(expected[0]));

    second.first();
    assert(root.addChild(new TestTask("incomplete-c", true)));
    assert(!second.isValid());
    assert(second.current() == NULL);
    assert(second.isDone());
}

void testEmptyAndNullTraversals() {
    StructureVersion version;
    WorkGroup root("root", "Root");
    root.setStructureVersion(&version);
    assert(root.addChild(new TestTask("completed", false)));

    IncompleteTaskIterator noIncomplete(&root, &version);
    noIncomplete.first();
    assert(noIncomplete.isValid());
    assert(noIncomplete.isDone());
    assert(noIncomplete.current() == NULL);

    DepthFirstIterator noRoot(NULL, &version);
    noRoot.first();
    assert(noRoot.isValid());
    assert(noRoot.isDone());
    assert(noRoot.current() == NULL);

    IncompleteTaskIterator noFilteredRoot(NULL, &version);
    noFilteredRoot.first();
    assert(noFilteredRoot.isValid());
    assert(noFilteredRoot.isDone());
    assert(noFilteredRoot.current() == NULL);
}

int main() {
    testDepthFirstOrderAndReset();
    testIndependentDepthFirstIterators();
    testStructuralInvalidation();
    testIncompleteFilteringAndIndependence();
    testEmptyAndNullTraversals();

    std::cout << "All iterator tests passed." << std::endl;
    return 0;
}
