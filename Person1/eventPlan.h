#ifndef EVENTPLAN_H
#define EVENTPLAN_H

#include <string>

#include "workGroup.h"
#include "structureVersion.h"

class EventPlan : public WorkGroup
{
private:
    std::string eventCode;
    StructureVersion structureVersion;

public:
    EventPlan(const std::string& id,const std::string& name, const std::string& eventCode);
    const std::string& getEventCode() const;
};
#endif