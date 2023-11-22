#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryParticle.hh"
#include "G4PrimaryVertex.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "G4ParticleGun.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(), fParticleGun(nullptr) {
    fParticleGun = new G4ParticleGun(1);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    // Lista de partículas a disparar
    std::vector<G4String> particleList = {"mu+", "gamma", "proton"}; // Agregar más partículas según sea necesario

    for (const auto& particleName : particleList) {
        G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
        G4ParticleDefinition* particle = particleTable->FindParticle(particleName);

        if (!particle) {
            G4cout << "Particle " << particleName << " not found in table." << G4endl;
            continue;
        }

        fParticleGun->SetParticleDefinition(particle);
        fParticleGun->SetParticleEnergy(1.0 * GeV); // Ajusta la energía según sea necesario

        // Posición inicial 5 cm afuera del detector
        G4ThreeVector position(0.0, 1.0 * cm, -15.0 * cm); // Ajusta la posición de inicio
        G4ThreeVector direction(0.0, 0.0, 1.0); // Dirección hacia el detector

        fParticleGun->SetParticlePosition(position);
        fParticleGun->SetParticleMomentumDirection(direction);

        fParticleGun->GeneratePrimaryVertex(anEvent);
    }
}
