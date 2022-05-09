
#ifndef YOURRUNACTIONMESSENGER_HH
#define YOURRUNACTIONMESSENGER_HH

#include "G4UImessenger.hh"

// forward declarations
class YourRunAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4String;

class YourRunActionMessenger : public G4UImessenger {

  // Method declaration:
  public:

    // CTR & DTR
    YourRunActionMessenger(YourRunAction* runAction);
   ~YourRunActionMessenger();

    // Override the base class method
    void SetNewValue(G4UIcommand*, G4String) override;


  // Data member declarations
  private:

    YourRunAction*             fYourRunAction;

    G4UIdirectory*             fDirCMD;
    G4UIcmdWithAString*        fEdepHistogramCMD;
};

#endif
