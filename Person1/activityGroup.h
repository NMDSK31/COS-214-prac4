#ifndef ACTIVITYGROUP_H
#define ACTIVITYGROUP_H

#include <string>

#include "workGroup.h"

class ActivityGroup : public WorkGroup
{
private:
    std::string groupCode;
public:
    ActivityGroup(const std::string& id,const std::string& name,const std::string& groupCode);
    const std::string& getGroupCode() const;
};

#endif