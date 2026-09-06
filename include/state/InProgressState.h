#ifndef INPROGRESSSTATE_H
#define INPROGRESSSTATE_H

#include "TaskState.h"

class InProgressState : public TaskState
{
public:
    std::string name() const override;

    bool block(EventTask& task,
               const std::string& reason) override;

    bool submitForReview(EventTask& task) override;
};

#endif