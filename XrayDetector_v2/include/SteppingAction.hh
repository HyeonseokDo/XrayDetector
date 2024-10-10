#ifndef STEPPING_ACTION_HH
#define STEPPING_ACTION_HH

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

namespace XrayDetector {

class SteppingAction : public G4UserSteppingAction {
public:
    SteppingAction(const DetectorConstruction* detConstruction, EventAction* eventAction);
    virtual ~SteppingAction();

    virtual void UserSteppingAction(const G4Step* step) override;

private:
    const DetectorConstruction* fDetConstruction;
    EventAction* fEventAction;
};

}

#endif // STEPPING_ACTION_HH
