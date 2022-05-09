
#ifndef YOURACTIONINITIALIZATION_HH
#define YOURACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"


// forward declarations
class YourDetectorConstruction;

/**
 * @file    YourActionInitialization.hh
 * @class   YourActionInitialization
 * @author  M. Novak
 * @date    December 2019
 *
 * Implementation of the ``Geant4`` ``G4VUserActionInitialization`` **mandatory
 * interface** for this user application.
 *
 * All user actions (i.e. at least your implementation of the ``G4VUserPrimaryGeneratorAction``
 * ,that is YourPrimaryGeneratorAction in our case, but all optional actions) objects must
 * be constructed and registered in the ``G4RunManager`` through a single user action initialization
 * object from this class.
 *
 * The *construction* and *registration* of all user action objects must be implemented
 * in the Build() interface (pure virtual) method that is invoked by all worker threads before starting the run.
 * The additional BuildForMaster() virtual method of the base class is invoked by only the master thread. No other user
 * actions than implementation of the ``G4UserRunAction`` should be constructed here!
 *
 * According to the above, we construct and register only YourRunAction object in the BuildForMaster() interface method
 * while all the user actions are constructed and created in the Build() method. This is because, the master run action object
 * YourRunAction::GenerateRun() method is invoked by the master at the beginning of the run to create its own YourRun object.
 * The same is done for each workers. Hoever, unlike the individual worker YourRun objects, that are used during the simulatio to
 * collect thread-local infomation, the single master YourRun object is untouched till the end of the run. It will be used only
 * to collect/merge the individual thread-local run infomation into one global YourRun obejct after all worker finished the simulation.
 *
 */

class YourActionInitialization : public G4VUserActionInitialization {

  // Method declaration:
  public:

    // CTR & DTR (you will need to talk to your detector to find out the GUN pos.)
    YourActionInitialization(YourDetectorConstruction* det);
    ~YourActionInitialization() override;

    /**
     * (Pure) Virtual method to be implemented by the user to instantiate
     * User Action class objects.
     *
     * Each application **must implemnted** this method. It is invoked by all workers
     * at the beginning of the run to instantiate all (worker) thread-local user action
     * objects. At least the construction and registration of the primary generation action
     * must be implemented in this method.
     */
    void Build() const override;

    /**
     * Virtual method to be implemented by the user to instantiate User RunAction
     *
     * This method is invoked only by the master and only your implementation of
     * the `G4VUserRunAction` should be constructed and registered here (see the
     * class description why).
     */
    void BuildForMaster() const override;


  // Data member declarations:
  private:

    YourDetectorConstruction* fYourDetector;
};

#endif
