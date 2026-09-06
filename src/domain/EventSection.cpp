#include "EventSection.h"

EventSection::EventSection(const string& id, const string& name, const string& sectionCode)
: WorkGroup(id,name),sectionCode(sectionCode)
{

}
const string& EventSection::getSectionCode() const
{
    return sectionCode;
}
