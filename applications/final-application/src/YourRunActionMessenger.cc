#include "YourRunActionMessenger.hh"

#include "YourRunAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4String.hh"
#include "G4SystemOfUnits.hh"

#include <iterator>

YourRunActionMessenger::YourRunActionMessenger(YourRunAction* runAction)
:   G4UImessenger(),
    fYourRunAction(runAction),
    fDirCMD(nullptr),
    fEdepHistogramCMD(nullptr) {
    //
    // create the "yourRun" command directory first then add commands
    fDirCMD = new G4UIdirectory("/yourApp/runAction/");
    fDirCMD->SetGuidance("UI commands specific to YourRun object of this application that will act through YourRunAction");
    //
    // UI command to set the ...
    fEdepHistogramCMD = new G4UIcmdWithAString("/yourApp/runAction/edepHisto",this);
    // set the description of the command
    fEdepHistogramCMD->SetGuidance("Activates and sets the [File-Name Minimum-Eenrgy Maximum-Energy Energy-Unit(keV, MeV, GeV) Number-of-Bins] of the Energy-deposit histogram.");
    // name = edepHisto; omittable=false i.e. user needs to supply value
    fEdepHistogramCMD->SetParameterName("edepHisto",false);
    // can be modified at PreInit and Idle state
    fEdepHistogramCMD->AvailableForStates(G4State_PreInit, G4State_Idle);
    // in MT mode: needs to be broadcasted for workers (each worker has their own
    //             YourRun object and the UI commands act on the Master's one)
    fEdepHistogramCMD->SetToBeBroadcasted(true);
}


YourRunActionMessenger::~YourRunActionMessenger() {
    delete fEdepHistogramCMD;
    delete fDirCMD;
}


void YourRunActionMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
    // set target thickness
    if (command == fEdepHistogramCMD) {
        // parse string to get: FileName MinEnergy MaxEnergy EnergyUnit(keV, MeV, GeV) NumberOfBins
        std::istringstream iss(newValue);
        std::vector<G4String> vscmd(std::istream_iterator<std::string>{iss},
                                    std::istream_iterator<std::string>());
        G4String fname     = vscmd[0];
        G4double minEnergy = std::stod(vscmd[1]);
        G4double maxEnergy = std::stod(vscmd[2]);
        G4double unit      = 1.0;
        if (vscmd[3] == "keV") {
          unit = CLHEP::keV;
        } else if (vscmd[3] == "GeV") {
          unit = CLHEP::GeV;
        } // else take the default MeV i.e. unts stays to be = 1
        G4int    numBins   = std::stoi(vscmd[4]);
//        G4cout << fname << " " << minEnergy << " " << maxEnergy << " " << numBins << G4endl;
        fYourRunAction->SetEdepHistogram(fname, minEnergy*unit, maxEnergy*unit,
                                         numBins);
    }
}
