#include "WorkIterator.h"

#include "../Person1/activityGroup.h"
#include "../Person1/eventPlan.h"
#include "../Person1/eventSection.h"
#include "../Person1/taskList.h"
#include "../Person2/ApprovalRequiredDecorator.h"
#include "../Person2/EventTask.h"
#include "../Person2/UrgentTaskDecorator.h"

#include <iostream>
#include <string>

namespace {

const char* outcome(bool succeeded) {
    return succeeded ? "accepted" : "rejected";
}

void printTraversal(const std::string& heading, WorkIterator& iterator) {
    std::cout << "\n" << heading << "\n";
    iterator.first();

    while (!iterator.isDone()) {
        WorkComponent* component = iterator.current();
        if (component != NULL) {
            std::cout << "  - " << component->summary() << "\n";
        }
        iterator.next();
    }
}

} // namespace

int main() {
    std::cout << "EventForge: Open Day operations\n";

    EventPlan* plan =
        new EventPlan("open-day", "University Open Day", "OD-2026");
    EventSection* visitorExperience = new EventSection(
        "visitor-experience", "Visitor experience", "VIS");
    ActivityGroup* venueSetup =
        new ActivityGroup("venue-setup", "Venue setup", "SETUP");
    TaskList* technicalTasks = new TaskList(
        "technical", "Technical preparation", "TECH", "Main hall");
    TaskList* liveOperations = new TaskList(
        "live-operations", "Live operations", "LIVE", "Control room");

    EventTask* testLighting =
        new EventTask("test-lighting", "Test hall lighting", 450.0, 4);
    EventTask* setupSound =
        new EventTask("setup-sound", "Set up sound", 800.0, 6);
    EventTask* welcomeGuests =
        new EventTask("welcome-guests", "Welcome guests", 200.0, 5);

    technicalTasks->addChild(testLighting);
    technicalTasks->addChild(setupSound);
    liveOperations->addChild(welcomeGuests);
    venueSetup->addChild(technicalTasks);
    venueSetup->addChild(liveOperations);
    visitorExperience->addChild(venueSetup);
    plan->addChild(visitorExperience);

    WorkIterator* report = plan->createDepthFirstIterator();
    WorkIterator* supervisor = plan->createDepthFirstIterator();
    report->first();
    supervisor->first();
    report->next();
    report->next();

    std::cout << "\nIndependent traversal cursors\n";
    std::cout << "  report cursor: " << report->current()->getName() << "\n";
    std::cout << "  supervisor cursor: "
              << supervisor->current()->getName() << "\n";

    std::cout << "\nState-controlled setup\n";
    std::cout << "  start while Planned: "
              << outcome(setupSound->start()) << "\n";
    std::cout << "  mark Ready: " << outcome(setupSound->markReady()) << "\n";

    const double costBeforeDecoration = plan->estimatedCost();
    const int priorityBeforeDecoration = plan->priorityScore();

    WorkIterator* traversalBeforeMove = plan->createDepthFirstIterator();
    traversalBeforeMove->first();

    WorkComponent* detached = technicalTasks->detachChild("setup-sound");
    if (detached != setupSound) {
        std::cerr << "Could not move Setup Sound safely.\n";
        delete detached;
        delete traversalBeforeMove;
        delete report;
        delete supervisor;
        delete plan;
        return 1;
    }

    UrgentTaskDecorator* urgentSetup = new UrgentTaskDecorator(
        setupSound, 3, 150.0, "event coordinator");
    ApprovalRequiredDecorator* approvedSetup =
        new ApprovalRequiredDecorator(urgentSetup, 50.0);
    liveOperations->addChild(approvedSetup);

    std::cout << "\nMove and runtime decoration\n";
    std::cout << "  old traversal valid after move: "
              << (traversalBeforeMove->isValid() ? "yes" : "no") << "\n";
    std::cout << "  cost: " << costBeforeDecoration << " -> "
              << plan->estimatedCost() << "\n";
    std::cout << "  priority: " << priorityBeforeDecoration << " -> "
              << plan->priorityScore() << "\n";
    std::cout << "  start before organiser approval: "
              << outcome(approvedSetup->start()) << "\n";
    approvedSetup->grantApproval();
    std::cout << "  start after organiser approval: "
              << outcome(approvedSetup->start()) << "\n";

    std::cout << "\nComplete guest-welcome lifecycle\n";
    std::cout << "  mark Ready: " << outcome(welcomeGuests->markReady()) << "\n";
    std::cout << "  start: " << outcome(welcomeGuests->start()) << "\n";
    std::cout << "  submit for review: "
              << outcome(welcomeGuests->submitForReview()) << "\n";
    std::cout << "  approve: "
              << outcome(welcomeGuests->approveReview()) << "\n";

    WorkIterator* refreshed = plan->createDepthFirstIterator();
    printTraversal("Refreshed depth-first report", *refreshed);

    WorkIterator* incomplete = plan->createIncompleteTaskIterator();
    printTraversal("Incomplete work after the runtime changes", *incomplete);

    delete incomplete;
    delete refreshed;
    delete traversalBeforeMove;
    delete report;
    delete supervisor;
    delete plan;

    std::cout << "\nEventForge scenario completed.\n";
    return 0;
}
