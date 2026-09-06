#ifndef REVIEWSTATE_H
#define REVIEWSTATE_H

#include "TaskState.h"

class ReviewState : public TaskState
{
public:
    std::string name() const override;

    bool approveReview(EventTask& task) override;

    bool rejectReview(EventTask& task) override;
};

#endif