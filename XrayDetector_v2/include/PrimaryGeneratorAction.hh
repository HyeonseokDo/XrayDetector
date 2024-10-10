#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include <vector>

namespace XrayDetector {

class DetectorConstruction; // Forward declaration

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction(const DetectorConstruction* detConstruction);  // 인자를 받는 생성자 추가
    ~PrimaryGeneratorAction() override;

    void GeneratePrimaries(G4Event* event) override;

private:
    std::vector<G4ParticleGun*> fParticleGuns;
    const DetectorConstruction* fDetConstruction; // DetectorConstruction를 받음
};

}

#endif // PRIMARYGENERATORACTION_HH

