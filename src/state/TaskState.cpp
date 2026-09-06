/**
 * @file TaskState.cpp
 * @brief Implements the common behaviour of task states.
 */

#include "TaskState.h"
#include "EventTask.h"

/**
 * @brief Attempts to move a task to the Ready state.
 *
 * This operation is invalid for states that do not override it.
 *
 * @param task Task whose state is being changed.
 * @return false because the operation is not supported by default.
 */
bool TaskState::markReady(EventTask& task)
{
    (void)task;
    return false;
}

/**
 * @brief Attempts to start a task.
 *
 * This operation is invalid for states that do not override it.
 *
 * @param task Task being started.
 * @return false because the operation is not supported by default.
 */
bool TaskState::start(EventTask& task)
{
    (void)task;
    return false;
}

/**
 * @brief Attempts to block a task.
 *
 * This operation is invalid for states that do not override it.
 *
 * @param task Task being blocked.
 * @param reason Reason why the task is blocked.
 * @return false because the operation is not supported by default.
 */
bool TaskState::block(EventTask& task,
                      const std::string& reason)
{
    (void)task;
    (void)reason;
    return false;
}

/**
 * @brief Attempts to resolve a blocked task.
 *
 * This operation is invalid for states that do not override it.
 *
 * @param task Task whose block is being resolved.
 * @return false because the operation is not supported by default.
 */
bool TaskState::resolveBlock(EventTask& task)
{
    (void)task;
    return false;
}

/**
 * @brief Attempts to submit a task for review.
 *
 * This operation is invalid for states that do not override it.
 *
 * @param task Task being submitted.
 * @return false because the operation is not supported by default.
 */
bool TaskState::submitForReview(EventTask& task)
{
    (void)task;
    return false;
}

/**
 * @brief Attempts to approve a task under review.
 *
 * This operation is invalid for states that do not override it.
 *
 * @param task Task being approved.
 * @return false because the operation is not supported by default.
 */
bool TaskState::approveReview(EventTask& task)
{
    (void)task;
    return false;
}

/**
 * @brief Attempts to reject a task under review.
 *
 * This operation is invalid for states that do not override it.
 *
 * @param task Task being rejected.
 * @return false because the operation is not supported by default.
 */
bool TaskState::rejectReview(EventTask& task)
{
    (void)task;
    return false;
}

/**
 * @brief Checks whether this state represents completion.
 *
 * Only CompletedState overrides this method.
 *
 * @return false by default.
 */
bool TaskState::isCompleted() const
{
    return false;
}

/**
 * @brief Changes the state of the supplied task.
 *
 * Ownership of the new state is transferred to EventTask.
 *
 * @param task Task whose state is changing.
 * @param nextState New state for the task.
 */
void TaskState::transition(EventTask& task,
                           TaskState* nextState)
{
    task.replaceState(nextState);
}