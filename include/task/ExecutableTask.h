#ifndef EXECUTABLETASK_H
#define EXECUTABLETASK_H

#include <string>
#include "WorkComponent.h"

class ExecutableTask : public WorkComponent
{
public:
    ExecutableTask(const std::string& id,
                   const std::string& name)
        : WorkComponent(id, name)
    {
    }

    virtual ~ExecutableTask()
    {
    }

    virtual bool markReady() = 0;
    virtual bool start() = 0;
    virtual bool block(const std::string& reason) = 0;
    virtual bool resolveBlock() = 0;
    virtual bool submitForReview() = 0;
    virtual bool approveReview() = 0;
    virtual bool rejectReview() = 0;

    virtual std::string getStateName() const = 0;
};

#endif
