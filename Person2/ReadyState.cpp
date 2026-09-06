/**
 * @file ReadyState.cpp
 * @brief Implements the Ready state of an event task.
 */

#include "ReadyState.h"
#include "InProgressState.h"
#include "BlockedState.h"
#include "EventTask.h"

/**
 * @brief Returns the name of this state.
 *
 * @return "Ready".
 */
std::string ReadyState::name() const
{
    return "Ready";
}

/**
 * @brief Starts a task that is ready to run.
 *
 * @param task Task being started.
 * @return true when the transition is performed.
 */
bool ReadyState::start(EventTask& task)
{
    transition(task, new InProgressState());
    return true;
}

/**
 * @brief Blocks a task that is currently ready.
 *
 * @param task Task being blocked.
 * @param reason Reason for blocking the task.
 * @return true when the task is moved to Blocked.
 */
bool ReadyState::block(EventTask& task,
                       const std::string& reason)
{
    task.setBlockReason(reason);
    transition(task, new BlockedState());
    return true;
}