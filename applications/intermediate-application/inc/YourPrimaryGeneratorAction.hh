
// The G4ParticleGun object will be used to produce primary events:
// - containing a single primary particle with a well defined type,
//   kinetic energy and direction (default: E = 30 MeV e- to the [1,0,0] dir.)

#ifndef YOURPRIMARYGENERATORACTION_HH
#define YOURPRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "globals.hh"

// forward declaration
class YourDetectorConstruction;
class G4ParticleGun;
class G4Event;
class G4String;


class YourPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {

  // Method declaration:
  public:

    // CTR & DTR
    YourPrimaryGeneratorAction(YourDetectorConstruction* det);
    virtual ~YourPrimaryGeneratorAction();

    // (Pure) virtual method to generata primary events
    virtual void   GeneratePrimaries(G4Event*);

    //
    // Additional custom methods:

    // Public method to set the default properties for the G4ParticleGun
    void            SetDefaultKinematic();

    // Public method to set the position of the particle gun: will be taken for
    // the actual detector construction (we will dicusse this shortly)
    void            UpdatePosition();

 /*
    // Public method to get the primary particle name (for the final printout).
    const G4String& GetParticleName() const;

    // Public method to get the primary particle kinetic energy (for the final printout).
    G4double        GetParticleEnergy() const;
*/

  // Data member declarations:
  private:

    // a pointer to the detector construction object (will be set trhough the CTR)
  	YourDetectorConstruction* fYourDetector;

    // the particle gun object of the class
    G4ParticleGun*            fParticleGun;


};

#endif
