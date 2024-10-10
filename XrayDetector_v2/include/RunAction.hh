#ifndef RUN_ACTION_HH
#define RUN_ACTION_HH

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <vector>

namespace XrayDetector {

class RunAction : public G4UserRunAction {
public:
    RunAction();
    ~RunAction() override;

    G4Run* GenerateRun() override; // 이 부분이 선언되어 있는지 확인
    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

	void AccumulateEnergy(const std::vector<G4double>& eventDeposits);

private:
    std::vector<G4double> fTotalEnergyDeposits;

};

}

#endif // RUN_ACTION_HH
