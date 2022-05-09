
#ifndef YOURRUNACTION_HH
#define YOURRUNACTION_HH

#include "G4UserRunAction.hh"

#include "G4String.hh"

// forward declarations
class YourDetectorConstruction;
class YourPrimaryGeneratorAction;
class YourRun;
class G4Run;
class YourRunActionMessenger;

/**
 * @file    YourRunAction.hh
 * @class   YourRunAction
 * @author  M. Novak
 * @date    December 2019
 *
 * Implementation of the ``Geant4`` ``G4UserRunAction`` **optional interface** for this user application.
 *
 * This interface gives the possibility for interacting with the simulation before
 * the simulation of the first (BeginOfRunAction()) and after the last (EndOfRunAction()) event.
 * The additional GenerateRun() virtual method can be used to generate YourRun object, i.e.
 * your implementation of `G4Run`, both for the master and for the individual worker threads.
 *
 * @note this is the only user action that can be constructed and registered in YourActionInitialization::BuildForMaster().
 *
 *
 */


class YourRunAction : public G4UserRunAction {

  // Method declaration:
  public:

    // CTR:
    //  - detector construction object is used in the stepping action to check target
    //  - primary generator is used to re-set position for workers and to get E0 (set only for workers)
    YourRunAction(YourDetectorConstruction* det, YourPrimaryGeneratorAction* prim = nullptr);
    virtual ~YourRunAction();


    /** Virtual method to generate YourRun for each threads.*/
    G4Run* GenerateRun() override;

    /**
     * Virtial method that is called by the RunManager before the first event starts.
     *
     * This is the point where we usually perfrom some final actions needed to be done
     * before the simulation, constructing some run global objects (e.g. for analysis)
     * or we will ensure here that the primary generator gun position is correct.
     *
     * @param[in] run Pointer to the G4Run (YourRun) object that has been generated for
     *                this thread.
     */
    void   BeginOfRunAction(const G4Run* run) override;

    /**
     * Virtial method that is called by the RunManager after the last event simulation is completed.
     *
     * This is the point where we usually perfrom some actions needed to be done
     * when the simulation is completed, performing final computation and writing the
     * simulation results usually happens here (we do this here by calling the corresponding
     * method of YourRun).
     *
     * @param[in] run Pointer to the G4Run (YourRun) object that has been generated for
     *                this thread.
     */
    void   EndOfRunAction(const G4Run* run) override;

    // Public method to activate and set properties to the energy deposit histogram
    // member of YourRun object(s). Note, that YourRun objects will be created
    // when the G4RunManager(s) and G4MTRunManager invokes the GenerateRun() method
    // of their thraed local object of this RunAction class. Since these YourRun
    // objects, together with their Energy-deposit histogram members, will be
    // available only after that point, we need to keep all the histogram
    // properties here, in the RunAction class, that is available before (see more
    // below at the fMessenger declaration) and propagate all proprties to the
    // Energy deposit histogram member of YourRun in the BeginOfRunAction when
    // all those objects are already available.
    void SetEdepHistogram(const G4String& filename, G4double emin, G4double emax,
                          G4int numbins) {
        fIsEdepHistogramUICmdInvoked = true;
        fEdepHistFileName  = filename;
        fEdepHistMinEnergy = emin;
        fEdepHistMaxEnergy = emax;
        fEdepHistNumBins   = numbins;
    }


  // Data member declarations:
  private:

    YourDetectorConstruction*    fYourDetector;

    YourPrimaryGeneratorAction*  fYourPrimary;

    YourRun*                     fYourRun;

    // Store Edep-Histogram properties of YourRun here and reset at the begining
    // of the run.
    //
    // Note, that YourRun object is not available before the GenerateRun method
    // of this YourRunAction is invoked by the G4RunManager or G4MTRunManager.
    // On the same time, one YourRunAction object is created immediately when the
    // ActionInitialization is registered in the RunManager (in the main) by
    // calling immediately either the ActionInitialization::BuildForMaster (in
    // case of MT Geant4) or ActionInitialization::Build (in case of sequential
    // Geant4) interface method.
    // Therefore, we need to communicate (by UI command) the histogram information
    // to and store in the RunAction object. Then all the information will be used
    // to update the corresponding histogram in the BeginOfRunAction method when
    // YourRun object(s) is(are) already available(created) together with their
    // histogram objects.
    YourRunActionMessenger*     fMessenger;

    // See the description at the SetEdepHistogram method above.
    G4bool      fIsEdepHistogramUICmdInvoked;
    G4String    fEdepHistFileName;
    G4double    fEdepHistMinEnergy;
    G4double    fEdepHistMaxEnergy;
    G4int       fEdepHistNumBins;

};

#endif
