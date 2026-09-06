#ifndef COMPLETEDSTATE_H
#define COMPLETEDSTATE_H

#include "TaskState.h"

class CompletedState : public TaskState
{
public:
    std::string name() const override;

    bool isCompleted() const override;
};

#endif