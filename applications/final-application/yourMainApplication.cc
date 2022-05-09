


// Inlcude global-definitions: G4GlobalConfig.hh contains information on the
// Geant4 build in form of variable definitions e.g. G4MULTITHREADED variable
// will be defined in this header only in case of Geant4-MT.
// One can also include "globals.hh" instead that will include G4GlobalConfig.hh
//#include "G4GlobalConfig.hh"
#include "globals.hh"

// This will be used to create the RunManager
#include "G4RunManagerFactory.hh"

// Your detector construction and user action initialization
#include "YourDetectorConstruction.hh"
#include "YourActionInitialization.hh"

// To be able to use and combine the refrence physics lists
#include "G4PhysListFactory.hh"
#include "G4ThermalNeutrons.hh"

// For the UI manager (to expecute the G4 macro input file)
#include "G4UImanager.hh"

// For VIS and/or UI-session
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

/**
 * @file     yourMainApplication.cc
 * @author   M. Novak
 * @date     December 2019
 *
 * The main function of this user application.
 *
 */

/** The `main` function of the user application. */
int main(int argc, char** argv) {
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
      // If you want to specifty the UI-session type i.e. qt, csh, tcsh, etc.
      // the one with higher priority will be used otherwise and GUI (e.g. qt)
      // has higher prioriy compared to terminals.
      // ui = new G4UIExecutive(argc, argv, "tcsh");
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
    const G4String plName = "FTFP_BERT_EMZ";
    G4PhysListFactory plFactory;
    G4VModularPhysicsList *pl = plFactory.GetReferencePhysList( plName );
    runManager->SetUserInitialization( pl );
    //
    // 3. ActionInitialization = YourActionInitialization <- G4VUserActionInitialization
    //    (and YourActionInitialization contains YourPrimaryGeneratorAction which is
    //     <- G4VUserPrimaryGeneratorActions)
    //    Note, that:
    //     - all other UserActions (Run, Event, Stepping, Tracking, Stacking) are optional !
    //     - the DetectorConstruction pointer is propagated down to the UserActions
    //       because some actions (e.g. PrimaryGenerator) needs information from the detector.
    runManager->SetUserInitialization( new YourActionInitialization( detector ) );


    //
    // Initialize the RunManager and exeute 10 events
//    runManager->Initialize();
//    runManager->BeamOn(10);


    //
    // Add visualization:
    // - create a G4VisExecutive object as the Visualization Manager
    // - initialize the Visualization Manager (will handle all vis components)
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    //
    // Get the pointer to the User Interface manager.
    G4UImanager* UI = G4UImanager::GetUIpointer();
    // Then either:
    // - batch mode: process the macro file
    // - interactive mode: create ui-session
    if ( ! ui ) {
      // batch mode
      G4String command  = "/control/execute ";
      UI->ApplyCommand( command + macrofile );
      G4cerr << "  == Here we are after the batch execution! " << G4endl;
    } else {
      // interactive mode
      ui->SessionStart();
      G4cerr << "  == Here we are after the ui-session termination! " << G4endl;
      delete ui;
    }

    //
    // delete the Visualization Manger
    delete visManager;

    //
    // At the end delete the RunManager
    delete runManager;
  return 0;
}
