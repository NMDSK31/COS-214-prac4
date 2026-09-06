#ifndef WORKCOMPONENT_H
#define WORKCOMPONENT_H
#include <cstddef>
#include <string>

#include "StructureVersion.h"

class DepthFirstIterator;

class WorkComponent {
public:
    WorkComponent(const std::string& id, const std::string& name);
    virtual ~WorkComponent() {}

    const std::string& getId() const;
    const std::string& getName() const;
    StructureVersion* getStructureVersion() const;
    virtual void setStructureVersion(StructureVersion* version);
    virtual bool isIncompleteWork() const;
    virtual double estimatedCost() const = 0;
    virtual int priorityScore() const = 0;
    virtual std::string summary() const = 0;

protected:
    friend class DepthFirstIterator;

    virtual std::size_t iteratorChildCount() const = 0;
    virtual WorkComponent* iteratorChildAt(std::size_t index) const = 0;

private:
    std::string id;
    std::string name;
    StructureVersion* version;
};
#endif
