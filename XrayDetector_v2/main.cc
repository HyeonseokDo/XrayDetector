#include "G4Types.hh"
#include "G4RunManagerFactory.hh"
//#include "G4SteppingVerbose.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4AnalysisManager.hh"
//#include "G4TScoreNtupleWriter.hh"

#include "DetectorConstruction.hh"
#include "FTFP_BERT.hh"

#include <iostream>
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char** argv)
{
    // Detect interactive mode (if no arguments) and define UI session
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    // Optionally: choose a different Random engine...
    // G4Random::setTheEngine(new CLHEP::MTwistEngine);

    // Use G4SteppingVerboseWithUnits
//    G4int precision = 4;
//    G4SteppingVerbose::UseBestUnit(precision);

    // Construct the default run manager
    auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);//Default

    // Set mandatory initialization classes
    runManager->SetUserInitialization(new FTFP_BERT);

	auto detConstruction = new XrayDetector::DetectorConstruction();
    runManager->SetUserInitialization(detConstruction);

    // Set user action initialization
//    runManager->SetUserInitialization(new XrayDetector::ActionInitialization());
	
	auto actionInitialization = new XrayDetector::ActionInitialization(detConstruction);
	runManager->SetUserInitialization(actionInitialization);
	

    // Initialize visualization
    auto visManager = new G4VisExecutive;
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    auto UImanager = G4UImanager::GetUIpointer();
	
	G4RunManager::GetRunManager()->SetNumberOfThreads(1);

    // Activate score ntuple writer
//    G4TScoreNtupleWriter<G4AnalysisManager> scoreNtupleWriter;
//    scoreNtupleWriter.SetVerboseLevel(1);
//    scoreNtupleWriter.SetNtupleMerging(true);

    // Process macro or start UI session
    if (!ui) {
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
		std::cout<<"mode1"<<std::endl;
    } else {
        // interactive mode
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
		std::cout<<"mode2"<<std::endl;
        delete ui;
    }

    // Job termination
    delete visManager;
    delete runManager;

    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

