#ifndef EVENT_ACTION_HH
#define EVENT_ACTION_HH

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include <vector>

class G4Event;
class G4VPhysicalVolume;
namespace XrayDetector {
class RunAction;  // Forward declaration to use RunAction as a pointer

class EventAction : public G4UserEventAction {
public:
    EventAction(RunAction* runAction);  // RunAction 포인터를 받는 생성자
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event*) override;
    virtual void EndOfEventAction(const G4Event*) override;

    void AddEnergyDeposit(G4int detectorID, G4double edep);
    void RecordStartStep(const G4ThreeVector& prePosition, const G4VPhysicalVolume* postVolume);
    void RecordEndStep(const G4ThreeVector& endPosition, G4int endDetectorID);

private:
    G4ThreeVector fStartPosition; // 시작 위치
    G4ThreeVector fEndPosition;   // 종료 위치
    G4int fStartDetectorID;       // 시작 탐지기 ID
    G4int fEndDetectorID;         // 종료 탐지기 ID
    std::vector<G4double> fEnergyDeposits; // 각 서브 탐지기에서의 에너지 누적값

    RunAction* fRunAction; // RunAction 포인터
};

}

#endif // EVENT_ACTION_HH
