
#include "YourPrimaryGeneratorAction.hh"

#include "YourDetectorConstruction.hh"

#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"

YourPrimaryGeneratorAction::YourPrimaryGeneratorAction(YourDetectorConstruction* det)
:   G4VUserPrimaryGeneratorAction(),
    fYourDetector(det),
    fParticleGun(nullptr) {
    // create the particle-gun object
    G4int nParticle = 1;
    fParticleGun    = new G4ParticleGun(nParticle);
    SetDefaultKinematic();
}


YourPrimaryGeneratorAction::~YourPrimaryGeneratorAction() {
    delete fParticleGun;
}


void YourPrimaryGeneratorAction::GeneratePrimaries(G4Event* evt) {
  fParticleGun->GeneratePrimaryVertex(evt);
}


void YourPrimaryGeneratorAction::SetDefaultKinematic() {
    //
    // default primary particle: 30 [MeV] e- perpendicular to the target
  G4ParticleDefinition* part = G4ParticleTable::GetParticleTable()->FindParticle( "e-" );
    fParticleGun->SetParticleDefinition( part );
    fParticleGun->SetParticleMomentumDirection( G4ThreeVector(1., 0., 0.) );
    fParticleGun->SetParticleEnergy( 30.*CLHEP::MeV );
    UpdatePosition();
}


// needs to be invoked for all workers at the begining of the run: user might
// have changed the target thickness
void YourPrimaryGeneratorAction::UpdatePosition() {
    fParticleGun->SetParticlePosition(
        G4ThreeVector( fYourDetector->GetGunXPosition(), 0.0, 0.0 ) );
}


const G4String& YourPrimaryGeneratorAction::GetParticleName() const {
  return fParticleGun->GetParticleDefinition()->GetParticleName();
}


G4double YourPrimaryGeneratorAction::GetParticleEnergy() const {
  return fParticleGun->GetParticleEnergy();
}
