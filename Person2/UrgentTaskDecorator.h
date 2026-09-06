#ifndef URGENTTASKDECORATOR_H
#define URGENTTASKDECORATOR_H

#include <string>

#include "TaskDecorator.h"

class UrgentTaskDecorator : public TaskDecorator
{
private:
    int priorityBoost;
    double rushCost;
    std::string notifyContact;

public:
    UrgentTaskDecorator(ExecutableTask* wrapped,
                         int priorityBoost,
                         double rushCost,
                         const std::string& notifyContact);

    bool start() override;

    double estimatedCost() const override;

    int priorityScore() const override;

    std::string summary() const override;
};

#endif