#include "EventPlan.h"

EventPlan::EventPlan(const std::string& id, const std::string& name, const std::string& eventCode)
:WorkGroup(id,name),eventCode(eventCode)
{
    setStructureVersion(&structureVersion);
}
const std::string& EventPlan::getEventCode() const
{
    return eventCode;
}
