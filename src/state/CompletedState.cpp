/**
 * @file CompletedState.cpp
 * @brief Implements the Completed state of an event task.
 */

#include "CompletedState.h"
#include "EventTask.h"

/**
 * @brief Returns the name of this state.
 *
 * @return "Completed".
 */
std::string CompletedState::name() const
{
    return "Completed";
}

/**
 * @brief Checks whether the task is completed.
 *
 * @return true because this is the Completed state.
 */
bool CompletedState::isCompleted() const
{
    return true;
}