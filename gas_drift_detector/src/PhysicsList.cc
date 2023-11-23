
#include "PhysicsList.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ionIonisation.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonParametrisedLossModel.hh"

PhysicsList::PhysicsList() : G4VModularPhysicsList() {}

PhysicsList::~PhysicsList() {}

void PhysicsList::ConstructParticle() {
    // Partículas disponibles
    G4Geantino::GeantinoDefinition();
    G4ChargedGeantino::ChargedGeantinoDefinition();
    G4Electron::ElectronDefinition();
    G4Positron::PositronDefinition();
    G4Gamma::GammaDefinition();
    G4MuonPlus::MuonPlusDefinition();
    G4MuonMinus::MuonMinusDefinition();
}

void PhysicsList::ConstructProcess() {
    std::vector<G4String> particleNames = {"mu+", "gamma", "proton"}; // Lista de partículas a considerar

    for (const auto& particleName : particleNames) {
        G4ParticleDefinition* particle =
            G4ParticleTable::GetParticleTable()->FindParticle(particleName);

        if (particle) {
            G4ProcessManager* pmanager = particle->GetProcessManager();
            G4ionIonisation* ionIonisation = new G4ionIonisation();
            ionIonisation->SetEmModel(new G4IonParametrisedLossModel());
            pmanager->AddProcess(ionIonisation);
            pmanager->SetProcessOrdering(ionIonisation, idxPostStep);
        }
    }
}
