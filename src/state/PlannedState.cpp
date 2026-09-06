/**
 * @file PlannedState.cpp
 * @brief Implements the Planned state of an event task.
 */

#include "PlannedState.h"
#include "ReadyState.h"
#include "EventTask.h"

/**
 * @brief Returns the name of this state.
 *
 * @return "Planned".
 */
std::string PlannedState::name() const
{
    return "Planned";
}

/**
 * @brief Moves a planned task into the Ready state.
 *
 * @param task Task that is being made ready.
 * @return true when the transition is performed.
 */
bool PlannedState::markReady(EventTask& task)
{
    transition(task, new ReadyState());
    return true;
}