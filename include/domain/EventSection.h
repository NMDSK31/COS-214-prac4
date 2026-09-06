#ifndef EVENTSECTION_H
#define EVENTSECTION_H
#include <string>
#include "WorkGroup.h"

class EventSection : public WorkGroup
{
private:
    std::string sectionCode;
public:
    EventSection(const std::string& id, const std::string& name,const std::string& sectionCode);
    const std::string& getSectionCode() const;
};

#endif
