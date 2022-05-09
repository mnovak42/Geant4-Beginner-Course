
#include "YourDetectorMessenger.hh"

#include "YourDetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4String.hh"


YourDetectorMessenger::YourDetectorMessenger(YourDetectorConstruction* det)
:   G4UImessenger(),
    fYourDetector(det),
    fDirCMD(nullptr),
    fTargetThicknessCMD(nullptr),
    fTargetMaterialCMD(nullptr) {
    //
    // create the "det" command directory first then add commands
    fDirCMD = new G4UIdirectory("/yourApp/det/");
    fDirCMD->SetGuidance("UI commands specific to the detector construction of this application");
    //
    // UI command to set the target thickness
    fTargetThicknessCMD = new G4UIcmdWithADoubleAndUnit("/yourApp/det/setTargetThickness",this);
    // set the description of the command
    fTargetThicknessCMD->SetGuidance("Sets the Thickness of the Target.");
    // name = TagetSizeX; omittable=false i.e. user needs to supply a value
    fTargetThicknessCMD->SetParameterName("TagetSizeX",false);
    // set the aceptable range of the parameter value higher than zero
    fTargetThicknessCMD->SetRange("TagetSizeX>0.");
    // set the unit category to be length
    fTargetThicknessCMD->SetUnitCategory("Length");
    // can be modified at PreInit and Idle state
    fTargetThicknessCMD->AvailableForStates(G4State_PreInit, G4State_Idle);
    // in MT mode: do not need to be broadcasted for workers
    fTargetThicknessCMD->SetToBeBroadcasted(false);
    // UI command to set the target material (NIST material i.e. with G4_ prefix)
    fTargetMaterialCMD  = new G4UIcmdWithAString("/yourApp/det/setTargetMaterial",this);
    fTargetMaterialCMD->SetGuidance("Sets the Material of the Target.");
    fTargetMaterialCMD->SetParameterName("TagetMaterial",false);
    fTargetMaterialCMD->AvailableForStates(G4State_PreInit, G4State_Idle);
//    fTargetMaterialCMD->SetToBeBroadcasted(false);
}


YourDetectorMessenger::~YourDetectorMessenger() {
  delete fTargetThicknessCMD;
  delete fTargetMaterialCMD;
  delete fDirCMD;
}


void YourDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    // set target thickness
    if (command == fTargetThicknessCMD) {
        G4double thickness = fTargetThicknessCMD->GetNewDoubleValue(newValue);
        fYourDetector->SetTargetThickness(thickness);
    }
    // set tartget material name
    if (command == fTargetMaterialCMD) {
        fYourDetector->SetTargetMaterial(newValue);
   }
}
