#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4Gamma.hh"
#include "G4Positron.hh"
#include "G4SystemOfUnits.hh"

namespace XrayDetector {

PrimaryGeneratorAction::PrimaryGeneratorAction(const DetectorConstruction* detConstruction)
    : fDetConstruction(detConstruction) {
    G4int n_particle = 1;
    fParticleGuns.push_back(new G4ParticleGun(n_particle)); // 총을 하나 생성

    // 기본 입자를 감마선으로 설정
    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");//gamma
    fParticleGuns[0]->SetParticleDefinition(particle);
    fParticleGuns[0]->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGuns[0]->SetParticleEnergy(0.1 * MeV);  // 에너지 설정
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    for (auto gun : fParticleGuns) {
        delete gun;  // 생성된 총 객체를 삭제
    }
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    //G4ThreeVector position(-0.21 * cm, -1.* cm, -7. * cm);  // 총 위치 설정
    //G4ThreeVector position(-0.11 * cm, -0.5* cm, -7. * cm);  // 총 위치 설정
    G4ThreeVector position(0. * cm, 0.* cm, -7. * cm);  // 총 위치 설정
    fParticleGuns[0]->SetParticlePosition(position);
    fParticleGuns[0]->GeneratePrimaryVertex(event);  // 입자 생성
}

}

