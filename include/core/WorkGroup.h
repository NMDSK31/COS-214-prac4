#ifndef WORKGROUP_H
#define WORKGROUP_H
#include <iostream>
#include <vector>
#include "WorkComponent.h"
using namespace std;
class WorkIterator;
class WorkGroup:public WorkComponent
{
    private:
          vector<WorkComponent*> children;  
    public:
        WorkGroup(const std::string& id, const std::string& name);
        bool addChild(WorkComponent*child);
        WorkComponent* detachChild(const string& childId);
        bool removeChild(const std::string& childId);
        WorkComponent* findDirectById(const std::string& childId) const;
        void setStructureVersion(StructureVersion* version);
        double estimatedCost() const;
        int priorityScore() const;
        string summary() const;
        WorkIterator* createDepthFirstIterator();
        WorkIterator* createIncompleteTaskIterator();
        std::size_t iteratorChildCount() const;
        WorkComponent* iteratorChildAt(std::size_t index) const;
        virtual ~WorkGroup();

};
#endif
