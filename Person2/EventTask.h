#ifndef EVENTTASK_H
#define EVENTTASK_H

#include <string>

#include "ExecutableTask.h"
#include "TaskState.h"

class EventTask : public ExecutableTask
{
private:
    double baseCost;
    int basePriority;

    TaskState* state;
    std::string blockReason;

    friend class TaskState;

    void replaceState(TaskState* nextState);

protected:
    void setBlockReason(const std::string& reason);
    void clearBlockReason();

public:
    EventTask(const std::string& id,
              const std::string& name,
              double baseCost,
              int basePriority);

    ~EventTask();

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

    std::size_t iteratorChildCount() const override;
    WorkComponent* iteratorChildAt(std::size_t index) const override;
};

#endif