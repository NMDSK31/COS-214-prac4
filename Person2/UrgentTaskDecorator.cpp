/**
 * @file UrgentTaskDecorator.cpp
 * @brief Implements the urgent task decorator.
 */

#include "UrgentTaskDecorator.h"

/**
 * @brief Constructs an urgent task decorator.
 *
 * @param wrapped Task being decorated.
 * @param priorityBoost Amount added to the task priority.
 * @param rushCost Additional cost for urgent handling.
 * @param notifyContact Contact associated with the urgent task.
 */
UrgentTaskDecorator::UrgentTaskDecorator(
    ExecutableTask* wrapped,
    int priorityBoost,
    double rushCost,
    const std::string& notifyContact)
    : TaskDecorator(wrapped),
      priorityBoost(priorityBoost),
      rushCost(rushCost),
      notifyContact(notifyContact)
{
}

/**
 * @brief Starts the urgent task.
 *
 * The normal task start operation is still used.
 *
 * @return Result of starting the wrapped task.
 */
bool UrgentTaskDecorator::start()
{
    return TaskDecorator::start();
}

/**
 * @brief Calculates the urgent task cost.
 *
 * @return Wrapped task cost plus the rush cost.
 */
double UrgentTaskDecorator::estimatedCost() const
{
    return TaskDecorator::estimatedCost() + rushCost;
}

/**
 * @brief Calculates the urgent task priority.
 *
 * @return Wrapped priority plus the urgent priority boost.
 */
int UrgentTaskDecorator::priorityScore() const
{
    return TaskDecorator::priorityScore() + priorityBoost;
}

/**
 * @brief Creates a summary containing urgent-task information.
 *
 * @return Task summary with priority and contact information.
 */
std::string UrgentTaskDecorator::summary() const
{
    std::string result = TaskDecorator::summary();

    result += " | urgent: yes";
    result += " | notify: " + notifyContact;

    return result;
}