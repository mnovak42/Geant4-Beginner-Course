
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

// BC.
// For the UI manager (to expecute the G4 macro input file)
#include "G4UImanager.hh"
// For the Interaction User Interface session i.e. for interactive command line
// ABC.
// executions
#include "G4UIExecutive.hh"


// C.
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"

int main(int argc, char** argv) {
//
// BC. NOTE: order is because of the visualisation and other managers...
    // Interactive OR batch mode? Check the inputs:
    // - if no arguments i.e. argc = 1 (i.e. no macro file)
    //    => interactive mode: create G4UIExecutive i.e. UI session for interactive
    //                         command executions
    // - if argument is given i.e. argc = 2 (i.e. macro file)
    //    => batch mode: macro file will be processed by the G4UImanager
    //                   (the UI manager can execute commands given as string
    //                    by its ApplyCommand method)
    G4String macrofile = "";
    G4UIExecutive* ui  = nullptr;
    if ( argc == 1 ) {
//      ui = new G4UIExecutive(argc, argv, "tcsh");
      ui = new G4UIExecutive(argc, argv);
    } else {
      macrofile = argv[1];
    }

    //
    // Construct the RunManager
    auto* runManager = G4RunManagerFactory::CreateRunManager();
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
    // - create a G4 User Interface session for interactive control i.e.
    //   User Interface command executions
    G4cout << "  ====== Simulation Session STARTED ====== " << G4endl;

//
// C.
    //
    // Add visualization:
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

//
// BC.
    //
    // Get the pointer to the User Interface manager.
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    // Then either:
    // - batch mode: process the macro file
    // - interactive mode: create ui-session
    if ( ! ui ) {
      // batch mode
      G4String command  = "/control/execute ";
      UImanager->ApplyCommand( command + macrofile );
      G4cerr << "  == Here we are after the batch execution! " << G4endl;
    } else {
      // interactive mode
      ui->SessionStart();
      G4cerr << "  == Here we are after the ui-session termination! " << G4endl;
      delete ui;
    }


    G4cout << "  ====== Simulation FINISHED ====== " << G4endl;

    //
    // At the end delete the RunManager and the visManager
    delete visManager;
    delete runManager;

   return 0;
}
