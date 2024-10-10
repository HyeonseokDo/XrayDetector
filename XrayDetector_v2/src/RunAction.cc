#include "RunAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"

namespace XrayDetector {

RunAction::RunAction() : G4UserRunAction() {
    G4RunManager::GetRunManager()->SetPrintProgress(1);
    auto analysisManager = G4AnalysisManager::Instance();
    if (!analysisManager) {
        G4cerr << "Failed to create G4AnalysisManager!" << G4endl;
        return;
    }
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetNtupleMerging(false);  // 단일 스레드 실행 시 필요 없음

    // 이벤트별 위치 정보를 저장할 Ntuple 생성
    analysisManager->CreateNtuple("Xray", "Gamma Info");
    analysisManager->CreateNtupleDColumn("StartX");
    analysisManager->CreateNtupleDColumn("StartY");
    analysisManager->CreateNtupleDColumn("StartZ");
    analysisManager->CreateNtupleIColumn("StartDetectorID");
    analysisManager->CreateNtupleDColumn("EndX");
    analysisManager->CreateNtupleDColumn("EndY");
    analysisManager->CreateNtupleDColumn("EndZ");
    analysisManager->CreateNtupleIColumn("EndDetectorID");
    analysisManager->FinishNtuple(); // 이 Ntuple의 ID는 0

    // 각 이벤트에서 각 서브 탐지기의 에너지 누적값을 저장할 Ntuple 생성
    analysisManager->CreateNtuple("TotalEnergy", "Total Energy Deposit in Detectors");
    for (int i = 0; i < 861; ++i) {
        analysisManager->CreateNtupleDColumn("EnergyDeposit_" + std::to_string(i));
    }
    analysisManager->FinishNtuple(); // 이 Ntuple의 ID는 1
}

RunAction::~RunAction() {
    delete G4AnalysisManager::Instance();
}

G4Run* RunAction::GenerateRun() {
    return new G4Run();
}

void RunAction::BeginOfRunAction(const G4Run*) {
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile("XrayOutput.root");
}

void RunAction::EndOfRunAction(const G4Run*) {
    auto analysisManager = G4AnalysisManager::Instance();

	// 누적된 에너지 값을 기록 (각 서브 탐지기별로 하나의 값만 기록)
    for (size_t i = 0; i < fTotalEnergyDeposits.size(); ++i) {
        analysisManager->FillNtupleDColumn(1, i, fTotalEnergyDeposits[i]);
    }

    analysisManager->AddNtupleRow(1); // 모든 서브 탐지기의 누적 에너지를 한 번의 엔트리로 기록

    analysisManager->Write();
    analysisManager->CloseFile();
}

}
