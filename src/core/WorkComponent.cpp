#include "WorkComponent.h"
using namespace std;

WorkComponent::WorkComponent(const string& id,const string &name)
{
    this->id=id;
    this->name=name;
    version=NULL;
}
const string & WorkComponent::getId()const
{
    return id;
}
const string& WorkComponent::getName()const
{
    return name;
}
StructureVersion* WorkComponent::getStructureVersion()const
{
    return version;
}
void WorkComponent::setStructureVersion(StructureVersion * s)
{
    version=s;
}
bool WorkComponent::isIncompleteWork()const
{
    return false;
}
