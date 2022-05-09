
#include "YourDetectorConstruction.hh"

// for geometry definitions 
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

// for material definitions
#include "G4Material.hh"
#include "G4NistManager.hh"

// for having units and constants
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


// CTR
YourDetectorConstruction::YourDetectorConstruction()
:   G4VUserDetectorConstruction() {
    // set default material: try to find the material in the NIST DB
    G4String matName = "G4_Si";
    fTargetMaterial = G4NistManager::Instance()->FindOrBuildMaterial(matName);
    if (!fTargetMaterial) {
      G4cerr<< "\n **** ERROR in YourDetectorConstruction::YourDetectorConstruction() \n"
            << "        Material with the given name of < " << matName << " >  \n"
            << "        was not found in the G4 NIST material DB               \n"
            << G4endl;
      exit(-1);      
    }
    // set default target thickness
    fTargetThickness = 1.0*CLHEP::cm; 
    // set the gun position: we should set it in the Construct() method and we  
    //  do it there later. Make it simple now: the world will be 1.1x the target 
    //  so we can compute the proper position of the gun (no any translations!!)
    fGunXPosition    = -0.25*( 1.1*fTargetThickness + fTargetThickness );
}

// DTR
YourDetectorConstruction::~YourDetectorConstruction() {}

//
// The detector is a simple slab (with fTargetThickness along the x-direction).
//
G4VPhysicalVolume* YourDetectorConstruction::Construct() {
    G4cout << " ---- YourDetectorConstruction::Construct() is called " << G4endl;
	// I. CREATE/SET MATERIALS:
    // (note that we use fixed material here. One could use messenger to set them)
    // 1. Material for the world: low density hydrogen defined by "hand"
    G4double zet      = 1.0;
    G4double amass    = 1.01*CLHEP::g/CLHEP::mole;
    G4double density  = CLHEP::universe_mean_density;
    G4double pressure = 3.e-18*CLHEP::pascal;
    G4double tempture = 2.73*CLHEP::kelvin;
    G4Material* materialWorld  = new G4Material("Galactic", zet, amass, density,
                                                kStateGas, tempture, pressure);
    // 2. Material for the target: material pointer stored in fTargetMaterial 
    G4Material* materialTarget = fTargetMaterial;
    //
    // II. CREATE GEOMETRY:
    // 1. Define target and world sizes
    G4double targetXSize  = fTargetThickness;
    G4double targetYZSize = 1.25*targetXSize;
    G4double worldXSize   = 1.1*targetXSize;
    G4double worldYZSize  = 1.1*targetYZSize;
    // we can compute now the proper position of the gun
//    fGunXPosition         = -0.25*( worldXSize + targetXSize );
    // 2. Create the world and the target (both will be box):
    // a. world
    G4Box*              worldSolid   = new G4Box("solid-World",  // name
    	                                       0.5*worldXSize,   // half x-size
    	                                       0.5*worldYZSize,  // half y-size 
    	                                       0.5*worldYZSize); // half z-size
    G4LogicalVolume*    worldLogical = new G4LogicalVolume(worldSolid,     // solid
                                                           materialWorld,  // material
                                                           "logic-World"); // name
    G4VPhysicalVolume*  worldPhyscal = new G4PVPlacement(nullptr,                 // (no) rotation
                                                         G4ThreeVector(0.,0.,0.), // translation
                                                         worldLogical,            // its logical volume
                                                         "World",                 // its name
                                                         nullptr,                 // its mother volume
                                                         false,                   // not used
                                                         0);                      // cpy number
    // b. target
    G4Box*              targetSolid   = new G4Box("solid-Target",    // name
    	                                          0.5*targetXSize,   // half x-size
    	                                          0.5*targetYZSize,  // half y-size 
    	                                          0.5*targetYZSize); // half z-size
    G4LogicalVolume*    targetLogical = new G4LogicalVolume(targetSolid,    // solid
                                                           materialTarget,  // material
                                                           "logic-Target"); // name
    G4VPhysicalVolume*  targetPhyscal = new G4PVPlacement(nullptr,                 // (no) rotation
                                                          G4ThreeVector(0.,0.,0.), // translation
                                                          targetLogical,           // its logical volume
                                                          "Target",                // its name
                                                          worldLogical,            // its mother volume
                                                          false,                   // not used
                                                          0);                      // cpy number                                                          
    //
    // III. CREATE FIELD and RETURN WITH THE World PHYSICAL-VOLUME POINTER:
    return worldPhyscal;
}
