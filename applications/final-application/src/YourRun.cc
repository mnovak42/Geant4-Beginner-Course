
#include "YourRun.hh"

#include "YourDetectorConstruction.hh"
#include "YourPrimaryGeneratorAction.hh"

#include "G4Material.hh"

YourRun::YourRun(YourDetectorConstruction* det, YourPrimaryGeneratorAction* prim)
:   G4Run(),
    fYourDetector(det),
    fYourPrimary(prim) {
    // init data members
    fEdepInTarget                = 0.0;
    fEdepInTarget2               = 0.0;

    fChargedTrackLengthInTarget  = 0.0;
    fChargedTrackLengthInTarget2 = 0.0;

    // Energy deposit histogram with default paraneters. 
    // Note: all properties can be set from UI command (our pwn UI command is
    // /yourApp/runAction/edepHisto ... see YourRunActionMessenger) and will be
    // updated in YourRunAction::BeginOfRunAction method. Invoking this UI
    // command (in the g4 macro file) activates this energy deposit histogram
    // that stays inactive (not used) otherwise.
    //
    fIsActiveEdepHistogram = false;
    fEdepHistogram = new Hist("Hist_Edep.dat", 0.0, 10.0*CLHEP::keV, 100);
}


YourRun::~YourRun() {
  // free the memoery that was allocated dynamically (i.e. our histogram object)
  delete fEdepHistogram;
}

// This method will be called by the master RunManager by passing each theard
// local run (YourRun) pointers as argument. Therefore, here you define how to
// merge each thread local Run global data structures (all thread local Run-s
// will be merged to the master Run data).
void YourRun::Merge(const G4Run* run) {
  // Cast the (theard local) G4Run (base) pointer to YourRun pointer (it will
  // be YourRun since the RunManager will call YourRunAction::GenerateRun
  // interface method to generate the Run-s)
  const YourRun* localRun = static_cast<const YourRun*>(run);
  //
  // Then you can define how to sum up the individual YourRun data members
  fEdepInTarget                += localRun->fEdepInTarget;
  fEdepInTarget2               += localRun->fEdepInTarget2;

  fChargedTrackLengthInTarget  += localRun->fChargedTrackLengthInTarget;
  fChargedTrackLengthInTarget2 += localRun->fChargedTrackLengthInTarget2;

  // add our histograms: note, since the Hist object is not a primitive type,
  // the addition of such objects needs to be defined (see the Hist::Add()
  // method for more details).
  if (fIsActiveEdepHistogram) {
    fEdepHistogram->Add(localRun->fEdepHistogram);
  }

  // This is just to have one PrimaryGeneratorAction object at the end (because)
  // here we are merging the worker threads run objects into the master thread
  // run object but the master's RunAction do not have the PrimaryGenerator set.)
  fYourPrimary = localRun->fYourPrimary;

  // Call the base class Merge method at the end to merge the base class members
  G4Run::Merge(run);
}

// Called only for the Master's RunAction at the end after all thread local runs
// have been merged.
void  YourRun::EndOfRunSummary() {
    // Get number of events simulated from the base G4Run object (number of
    // events processed by each worker thread has already been merged at the end
    // of the Merge method when calling the base class Merge method).
    const G4int    nEvt = GetNumberOfEvent();
    if (nEvt == 0) return;
    const G4double norm = 1.0/nEvt;

    //
    // Compute mean energy deposit in target per event and its rms
    fEdepInTarget    *= norm;
    fEdepInTarget2   *= norm;
    G4double rmsEdep  = fEdepInTarget2 - fEdepInTarget*fEdepInTarget;
    rmsEdep = ( rmsEdep > 0. ) ? std::sqrt( rmsEdep*norm ) : 0.;
    //
    // Compute mean charged particle track length in target per event and its rms
    fChargedTrackLengthInTarget    *= norm;
    fChargedTrackLengthInTarget2   *= norm;
    G4double rmsChTr  = fChargedTrackLengthInTarget2
                      - fChargedTrackLengthInTarget * fChargedTrackLengthInTarget;
    rmsChTr = ( rmsChTr > 0. ) ? std::sqrt( rmsChTr*norm ) : 0.;

    //
    // Print out the information
    G4String primInfo = std::to_string( nEvt ) + " E = ";
    primInfo += std::to_string( fYourPrimary->GetParticleEnergy() ) + " [MeV] ";
    primInfo += fYourPrimary->GetParticleName() + "\n";

    G4cout<< "\n\n" << G4endl;
    G4cout<< "\n =================================  Run Summary ================================= \n"
          << " Target thickness    : " << fYourDetector->GetTargetThickness()/CLHEP::cm << " [cm] \n"
          << " Target material info: " << "                                 \n"
          <<  fYourDetector->GetTargetMaterial() << "\n"
          << " Primary particle: " << primInfo
          << " -------------------------------------------------------------------------------- \n"
          << " Mean energy deposit in target               : "
          << fEdepInTarget << " +- " << rmsEdep << " [MeV] \n"
          << " Mean charged particle track length in target: "
          << fChargedTrackLengthInTarget << " +- " << rmsChTr << " [mm] \n"
          << " ================================================================================ \n"
          << G4endl;
    G4cout<< "\n\n" << G4endl;

    // write the energy deposit histogram to file (ask normalization i.e. 'true')
    if (fIsActiveEdepHistogram) {
      fEdepHistogram->WriteToFile(true);
    }

}
