/**
 * @file BlockedState.cpp
 * @brief Implements the Blocked state of an event task.
 */

#include "BlockedState.h"
#include "ReadyState.h"
#include "EventTask.h"

/**
 * @brief Returns the name of this state.
 *
 * @return "Blocked".
 */
std::string BlockedState::name() const
{
    return "Blocked";
}

/**
 * @brief Resolves the block on a task.
 *
 * Once the block has been resolved, the task becomes Ready again.
 *
 * @param task Task whose block is being resolved.
 * @return true when the transition is performed.
 */
bool BlockedState::resolveBlock(EventTask& task)
{
    task.clearBlockReason();
    transition(task, new ReadyState());
    return true;
}