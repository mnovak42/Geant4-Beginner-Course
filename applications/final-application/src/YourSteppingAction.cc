
#include "YourSteppingAction.hh"

#include "YourDetectorConstruction.hh"
#include "YourEventAction.hh"

#include "G4Step.hh"


YourSteppingAction::YourSteppingAction(YourDetectorConstruction* det, YourEventAction* evtAction)
:   G4UserSteppingAction(),
    fYourDetector(det),
    fYourEventAction(evtAction) { }


YourSteppingAction::~YourSteppingAction() {}


//
// Score only if the step was done in the Target:
//  - cllect energy deposit for the mean (per-event) energy deposit computation
//  - same for the charged particle track length
void YourSteppingAction::UserSteppingAction(const G4Step* theStep) {
  // Score steps done only in the target: i.e. pre-step point was in target
  if (theStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()
    != fYourDetector->GetTargetPhysicalVolume() )  return;
  // Step was done inside the Target so do scoring:
  //
    // Get the energy deposit and the step length
    const G4double eDep   = theStep->GetTotalEnergyDeposit();
    const G4double trackL = theStep->GetStepLength();
    // Get the G4Track and the ParticleDefinition to see if the particle is charged
  const G4ParticleDefinition* pDef = theStep->GetTrack()->GetParticleDefinition();
    if ( pDef->GetPDGCharge() != 0.0 ) {
      // add current step length to the charged particle track length per-event
      fYourEventAction->AddChargedTrackLengthPerStep( trackL );
    }
    // add current energy deposit to the charged particle track length per-event
    fYourEventAction->AddEnergyDepositPerStep( eDep );
}
