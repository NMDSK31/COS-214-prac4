#ifndef INCOMPLETE_TASK_ITERATOR_H
#define INCOMPLETE_TASK_ITERATOR_H

#include "WorkIterator.h"

class DepthFirstIterator;
class StructureVersion;

/**
 * @brief Filtered traversal that yields only incomplete executable work.
 *
 * Selection is performed polymorphically through
 * WorkComponent::isIncompleteWork(), without exposing containers or checking
 * concrete component types.
 */
class IncompleteTaskIterator : public WorkIterator {
public:
    IncompleteTaskIterator(WorkComponent* root, StructureVersion* version);
    virtual ~IncompleteTaskIterator();

    virtual void first();
    virtual void next();
    virtual bool isDone() const;
    virtual WorkComponent* current() const;
    virtual bool isValid() const;

private:
    IncompleteTaskIterator(const IncompleteTaskIterator&) = delete;
    IncompleteTaskIterator& operator=(const IncompleteTaskIterator&) = delete;

    void advanceToIncomplete();

    DepthFirstIterator* traversal;
};

#endif
