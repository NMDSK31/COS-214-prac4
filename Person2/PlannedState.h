#ifndef PLANNEDSTATE_H
#define PLANNEDSTATE_H

#include "TaskState.h"

class PlannedState : public TaskState
{
public:
    std::string name() const override;

    bool markReady(EventTask& task) override;
};

#endif