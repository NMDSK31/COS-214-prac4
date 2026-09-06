#ifndef APPROVALREQUIREDDECORATOR_H
#define APPROVALREQUIREDDECORATOR_H

#include "TaskDecorator.h"

class ApprovalRequiredDecorator : public TaskDecorator
{
private:
    bool approvalGranted;
    double approvalCost;

public:
    ApprovalRequiredDecorator(ExecutableTask* wrapped,
                               double approvalCost);

    void grantApproval();

    bool start() override;

    double estimatedCost() const override;

    std::string summary() const override;
};

#endif