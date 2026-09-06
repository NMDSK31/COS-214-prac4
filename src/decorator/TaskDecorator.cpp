/**
 * @file TaskDecorator.cpp
 * @brief Implements the base decorator for executable tasks.
 */

#include "TaskDecorator.h"

/**
 * @brief Constructs a task decorator.
 *
 * @param wrapped Task being decorated.
 */
TaskDecorator::TaskDecorator(ExecutableTask* wrapped)
    : ExecutableTask(
          wrapped != nullptr ? wrapped->getId() : "",
          wrapped != nullptr ? wrapped->getName() : ""),
      wrapped(wrapped)
{
}

/**
 * @brief Destroys the decorator.
 *
 * Each decorator owns its wrapped task or decorator. Deleting the outermost
 * decorator therefore destroys the complete wrapped ownership chain.
 */
TaskDecorator::~TaskDecorator()
{
    delete wrapped;
    wrapped = nullptr;
}

/**
 * @brief Forwards markReady to the wrapped task.
 */
bool TaskDecorator::markReady()
{
    return wrapped != nullptr && wrapped->markReady();
}

/**
 * @brief Forwards start to the wrapped task.
 */
bool TaskDecorator::start()
{
    return wrapped != nullptr && wrapped->start();
}

/**
 * @brief Forwards block to the wrapped task.
 */
bool TaskDecorator::block(const std::string& reason)
{
    return wrapped != nullptr && wrapped->block(reason);
}

/**
 * @brief Forwards resolveBlock to the wrapped task.
 */
bool TaskDecorator::resolveBlock()
{
    return wrapped != nullptr && wrapped->resolveBlock();
}

/**
 * @brief Forwards submitForReview to the wrapped task.
 */
bool TaskDecorator::submitForReview()
{
    return wrapped != nullptr && wrapped->submitForReview();
}

/**
 * @brief Forwards approveReview to the wrapped task.
 */
bool TaskDecorator::approveReview()
{
    return wrapped != nullptr && wrapped->approveReview();
}

/**
 * @brief Forwards rejectReview to the wrapped task.
 */
bool TaskDecorator::rejectReview()
{
    return wrapped != nullptr && wrapped->rejectReview();
}

/**
 * @brief Gets the current state of the wrapped task.
 */
std::string TaskDecorator::getStateName() const
{
    if (wrapped == nullptr)
    {
        return "Unknown";
    }

    return wrapped->getStateName();
}

/**
 * @brief Gets the estimated cost of the wrapped task.
 */
double TaskDecorator::estimatedCost() const
{
    if (wrapped == nullptr)
    {
        return 0.0;
    }

    return wrapped->estimatedCost();
}

/**
 * @brief Gets the priority score of the wrapped task.
 */
int TaskDecorator::priorityScore() const
{
    if (wrapped == nullptr)
    {
        return 0;
    }

    return wrapped->priorityScore();
}

/**
 * @brief Gets a summary of the wrapped task.
 */
std::string TaskDecorator::summary() const
{
    if (wrapped == nullptr)
    {
        return "No task wrapped";
    }

    return wrapped->summary();
}

/**
 * @brief Checks whether the wrapped task is incomplete.
 */
bool TaskDecorator::isIncompleteWork() const
{
    return wrapped != nullptr && wrapped->isIncompleteWork();
}

/**
 * @brief Propagates the StructureVersion to the wrapped task.
 *
 * @param version Shared structure version.
 */
void TaskDecorator::setStructureVersion(
    StructureVersion* version)
{
    WorkComponent::setStructureVersion(version);

    if (wrapped != nullptr)
    {
        wrapped->setStructureVersion(version);
    }
}

/**
 * @brief Returns the number of children.
 *
 * Decorators behave as leaves from the Composite's point
 * of view.
 *
 * @return 0.
 */
std::size_t TaskDecorator::iteratorChildCount() const
{
    return 0;
}

/**
 * @brief Returns a child at the specified index.
 *
 * @param index Child index.
 * @return nullptr because the decorator is treated as a leaf.
 */
WorkComponent* TaskDecorator::iteratorChildAt(
    std::size_t index) const
{
    (void)index;
    return nullptr;
}
