#include "EventAction.hh"
#include "RunAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "G4VPhysicalVolume.hh"

namespace XrayDetector {

EventAction::EventAction(RunAction* runAction)
    : G4UserEventAction(), fEnergyDeposits(861, 0.0), fStartDetectorID(-1), fEndDetectorID(-1), fRunAction(runAction) {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event*) {
    // 에너지 누적 벡터 초기화 (이벤트마다 초기화 필요)
    std::fill(fEnergyDeposits.begin(), fEnergyDeposits.end(), 0.0);
    fStartDetectorID = -1;
    fEndDetectorID = -1;
}

void EventAction::EndOfEventAction(const G4Event*) {
    auto analysisManager = G4AnalysisManager::Instance();

    // 위치 정보를 기록
    analysisManager->FillNtupleDColumn(0, 0, fStartPosition.x());
    analysisManager->FillNtupleDColumn(0, 1, fStartPosition.y());
    analysisManager->FillNtupleDColumn(0, 2, fStartPosition.z());
    analysisManager->FillNtupleIColumn(0, 3, fStartDetectorID);
    analysisManager->FillNtupleDColumn(0, 4, fEndPosition.x());
    analysisManager->FillNtupleDColumn(0, 5, fEndPosition.y());
    analysisManager->FillNtupleDColumn(0, 6, fEndPosition.z());
    analysisManager->FillNtupleIColumn(0, 7, fEndDetectorID);

    analysisManager->AddNtupleRow(0);

    // 에너지 누적값을 기록 (각 서브 탐지기별 에너지 누적)
    for (size_t i = 0; i < fEnergyDeposits.size(); ++i) {
        analysisManager->FillNtupleDColumn(1, i, fEnergyDeposits[i]);
    }
    analysisManager->AddNtupleRow(1);
}

void EventAction::AddEnergyDeposit(G4int detectorID, G4double edep) {
    if (detectorID >= 0 && detectorID < static_cast<G4int>(fEnergyDeposits.size())) {
        fEnergyDeposits[detectorID] += edep;
    }
}

void EventAction::RecordStartStep(const G4ThreeVector& prePosition, const G4VPhysicalVolume* postVolume) {
    if (fStartDetectorID == -1 && postVolume) {
        fStartPosition = prePosition;
        fStartDetectorID = postVolume->GetCopyNo();
    }
}

void EventAction::RecordEndStep(const G4ThreeVector& endPosition, G4int endDetectorID) {
    fEndPosition = endPosition;
    fEndDetectorID = endDetectorID;
}

}
