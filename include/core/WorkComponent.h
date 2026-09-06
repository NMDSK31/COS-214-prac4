#ifndef WORKCOMPONENT_H
#define WORKCOMPONENT_H
#include <iostream>
#include "StructureVersion.h"

using namespace std;

class WorkComponent
{
    private:
        string id;
        string name;
        StructureVersion* version;
    public:
        WorkComponent(const string&,const string &);
        const string& getId()const;
        const string& getName()const;
        StructureVersion* getStructureVersion()const;
        virtual void setStructureVersion(StructureVersion* version);
        virtual bool isIncompleteWork() const;
        virtual double estimatedCost() const=0;
        virtual int priorityScore() const=0;
        virtual string summary() const=0;
        virtual std::size_t iteratorChildCount() const=0;
        virtual WorkComponent* iteratorChildAt(std::size_t index) const=0;
        virtual ~WorkComponent(){};
};
#endif
