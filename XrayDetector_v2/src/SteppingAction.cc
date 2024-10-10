#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4VPhysicalVolume.hh"

namespace XrayDetector {

SteppingAction::SteppingAction(const DetectorConstruction* detConstruction, EventAction* eventAction)
    : G4UserSteppingAction(), fDetConstruction(detConstruction), fEventAction(eventAction) {}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    auto preStepPoint = step->GetPreStepPoint();
    auto postStepPoint = step->GetPostStepPoint();

    // Get position information
    G4ThreeVector prePosition = preStepPoint->GetPosition();
    G4ThreeVector postPosition = postStepPoint->GetPosition();

    // Get volume information
    const G4VPhysicalVolume* postVolume = postStepPoint->GetTouchableHandle()->GetVolume();

    // Only consider primary particle (TrackID == 1)
    if (step->GetTrack()->GetTrackID() == 1) {
        // Record the start step
        fEventAction->RecordStartStep(prePosition, postVolume);

        // Record the end step when particle is killed
        if (step->GetTrack()->GetTrackStatus() == fStopAndKill) {
            G4int endDetectorID = (postVolume && postVolume->GetName() == "Silicon") ? postVolume->GetCopyNo() : -999;
            fEventAction->RecordEndStep(postPosition, endDetectorID);
        }
    }

	auto edep = step->GetTotalEnergyDeposit();
    if (edep > 0) {
        auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
        if (volume->GetName() == "Silicon") {
            G4int copyNo = volume->GetCopyNo();
            fEventAction->AddEnergyDeposit(copyNo, edep);
        }
    }
}

}
