#include "workGroup.h"
#include <sstream>

using namespace std;

WorkGroup::WorkGroup(const string& id, const string& name)
:WorkComponent(id,name)
{

}
bool WorkGroup::addChild(WorkComponent* child)
{
    if(child==NULL)
    {
        return false;
    }
    for(size_t i=0;i<children.size();i++)
    {
        if(children[i]==child)
        {
            return false;
        }
        if (children[i]->getId() == child->getId())
        {
            return false;
        }
    }
    children.push_back(child);
    child->setStructureVersion(
        getStructureVersion()
    );
    if (getStructureVersion() != NULL)
    {
        getStructureVersion()->bump();
    }
    return true;
}
WorkComponent * WorkGroup::detachChild(const string & childID)
{
    for(size_t i=0;i<children.size();i++)
    {
        if(children[i]->getId()==childID)
        {
            WorkComponent* detached = children[i];

            children.erase(children.begin() + i);

            detached->setStructureVersion(NULL);

            if (getStructureVersion() != NULL)
            {
                getStructureVersion()->bump();
            }

            return detached;
        }
    }
    return NULL;
}
bool WorkGroup::removeChild(const string& childId)
{
    WorkComponent* p=detachChild(childId);
    if(p==NULL)
    {
        return false;
    }
    delete p;
    return true;
}
WorkComponent* WorkGroup::findDirectById(const string& childId) const
{
    for (size_t i = 0;i < children.size();++i)
    {
        if (children[i]->getId() == childId)
        {
            return children[i];
        }
    }
    return NULL;
}
void WorkGroup::setStructureVersion(StructureVersion* version)
{
    WorkComponent::setStructureVersion(version);
    for (std::size_t i = 0;i < children.size();++i)
    {
        children[i]->setStructureVersion(version);
    }
}
double WorkGroup:: estimatedCost()const
{
    
    double total = 0.0;
    for (std::size_t i = 0;i < children.size();++i)
    {
        total += children[i]->estimatedCost();
    }
    return total;
}
int WorkGroup::priorityScore() const
{
    int maxPriority = 0;
    for (std::size_t i = 0;i < children.size();++i)
    {
        int childPriority=children[i]->priorityScore();
        if (childPriority>maxPriority)
        {
            maxPriority=childPriority;
        }
    }
    return maxPriority;
}
string WorkGroup::summary() const
{
    ostringstream out;
    out<<getName()<< " | children: "<< children.size()<< " | estimated cost: "<< estimatedCost()<< " | priority: "<< priorityScore();
    return out.str();
}
size_t WorkGroup::iteratorChildCount() const
{
    return children.size();
}
WorkComponent*WorkGroup::iteratorChildAt(size_t index) const
{
    if (index >= children.size())
    {
        return NULL;
    }
    return children[index];
}
WorkIterator* WorkGroup::createDepthFirstIterator()
{
 //implement
}
WorkIterator* WorkGroup:: createIncompleteTaskIterator()
{
    //implement
}
WorkGroup::~WorkGroup()
{
    for (size_t i = 0; i < children.size(); i++)
    {
        delete children[i];
    }
    children.clear();
}