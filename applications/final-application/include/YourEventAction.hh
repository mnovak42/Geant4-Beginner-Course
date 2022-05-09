
#ifndef YOUREVENTACTION_HH
#define YOUREVENTACTION_HH

#include "G4UserEventAction.hh"

#include "globals.hh"

/**
 * @file    YourEventAction.hh
 * @class   YourEventAction
 * @author  M. Novak
 * @date    December 2019
 *
 * Implementation of the ``Geant4`` ``G4UserEventAction`` **optional interface** for this user application.
 *
 * This interface gives the possibility for interacting with the simulation before
 * (BeginOfEventAction()) and after (EndOfEventAction()) the simulation of each event.
 *
 */

class YourEventAction : public G4UserEventAction {

  // Method declaration:
  public:

    // CTR:
    YourEventAction();
    ~YourEventAction() override;

    /**
     * Virtial method that is called by the RunManager before the start of each event.
     *
     * This is the point where we usually reset some local variables that are used to accumulate
     * information during the simnulation of a given event.
     *
     * @param[in] evt Pointer to the ``G4Event`` object that will be simulated now.
     */
    void BeginOfEventAction(const G4Event* evt) override;

    /**
     * Virtial method that is called by the RunManager after the end of each event.
     *
     * This is the point where we usually propagate to upper level (i.e. usualy to the run (YourRun) obejct)
     * local infomation, that has been collected during the simnulation of a given event.
     *
     * @param[in] evt Pointer to the ``G4Event`` object that simulated has just been completed.
     */
    void EndOfEventAction(const G4Event* evt) override;


    //
    // Additional custom methods:


    // Public method (used by the SteppingAction) to add energy deposit and
    // charged particle track length information to this object after each step.
    void AddEnergyDepositPerStep(const G4double edepAlongTheStep) {
        fEdepPerEvt += edepAlongTheStep;
    }
    void AddChargedTrackLengthPerStep(const G4double trackLAlongTheStep) {
      fChTrackLengthPerEvt += trackLAlongTheStep;
    }

  // Data member declarations:
  private:

    G4double   fEdepPerEvt;
    G4double   fChTrackLengthPerEvt;

};

#endif
