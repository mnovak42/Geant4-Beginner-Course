// This class is mandatory: descriptin of the detector
// - the detector/target will be a simple slab (box) with a given material 
//   palced to the world (an other box filled with low density H gaz)

#ifndef YOURDETECTORCONTRUCTION_HH
#define YOURDETECTORCONTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

// forward declaration
class G4Material;

class YourDetectorConstruction : public G4VUserDetectorConstruction {

  // Method declaration:
  public:

    // CTR & DTR 
    YourDetectorConstruction();
    virtual ~YourDetectorConstruction();

    // The base class has the (only one) pure virtual method Construct() which
    // is invoked by the G4RunManager when it's Initialize() method is invoked.
    // The Construct() method must return the G4VPhysicalVolume pointer which 
    // represents the world volume.
    // Your detector description must be implemented here in this method.
    virtual G4VPhysicalVolume* Construct();

    // Note: other (not pure) virtual methods are available in the base class 
    // for SD and FIELD construction. See G4VUserDetectorConstruction for more 
    // details.
    
    
    // Public method to obtain the proper gun-position depending on the detector
    // size (i.e. the mid point between the the World and the Target along the 
    // x-axes on its negative side)
    G4double GetGunXPosition() { return fGunXPosition; }


  // Data member declaration
  private:

    // Target material 
    G4Material*            fTargetMaterial;

    // The target thickness i.e. its (full) x-size (YZ size will be set 1.25x this)
    G4double               fTargetThickness;
    
    // The midpoint between the target and the world on the negative x-side
    G4double               fGunXPosition;

};

#endif   
