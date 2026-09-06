#include "IncompleteTaskIterator.h"

#include "DepthFirstIterator.h"
#include "WorkComponent.h"

IncompleteTaskIterator::IncompleteTaskIterator(WorkComponent* root,
                                               StructureVersion* version)
    : traversal(new DepthFirstIterator(root, version)) {}

IncompleteTaskIterator::~IncompleteTaskIterator() {
    delete traversal;
    traversal = NULL;
}

void IncompleteTaskIterator::advanceToIncomplete() {
    while (traversal->isValid() && !traversal->isDone()) {
        WorkComponent* component = traversal->current();

        if (component != NULL && component->isIncompleteWork()) {
            return;
        }

        traversal->next();
    }
}

void IncompleteTaskIterator::first() {
    traversal->first();
    advanceToIncomplete();
}

void IncompleteTaskIterator::next() {
    if (!traversal->isValid() || traversal->isDone()) {
        return;
    }

    traversal->next();
    advanceToIncomplete();
}

bool IncompleteTaskIterator::isDone() const {
    return traversal->isDone();
}

WorkComponent* IncompleteTaskIterator::current() const {
    return traversal->current();
}

bool IncompleteTaskIterator::isValid() const {
    return traversal->isValid();
}
