#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

namespace XrayDetector {

ActionInitialization::ActionInitialization(const DetectorConstruction* detConstruction)
    : G4VUserActionInitialization(), fDetConstruction(detConstruction) {}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const {
    SetUserAction(new RunAction());
}

void ActionInitialization::Build() const {
    auto runAction = new RunAction();
    SetUserAction(runAction);

    auto eventAction = new EventAction(runAction); // RunAction 포인터를 전달하여 EventAction 객체 생성
    SetUserAction(eventAction);

    SetUserAction(new PrimaryGeneratorAction(fDetConstruction));
    SetUserAction(new SteppingAction(fDetConstruction, eventAction));
}

}
