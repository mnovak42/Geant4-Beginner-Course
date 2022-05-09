
#ifndef YOURPRIMARYGENERATORACTION_HH
#define YOURPRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "globals.hh"

// forward declaration
class YourDetectorConstruction;
class G4ParticleGun;
class G4Event;
class G4String;

/**
 * @file    YourPrimaryGeneratorAction.hh
 * @class   YourPrimaryGeneratorAction
 * @author  M. Novak
 * @date    December 2019
 *
 * Implementation of the ``Geant4`` ``G4VUserPrimaryGeneratorAction`` **mandatory
 * interface** for this user application.
 *
 * Generation of primary particles of the application must be implemented in
 * the GeneratePrimaries() interface. This interface method is invoked by the
 * G4RunManager::GenerateEvent() whenever a new event is needed.
 *
 * The construction and registration of the primary generator interface of the
 * application is done in the implementation of the **mandatory**
 * G4VUserActionInitialization (YourActionInitialization).
 *
 * An instance of this primary generator object **must be** created and set in
 * the implementation of the G4VUserActionInitialization::Build() interface method.
 * This is done in YourActionInitialization::Build() in this application.
 *
 * @note  each worker thread has their own object form this primary generator
 *        since YourActionInitialization::Build() interface method is invoked by
 *        each thread.
 *
 * @note  we keep the pointer to the detector object in order to be able to set
 *        the primary generator gun position dynamically. This can be done anytime
 *        by invoking the UpdatePosition() method.
 */


class YourPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {

  // Method declaration:
  public:

    // CTR & DTR
    YourPrimaryGeneratorAction(YourDetectorConstruction* det);
    ~YourPrimaryGeneratorAction() override;

    /**
     * It's interface method to generate primary particles.
     *
     * (Pure) virtual method to generata primary events. This method will be
     * invoked from the G4RunManager whenever a new event is required.
     *
     * @param [in:out] evt Pointer to the ``G4Event`` object to be filled with primaries.
     */
    void   GeneratePrimaries(G4Event* evt) override;

    //
    // Additional custom methods:

    // Public method to obtain the G4ParticleGun object pointer and some other
    // primary particle realted values
    G4ParticleGun*  GetParticleGun() { return fParticleGun; }

    // Public method to get the primary particle name.
    const G4String& GetParticleName() const;

    // Public method to get the primary particle kinetic energy.
    G4double        GetParticleEnergy() const;

    // Public method to set the default primary particle kinematics
    void            SetDefaultKinematic();

    /**
     * Public method to set the position of the particle gun.
     *
     * The detector might be resized by the user between its construction and the
     * start of the run. This method can be invoked (form YourRunAction::BeginOfRunAction())
     * at the begin of the run in order to ensure the proper position of the gun.
     */
    void            UpdatePosition();


  // Data member declarations:
  private:

    YourDetectorConstruction* fYourDetector;

    G4ParticleGun*            fParticleGun;

};

#endif
