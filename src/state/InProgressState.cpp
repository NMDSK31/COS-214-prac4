/**
 * @file InProgressState.cpp
 * @brief Implements the InProgress state of an event task.
 */

#include "InProgressState.h"
#include "BlockedState.h"
#include "ReviewState.h"
#include "EventTask.h"

/**
 * @brief Returns the name of this state.
 *
 * @return "InProgress".
 */
std::string InProgressState::name() const
{
    return "InProgress";
}

/**
 * @brief Blocks a task that is currently in progress.
 *
 * @param task Task being blocked.
 * @param reason Reason for blocking the task.
 * @return true when the transition is performed.
 */
bool InProgressState::block(EventTask& task,
                            const std::string& reason)
{
    task.setBlockReason(reason);
    transition(task, new BlockedState());
    return true;
}

/**
 * @brief Submits an in-progress task for review.
 *
 * @param task Task being submitted for review.
 * @return true when the transition is performed.
 */
bool InProgressState::submitForReview(EventTask& task)
{
    transition(task, new ReviewState());
    return true;
}