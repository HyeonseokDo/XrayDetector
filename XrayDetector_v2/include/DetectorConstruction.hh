#ifndef DETECTOR_CONSTRUCTION_HH
#define DETECTOR_CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4GlobalMagFieldMessenger.hh"

namespace XrayDetector {

/// Detector construction class to define materials and geometry.
/// This class defines a world volume and a mother volume containing replicated daughter detectors.
/// 
/// The world volume is a box of specified dimensions. The mother volume contains
/// daughter detectors arranged in a grid using G4Replica. The daughter detectors are made of silicon.
class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    ~DetectorConstruction() override;

public:
    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;

    // Get methods
    const G4VPhysicalVolume* GetMotherPV() const;
    const G4VPhysicalVolume* GetDaughterPV() const;

private:
    // Methods
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    // Data members
    static G4ThreadLocal G4GlobalMagFieldMessenger* fMagFieldMessenger; // magnetic field messenger

    G4VPhysicalVolume* fMotherPV = nullptr; // the mother physical volume
    G4VPhysicalVolume* fDaughterPV = nullptr; // the daughter physical volume

    G4bool fCheckOverlaps = true; // option to activate checking of volumes overlaps
};

// Inline functions
inline const G4VPhysicalVolume* DetectorConstruction::GetMotherPV() const {
    return fMotherPV;
}

inline const G4VPhysicalVolume* DetectorConstruction::GetDaughterPV() const {
    return fDaughterPV;
}

}

#endif

