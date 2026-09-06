#ifndef READYSTATE_H
#define READYSTATE_H

#include "TaskState.h"

class ReadyState : public TaskState
{
public:
    std::string name() const override;

    bool start(EventTask& task) override;

    bool block(EventTask& task,
               const std::string& reason) override;
};

#endif