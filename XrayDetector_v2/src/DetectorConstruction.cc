#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"

namespace XrayDetector {

G4ThreadLocal G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = nullptr;

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  fMotherPV(nullptr),
  fDaughterPV(nullptr)
{
  DefineMaterials();
}

DetectorConstruction::~DetectorConstruction()
{ }

void DetectorConstruction::DefineMaterials(){
    auto nistManager = G4NistManager::Instance();
    nistManager->FindOrBuildMaterial("G4_Galactic");
    nistManager->FindOrBuildMaterial("G4_Si");//G4_Si
}

G4VPhysicalVolume* DetectorConstruction::Construct(){
    return DefineVolumes();
}

G4VPhysicalVolume* DetectorConstruction::DefineVolumes(){
    // Define materials
    auto nistManager = G4NistManager::Instance();
    G4Material* galactic = nistManager->FindOrBuildMaterial("G4_Galactic");
    G4Material* silicon = nistManager->FindOrBuildMaterial("G4_Si");//G4_Si

    // World volume
    G4double worldSizeX = 2 * cm;
    G4double worldSizeY = 6 * cm;
    G4double worldSizeZ = 20 * cm;
    G4Box* worldS = new G4Box("World", worldSizeX / 2, worldSizeY / 2, worldSizeZ / 2);
    G4LogicalVolume* worldLV = new G4LogicalVolume(worldS, galactic, "World");
    G4VPhysicalVolume* worldPV = new G4PVPlacement(
        nullptr,
        G4ThreeVector(0, 0, 0 * cm), // the center of the world volume should be (0,0,0)
        worldLV,
        "World",
        nullptr,
        false,
        0,
        fCheckOverlaps
    );

    // Mother volume
    G4double motherSizeX = 4.1 * mm;
    G4double motherSizeY = 2.1 * cm;
    G4double motherSizeZ = 7.5 * cm;
    G4Box* motherS = new G4Box("Mother", motherSizeX / 2, motherSizeY / 2, motherSizeZ / 2);
    G4LogicalVolume* motherLV = new G4LogicalVolume(motherS, galactic, "Mother");
    fMotherPV = new G4PVPlacement(
        nullptr,
        G4ThreeVector(0, 0, 0),
        motherLV,
        "Mother",
        worldLV,
        false,
        0,
        fCheckOverlaps
    );

    // Daughter detector
    G4double daughterSizeX = 0.01 * cm;
    G4double daughterSizeY = 0.1 * cm;
    G4double daughterSizeZ = 7.5 * cm;
    G4Box* daughterS = new G4Box("Silicon", daughterSizeX / 2, daughterSizeY / 2, daughterSizeZ / 2);
    G4LogicalVolume* daughterLV = new G4LogicalVolume(daughterS, silicon, "Silicon");//silicon

    // Place daughter detectors within the mother volume using for loops
    G4int numDaughtersX = 41;
    G4int numDaughtersY = 21;
    for (G4int ix = 0; ix < numDaughtersX; ++ix) {
        for (G4int iy = 0; iy < numDaughtersY; ++iy) {
            G4double posX = -motherSizeX/2 + (ix + 0.5) * daughterSizeX;
            G4double posY = -motherSizeY/2 + (iy + 0.5) * daughterSizeY;
            new G4PVPlacement(
                nullptr,
                G4ThreeVector(posX, posY, 0),
                daughterLV,
                "Silicon",
                motherLV,
                false,
                ix * numDaughtersY + iy,
                fCheckOverlaps
            );
        }
    }

    // Visualization attributes
    worldLV->SetVisAttributes(G4VisAttributes::GetInvisible());
    G4VisAttributes* motherVisAttr = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0));
    motherVisAttr->SetVisibility(true);
    motherLV->SetVisAttributes(motherVisAttr);

    G4VisAttributes* daughterVisAttr = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    daughterVisAttr->SetVisibility(true);
    daughterLV->SetVisAttributes(daughterVisAttr);

    return worldPV;
}

void DetectorConstruction::ConstructSDandField(){
    // Add sensitive detectors and fields here if needed
}

} // namespace XrayDetector
