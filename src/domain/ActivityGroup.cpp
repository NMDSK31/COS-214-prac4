#include "ActivityGroup.h"
ActivityGroup::ActivityGroup(const std::string& id, const std::string& name, const std::string& groupCode)
: WorkGroup(id,name),groupCode(groupCode)
{

}
const string& ActivityGroup:: getGroupCode() const
{
    return groupCode;
}
