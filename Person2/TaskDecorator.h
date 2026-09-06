#ifndef TASKDECORATOR_H
#define TASKDECORATOR_H

#include <string>

#include "ExecutableTask.h"

class TaskDecorator : public ExecutableTask
{
protected:
    ExecutableTask* wrapped;

public:
    TaskDecorator(ExecutableTask* wrapped);

    virtual ~TaskDecorator();

    bool markReady() override;
    bool start() override;

    bool block(const std::string& reason) override;
    bool resolveBlock() override;

    bool submitForReview() override;
    bool approveReview() override;
    bool rejectReview() override;

    std::string getStateName() const override;

    double estimatedCost() const override;
    int priorityScore() const override;
    std::string summary() const override;

    bool isIncompleteWork() const override;

    void setStructureVersion(
        StructureVersion* version) override;
};

#endif