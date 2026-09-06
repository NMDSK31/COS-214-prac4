/**
 * @file ReviewState.cpp
 * @brief Implements the Review state of an event task.
 */

#include "ReviewState.h"
#include "CompletedState.h"
#include "ReadyState.h"
#include "EventTask.h"

/**
 * @brief Returns the name of this state.
 *
 * @return "Review".
 */
std::string ReviewState::name() const
{
    return "Review";
}

/**
 * @brief Approves a task that is under review.
 *
 * @param task Task being approved.
 * @return true when the task is completed.
 */
bool ReviewState::approveReview(EventTask& task)
{
    transition(task, new CompletedState());
    return true;
}

/**
 * @brief Rejects a task that is under review.
 *
 * A rejected task is returned to the Ready state.
 *
 * @param task Task being rejected.
 * @return true when the transition is performed.
 */
bool ReviewState::rejectReview(EventTask& task)
{
    transition(task, new ReadyState());
    return true;
}