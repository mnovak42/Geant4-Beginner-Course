
#include "YourEventAction.hh"

#include "G4RunManager.hh"
#include "YourRun.hh"

YourEventAction::YourEventAction()
: G4UserEventAction(),
  fEdepPerEvt(0.0),
  fChTrackLengthPerEvt(0.0) {}


YourEventAction::~YourEventAction() {}


// Beore each event: reset per-event variables
void YourEventAction::BeginOfEventAction(const G4Event* /*anEvent*/) {
  fEdepPerEvt           = 0.0;
  fChTrackLengthPerEvt  = 0.0;
}


// After each event:
// fill the data collected for this event into the Run global (thread local)
// data Run data object (i.e. into YourRun)
void YourEventAction::EndOfEventAction(const G4Event* /*anEvent*/) {
  // get the current Run object and cast it to YourRun (because for sure this is its type)
  YourRun* currentRun = static_cast< YourRun* > ( G4RunManager::GetRunManager()->GetNonConstCurrentRun() );
    // add the quantities to the (thread local) run global YourRun object
    currentRun->AddEnergyDepositPerEvent( fEdepPerEvt );
    currentRun->AddChTrackLengthPerEvent( fChTrackLengthPerEvt );
    currentRun->FillEdepHistogram( fEdepPerEvt );
}
