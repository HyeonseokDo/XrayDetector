#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "DetectorConstruction.hh"

namespace XrayDetector {

class ActionInitialization : public G4VUserActionInitialization {
public:
    ActionInitialization(const DetectorConstruction* detConstruction);
    virtual ~ActionInitialization();

    virtual void BuildForMaster() const override;
    virtual void Build() const override;

private:
    const DetectorConstruction* fDetConstruction;
};

}

#endif // ACTIONINITIALIZATION_HH
