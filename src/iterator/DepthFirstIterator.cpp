#include "DepthFirstIterator.h"

#include "StructureVersion.h"
#include "WorkComponent.h"

DepthFirstIterator::DepthFirstIterator(WorkComponent* root,
                                       StructureVersion* version)
    : root(root),
      version(version),
      expectedVersion(version != NULL ? version->current() : 0),
      invalidated(false),
      currentNode(NULL),
      stack() {}

DepthFirstIterator::~DepthFirstIterator() {
    stack.clear();
    currentNode = NULL;
    root = NULL;
    version = NULL;
}

bool DepthFirstIterator::checkVersion() const {
    if (invalidated) {
        return false;
    }

    if (version != NULL && version->current() != expectedVersion) {
        invalidated = true;
        currentNode = NULL;
        stack.clear();
        return false;
    }

    return true;
}

void DepthFirstIterator::first() {
    stack.clear();
    currentNode = NULL;
    invalidated = false;
    expectedVersion = version != NULL ? version->current() : 0;

    if (root == NULL) {
        return;
    }

    currentNode = root;
    stack.push_back(Frame(root, 0));
}

void DepthFirstIterator::next() {
    if (!checkVersion() || currentNode == NULL) {
        return;
    }

    while (!stack.empty()) {
        Frame& frame = stack.back();

        if (frame.nextChildIndex < frame.node->iteratorChildCount()) {
            WorkComponent* child =
                frame.node->iteratorChildAt(frame.nextChildIndex);
            ++frame.nextChildIndex;

            if (child != NULL) {
                currentNode = child;
                stack.push_back(Frame(child, 0));
                return;
            }
        } else {
            stack.pop_back();
        }
    }

    currentNode = NULL;
}

bool DepthFirstIterator::isDone() const {
    return !checkVersion() || currentNode == NULL;
}

WorkComponent* DepthFirstIterator::current() const {
    if (!checkVersion()) {
        return NULL;
    }

    return currentNode;
}

bool DepthFirstIterator::isValid() const {
    return checkVersion();
}
