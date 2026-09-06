#ifndef WORKGROUP_H
#define WORKGROUP_H
#include <cstddef>
#include <string>
#include <vector>

#include "WorkComponent.h"

class WorkIterator;

class WorkGroup : public WorkComponent {
public:
    WorkGroup(const std::string& id, const std::string& name);
    virtual ~WorkGroup();

    bool addChild(WorkComponent* child);
    WorkComponent* detachChild(const std::string& childId);
    bool removeChild(const std::string& childId);
    WorkComponent* findDirectById(const std::string& childId) const;
    void setStructureVersion(StructureVersion* version) override;
    double estimatedCost() const override;
    int priorityScore() const override;
    std::string summary() const override;
    WorkIterator* createDepthFirstIterator();
    WorkIterator* createIncompleteTaskIterator();

protected:
    std::size_t iteratorChildCount() const override;
    WorkComponent* iteratorChildAt(std::size_t index) const override;

private:
    WorkGroup(const WorkGroup&) = delete;
    WorkGroup& operator=(const WorkGroup&) = delete;

    std::vector<WorkComponent*> children;
};
#endif
