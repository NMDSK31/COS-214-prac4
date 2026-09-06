#include "DepthFirstIterator.h"
#include "IncompleteTaskIterator.h"
#include "ApprovalRequiredDecorator.h"
#include "EventTask.h"
#include "UrgentTaskDecorator.h"
#include "EventPlan.h"
#include "StructureVersion.h"
#include "TaskList.h"
#include "WorkComponent.h"
#include "WorkGroup.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
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

class DestructionTrackedTask : public EventTask {
public:
    explicit DestructionTrackedTask(int* destructionCount)
        : EventTask("tracked", "Tracked task", 10.0, 1),
          destructionCount(destructionCount) {}

    virtual ~DestructionTrackedTask() {
        ++(*destructionCount);
    }

private:
    int* destructionCount;
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

void testCompositeValidationAndOwnership() {
    EventPlan root("plan", "Event plan", "EVT-00");
    StructureVersion* version = root.getStructureVersion();
    assert(version != NULL);
    assert(version->current() == 0);
    assert(root.estimatedCost() == 0.0);
    assert(root.priorityScore() == 0);
    assert(!root.addChild(NULL));
    assert(!root.addChild(&root));
    assert(version->current() == 0);

    int destructionCount = 0;
    DestructionTrackedTask* tracked =
        new DestructionTrackedTask(&destructionCount);
    assert(root.addChild(tracked));
    assert(root.estimatedCost() == 10.0);
    assert(root.priorityScore() == 1);
    assert(version->current() == 1);
    assert(!root.addChild(tracked));

    EventTask* duplicateId =
        new EventTask("tracked", "Duplicate", 40.0, 5);
    assert(!root.addChild(duplicateId));
    delete duplicateId;
    assert(version->current() == 1);

    WorkComponent* detached = root.detachChild("tracked");
    assert(detached == tracked);
    assert(destructionCount == 0);
    assert(detached->getStructureVersion() == NULL);
    assert(version->current() == 2);
    delete detached;
    assert(destructionCount == 1);

    DestructionTrackedTask* removed =
        new DestructionTrackedTask(&destructionCount);
    assert(root.addChild(removed));
    assert(version->current() == 3);
    assert(root.removeChild("tracked"));
    assert(destructionCount == 2);
    assert(version->current() == 4);
    assert(!root.removeChild("missing"));
    assert(version->current() == 4);
}

void testCompleteStateTransitionMatrix() {
    EventTask task("stateful", "Stateful task", 50.0, 3);
    assert(task.getStateName() == "Planned");
    assert(!task.start());
    assert(!task.submitForReview());

    assert(task.markReady());
    assert(task.getStateName() == "Ready");
    assert(!task.markReady());
    assert(task.block("supplier delay"));
    assert(task.getStateName() == "Blocked");
    assert(!task.start());
    assert(task.resolveBlock());
    assert(task.getStateName() == "Ready");

    assert(task.start());
    assert(task.getStateName() == "InProgress");
    assert(task.block("safety check"));
    assert(task.resolveBlock());
    assert(task.start());
    assert(task.submitForReview());
    assert(task.getStateName() == "Review");
    assert(task.rejectReview());
    assert(task.getStateName() == "Ready");

    assert(task.start());
    assert(task.submitForReview());
    assert(task.approveReview());
    assert(task.getStateName() == "Completed");
    assert(!task.isIncompleteWork());
    assert(!task.markReady());
    assert(!task.start());
    assert(!task.block("late change"));
    assert(!task.resolveBlock());
    assert(!task.submitForReview());
    assert(!task.approveReview());
    assert(!task.rejectReview());
}

void testDecoratorRejectsNullTask() {
    bool rejected = false;

    try {
        ApprovalRequiredDecorator invalid(NULL, 5.0);
    } catch (const std::invalid_argument&) {
        rejected = true;
    }

    assert(rejected);
}

void completeTask(EventTask& task) {
    assert(task.markReady());
    assert(task.start());
    assert(task.submitForReview());
    assert(task.approveReview());
    assert(task.getStateName() == "Completed");
    assert(!task.isIncompleteWork());
}

void testFactoriesWithIntegratedTasksAndDecorators() {
    EventPlan root("plan", "Event plan", "EVT-01");
    TaskList* preparation =
        new TaskList("preparation", "Preparation", "PREP", "Hall");
    TaskList* operations =
        new TaskList("operations", "Operations", "OPS", "Stage");
    EventTask* completed = new EventTask("completed", "Completed task", 20.0, 1);
    EventTask* active = new EventTask("active", "Active task", 30.0, 2);
    EventTask* setupSound =
        new EventTask("setup-sound", "Set up sound", 100.0, 4);

    completeTask(*completed);
    assert(setupSound->markReady());
    assert(preparation->addChild(completed));
    assert(preparation->addChild(setupSound));
    assert(operations->addChild(active));
    assert(root.addChild(preparation));
    assert(root.addChild(operations));
    assert(root.estimatedCost() == 150.0);
    assert(root.priorityScore() == 4);

    WorkIterator* stale = root.createDepthFirstIterator();
    stale->first();
    stale->next();
    assert(stale->current() == preparation);

    WorkComponent* detached = preparation->detachChild("setup-sound");
    assert(detached == setupSound);
    assert(setupSound->getStructureVersion() == NULL);
    assert(!stale->isValid());
    assert(stale->current() == NULL);
    delete stale;

    UrgentTaskDecorator* urgent =
        new UrgentTaskDecorator(setupSound, 3, 25.0, "coordinator");
    ApprovalRequiredDecorator* approval =
        new ApprovalRequiredDecorator(urgent, 10.0);
    assert(operations->addChild(approval));
    assert(approval->estimatedCost() == 135.0);
    assert(approval->priorityScore() == 7);
    assert(root.estimatedCost() == 185.0);
    assert(root.priorityScore() == 7);
    assert(approval->getStructureVersion() == root.getStructureVersion());
    assert(urgent->getStructureVersion() == root.getStructureVersion());
    assert(setupSound->getStructureVersion() == root.getStructureVersion());

    WorkIterator* depth = root.createDepthFirstIterator();
    const std::vector<std::string> depthOrder = collect(*depth);
    const char* const expectedDepth[] = {
        "plan", "preparation", "completed", "operations", "active",
        "setup-sound"
    };
    assertOrder(depthOrder,
                expectedDepth,
                sizeof(expectedDepth) / sizeof(expectedDepth[0]));

    depth->first();
    const unsigned long beforeStateChanges =
        root.getStructureVersion()->current();
    assert(active->markReady());
    assert(root.getStructureVersion()->current() == beforeStateChanges);
    assert(depth->isValid());
    delete depth;

    WorkIterator* incomplete = root.createIncompleteTaskIterator();
    const std::vector<std::string> incompleteOrder = collect(*incomplete);
    const char* const expectedIncomplete[] = {"active", "setup-sound"};
    assertOrder(incompleteOrder,
                expectedIncomplete,
                sizeof(expectedIncomplete) / sizeof(expectedIncomplete[0]));

    assert(!approval->start());
    approval->grantApproval();
    assert(approval->start());
    assert(approval->submitForReview());
    assert(approval->approveReview());
    assert(active->start());
    assert(active->submitForReview());
    assert(active->approveReview());
    assert(incomplete->isValid());

    incomplete->first();
    assert(incomplete->isDone());
    assert(incomplete->current() == NULL);
    delete incomplete;
}

void testDecoratorOwnershipChain() {
    int destructionCount = 0;

    {
        EventPlan root("plan", "Event plan", "EVT-02");
        ExecutableTask* chain = new ApprovalRequiredDecorator(
            new UrgentTaskDecorator(
                new DestructionTrackedTask(&destructionCount),
                2,
                5.0,
                "owner"),
            3.0);
        assert(root.addChild(chain));
    }

    assert(destructionCount == 1);
}

int main() {
    testDepthFirstOrderAndReset();
    testIndependentDepthFirstIterators();
    testStructuralInvalidation();
    testIncompleteFilteringAndIndependence();
    testEmptyAndNullTraversals();
    testCompositeValidationAndOwnership();
    testCompleteStateTransitionMatrix();
    testDecoratorRejectsNullTask();
    testFactoriesWithIntegratedTasksAndDecorators();
    testDecoratorOwnershipChain();

    std::cout << "All iterator tests passed." << std::endl;
    return 0;
}
