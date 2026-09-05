#ifndef TASKLIST_H
#define TASKLIST_H

#include <string>

#include "workGroup.h"

class TaskList : public WorkGroup
{
private:
    std::string listCode;
    std::string location;
public:
    TaskList(const std::string& id,const std::string& name,const std::string& listCode,const std::string& location);
    const std::string& getListCode() const;
    const std::string& getLocation() const;
};

#endif