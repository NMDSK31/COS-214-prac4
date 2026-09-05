#ifndef DEPTH_FIRST_ITERATOR_H
#define DEPTH_FIRST_ITERATOR_H

#include "WorkIterator.h"

#include <cstddef>
#include <vector>

class StructureVersion;

/**
 * @brief Pre-order depth-first traversal of a WorkComponent hierarchy.
 *
 * The iterator stores non-owning pointers. A captured StructureVersion is
 * checked before any stored hierarchy pointer is dereferenced.
 */
class DepthFirstIterator : public WorkIterator {
public:
    DepthFirstIterator(WorkComponent* root, StructureVersion* version);
    virtual ~DepthFirstIterator();

    virtual void first();
    virtual void next();
    virtual bool isDone() const;
    virtual WorkComponent* current() const;
    virtual bool isValid() const;

private:
    struct Frame {
        Frame(WorkComponent* component, std::size_t childIndex)
            : node(component), nextChildIndex(childIndex) {}

        WorkComponent* node;
        std::size_t nextChildIndex;
    };

    bool checkVersion() const;

    WorkComponent* root;
    StructureVersion* version;
    unsigned long expectedVersion;
    mutable bool invalidated;
    mutable WorkComponent* currentNode;
    mutable std::vector<Frame> stack;
};

#endif
