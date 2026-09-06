#ifndef BLOCKEDSTATE_H
#define BLOCKEDSTATE_H

#include "TaskState.h"

class BlockedState : public TaskState
{
public:
    std::string name() const override;

    bool resolveBlock(EventTask& task) override;
};

#endif