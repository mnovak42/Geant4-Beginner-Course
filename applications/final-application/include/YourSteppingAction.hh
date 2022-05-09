
#ifndef YOURSTEPPINGACTION_HH
#define YOURSTEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

// forward declarations
class YourDetectorConstruction;
class YourEventAction;
class G4VPhysicalVolume;

/**
 * @file    YourSteppingAction.hh
 * @class   YourSteppingAction
 * @author  M. Novak
 * @date    December 2019
 *
 * Implementation of the ``Geant4`` ``G4UserSteppingAction`` **optional interface** for this user application.
 *
 * This interface gives the possibility for interacting with the simulation after
 * the complition of the individual simulation steps in its UserSteppingAction() method.
 *
 */

class YourSteppingAction : public G4UserSteppingAction {

  // Method declaration:
  public:

    // CTR:
    //  - detector construction object is used to find out the target volume
    //  - event action is used to fill per-event cumulative values
    YourSteppingAction(YourDetectorConstruction* det, YourEventAction* evtAction);
    ~YourSteppingAction() override;

    /**
     * Interface metho dthat is called after each simulation steps.
     *
     * We do all the fine grane infomation collection in this method that infomation
     * are usually propagated to an auuper elevel, e.g. YourEventAction.
     *
     * @param [in] step Pointer to the ``G4Step`` object that has just been completed.
     *
     * @warning You need to be careful here! Since this method is invoked after each individual simulation step, this is a very perfomance critical point.
     */
    void UserSteppingAction(const G4Step* step) override;



  // Data member declarations:
  private:

    YourDetectorConstruction*    fYourDetector;

    YourEventAction*             fYourEventAction;
};

#endif
