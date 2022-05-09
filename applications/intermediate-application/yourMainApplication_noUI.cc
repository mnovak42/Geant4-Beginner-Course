
// Inlcude global-definitions (information on the Geant4 build)
//#include "G4GlobalConfig.hh"
#include "globals.hh"

// This will be used to create the RunManager
#include "G4RunManagerFactory.hh"

// Your detector construction and user action initialization
#include "YourDetectorConstruction.hh"
#include "YourActionInitialization.hh"

// To select and use a refrence physics list
#include "G4PhysListFactory.hh"

// For the UI manager (to expecute the G4 macro input file)
// (ONLY for the traking verbose to see that something happens)
//#include "G4UImanager.hh"


int main(/*int argc, char** argv*/) {
    //
    // Construct the RunManager (build configuration dependent RM)
    auto* runManager = G4RunManagerFactory::CreateRunManager();

// (ONLY for the traking verbose to see that something happens)
//runManager->SetNumberOfThreads(1);

    //
    // Set (MANDATORY) User initialization classes:
    //  = 1. G4VUserDetectorConstruction
    //  = 2. G4VUserPhysicsList
    //  = 3. G4VUserActionInitialization (that contains G4VUserPrimaryGeneratorAction)
    //
    // 1. DetectorConstruction = YourDetectorConstruction <- G4VUserDetectorConstruction
    YourDetectorConstruction* detector = new YourDetectorConstruction;
    runManager->SetUserInitialization( detector );
    //
    // 2. PhysicsList = G4VModularPhysicsList <- G4VUserPhysicsList
    //    (use reference physics list through the G4PhysListFactory)
    const G4String plName = "FTFP_BERT";
    G4PhysListFactory plFactory;
//    plFactory.SetVerbose(0);
    G4VModularPhysicsList *pl = plFactory.GetReferencePhysList( plName );
    runManager->SetUserInitialization( pl );
    //
    // 3. ActionInitialization = YourActionInitialization <- G4VUserActionInitialization
    //    (and YourActionInitialization contains YourPrimaryGeneratorAction which is
    //     <- G4VUserPrimaryGeneratorActions)
    //    Note, that:
    //     - all other UserActions (Run, Event, Stepping, Tracking, Stacking) are optional !
    //     - the DetectorConstruction pointer is propagated to the UserActions
    //       because some actions (e.g. PrimaryGenerator) needs information from the detector.
    runManager->SetUserInitialization( new YourActionInitialization( detector ) );

    //
    // After creating and registering all mandatory objects:
    // - initialize the RunManager and execute 10 events (whatever primary venet
    //   is defined in YourPrimaryGeneratorAction, on whatever target defined in
    //   YourDetectorConstruction with whatever physics is defined in physics
    //   list registered to the RunManager)
    runManager->Initialize();
    // !! Update gun position: Construct() method needs to be called to set the
    //    proper position of the gun !!!

// (ONLY for the traking verbose to see that something happens)
//get the pointer to the User Interface manager
//G4UImanager* UImanager = G4UImanager::GetUIpointer();
//UImanager->ApplyCommand("/tracking/verbose 1");


    // Execute 10 events
    runManager->BeamOn(10);
    G4cout << "  ====== Simulation FINISHED ====== " << G4endl;

    //
    // At the end delete the RunManager
    delete runManager;

	return 0;
}
