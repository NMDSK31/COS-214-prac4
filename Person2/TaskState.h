#ifndef TASKSTATE_H
#define TASKSTATE_H

#include <string>

class EventTask;

class TaskState
{
public:
    virtual ~TaskState()
    {
    }

    virtual std::string name() const = 0;

    virtual bool markReady(EventTask& task);
    virtual bool start(EventTask& task);
    virtual bool block(EventTask& task,
                       const std::string& reason);
    virtual bool resolveBlock(EventTask& task);
    virtual bool submitForReview(EventTask& task);
    virtual bool approveReview(EventTask& task);
    virtual bool rejectReview(EventTask& task);

    virtual bool isCompleted() const;

protected:
    void transition(EventTask& task,
                    TaskState* nextState);
};

#endif