#include "TaskList.h"

TaskList::TaskList(const string& id, const string& name, const string& listCode, const string& location)
:WorkGroup(id,name),listCode(listCode),location(location)
{

}
const string& TaskList:: getListCode() const
{
    return listCode;
}
const string& TaskList::getLocation() const
{
    return location;
}
