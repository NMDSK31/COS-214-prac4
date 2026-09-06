/**
 * @file ApprovalRequiredDecorator.cpp
 * @brief Implements the approval-required task decorator.
 */

#include "ApprovalRequiredDecorator.h"

/**
 * @brief Constructs an approval-required decorator.
 *
 * Tasks start without approval.
 *
 * @param wrapped Task being decorated.
 * @param approvalCost Additional cost associated with approval.
 */
ApprovalRequiredDecorator::ApprovalRequiredDecorator(
    ExecutableTask* wrapped,
    double approvalCost)
    : TaskDecorator(wrapped),
      approvalGranted(false),
      approvalCost(approvalCost)
{
}

/**
 * @brief Grants approval for the task.
 */
void ApprovalRequiredDecorator::grantApproval()
{
    approvalGranted = true;
}

/**
 * @brief Starts the task if approval has been granted.
 *
 * @return true if the wrapped task starts successfully,
 *         otherwise false.
 */
bool ApprovalRequiredDecorator::start()
{
    if (!approvalGranted)
    {
        return false;
    }

    return TaskDecorator::start();
}

/**
 * @brief Calculates the decorated task cost.
 *
 * @return Wrapped task cost plus the approval cost.
 */
double ApprovalRequiredDecorator::estimatedCost() const
{
    return TaskDecorator::estimatedCost() + approvalCost;
}

/**
 * @brief Creates a summary including the approval status.
 *
 * @return Task summary with approval information.
 */
std::string ApprovalRequiredDecorator::summary() const
{
    std::string result = TaskDecorator::summary();

    result += " | approval: ";

    if (approvalGranted)
    {
        result += "granted";
    }
    else
    {
        result += "required";
    }

    return result;
}