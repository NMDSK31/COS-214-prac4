/**
 * @file EventTask.cpp
 * @brief Implements the EventTask leaf and State pattern context.
 */

#include "EventTask.h"

#include "PlannedState.h"

/**
 * @brief Constructs an event task.
 *
 * A newly created task starts in the Planned state.
 *
 * @param id Unique identifier for the task.
 * @param name Name of the task.
 * @param baseCost Base estimated cost of the task.
 * @param basePriority Base priority of the task.
 */
EventTask::EventTask(const std::string& id,
                     const std::string& name,
                     double baseCost,
                     int basePriority)
    : ExecutableTask(id, name),
      baseCost(baseCost),
      basePriority(basePriority),
      state(new PlannedState()),
      blockReason("")
{
}

/**
 * @brief Destroys the task and its current state.
 */
EventTask::~EventTask()
{
    delete state;
    state = nullptr;
}

/**
 * @brief Replaces the current task state.
 *
 * The EventTask owns the state object, so the previous
 * state is deleted when it is replaced.
 *
 * @param nextState New state to take ownership of.
 */
void EventTask::replaceState(TaskState* nextState)
{
    if (nextState == nullptr)
    {
        return;
    }

    delete state;
    state = nextState;
}

/**
 * @brief Stores the reason why a task was blocked.
 *
 * @param reason Reason for the block.
 */
void EventTask::setBlockReason(const std::string& reason)
{
    blockReason = reason;
}

/**
 * @brief Clears the current block reason.
 */
void EventTask::clearBlockReason()
{
    blockReason.clear();
}

/**
 * @brief Makes the task ready.
 *
 * @return Result of the current state's markReady operation.
 */
bool EventTask::markReady()
{
    return state->markReady(*this);
}

/**
 * @brief Starts the task.
 *
 * @return Result of the current state's start operation.
 */
bool EventTask::start()
{
    return state->start(*this);
}

/**
 * @brief Blocks the task.
 *
 * @param reason Reason why the task is blocked.
 * @return Result of the current state's block operation.
 */
bool EventTask::block(const std::string& reason)
{
    return state->block(*this, reason);
}

/**
 * @brief Resolves a task's block.
 *
 * @return Result of the current state's resolveBlock operation.
 */
bool EventTask::resolveBlock()
{
    return state->resolveBlock(*this);
}

/**
 * @brief Submits the task for review.
 *
 * @return Result of the current state's submitForReview operation.
 */
bool EventTask::submitForReview()
{
    return state->submitForReview(*this);
}

/**
 * @brief Approves a task under review.
 *
 * @return Result of the current state's approveReview operation.
 */
bool EventTask::approveReview()
{
    return state->approveReview(*this);
}

/**
 * @brief Rejects a task under review.
 *
 * @return Result of the current state's rejectReview operation.
 */
bool EventTask::rejectReview()
{
    return state->rejectReview(*this);
}

/**
 * @brief Gets the current state name.
 *
 * @return Name of the current state.
 */
std::string EventTask::getStateName() const
{
    return state->name();
}

/**
 * @brief Gets the estimated cost of the task.
 *
 * @return Base task cost.
 */
double EventTask::estimatedCost() const
{
    return baseCost;
}

/**
 * @brief Gets the priority score of the task.
 *
 * @return Base task priority.
 */
int EventTask::priorityScore() const
{
    return basePriority;
}

/**
 * @brief Creates a short task summary.
 *
 * @return Description containing the task name, state,
 *         cost and priority.
 */
std::string EventTask::summary() const
{
    return getName()
        + " | state: " + getStateName()
        + " | estimated cost: "
        + std::to_string(estimatedCost())
        + " | priority: "
        + std::to_string(priorityScore());
}

/**
 * @brief Checks whether the task is incomplete.
 *
 * @return true unless the task is in Completed state.
 */
bool EventTask::isIncompleteWork() const
{
    return !state->isCompleted();
}

/**
 * @brief Returns the number of children.
 *
 * EventTask is a Leaf, so it cannot contain children.
 *
 * @return 0.
 */
std::size_t EventTask::iteratorChildCount() const
{
    return 0;
}

/**
 * @brief Returns a child at the specified index.
 *
 * EventTask is a Leaf and therefore has no children.
 *
 * @param index Child index.
 * @return nullptr.
 */
WorkComponent* EventTask::iteratorChildAt(
    std::size_t index) const
{
    (void)index;
    return nullptr;
}