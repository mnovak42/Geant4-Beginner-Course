// A UI messenger class that implements our own UI commands to manipulate some
// properties (thickness, material) of the detector Target. An object from this
// class must be created and stored in the coresponding YourDetectorConstruction
// object on which the implemented/defined commands will act.
#ifndef YOURDETECTORMESSENGER_HH
#define YOURDETECTORMESSENGER_HH

#include "G4UImessenger.hh"

// forward declarations
class YourDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4String;

class YourDetectorMessenger : public G4UImessenger {

  // Method declaration:
  public:

    // CTR & DTR
    YourDetectorMessenger(YourDetectorConstruction* det);
   ~YourDetectorMessenger();

    void SetNewValue(G4UIcommand*, G4String) override;


  // Data member declarations
  private:

    YourDetectorConstruction*  fYourDetector;

    G4UIdirectory*             fDirCMD;
    G4UIcmdWithADoubleAndUnit* fTargetThicknessCMD;
    G4UIcmdWithAString*        fTargetMaterialCMD;

};

#endif
