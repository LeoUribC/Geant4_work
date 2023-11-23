
#include "SensitiveDetector.hh"

#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4RootAnalysisManager.hh"
#include "G4TouchableHistory.hh"

SensitiveDetector::SensitiveDetector(const G4String& name) : G4VSensitiveDetector(name) {}

SensitiveDetector::~SensitiveDetector() {}

void SensitiveDetector::Initialize(G4HCofThisEvent* hitsCollection) {
    // Aquí se inicializan las colecciones de hits, si es necesario
}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history) {
    // Aquí se procesan los hits, se registra la energía, se sigue la trayectoria, etc.
    // Este método se ejecutará cada vez que una partícula interactúe con el detector

    // Obtener la energía depositada en el hit
    G4double edep = step->GetTotalEnergyDeposit();

    // Obtener la trayectoria del hit
    G4Track* track = step->GetTrack();
    G4double trackLength = track->GetTrackLength();

    // Registrar los histogramas en el archivo .root
    G4RootAnalysisManager* analysisManager = G4RootAnalysisManager::Instance();
    analysisManager->FillH1(0, edep);
    analysisManager->FillH1(1, trackLength);

    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* hitsCollection) {
    // Aquí se puede hacer algo al final del evento, si es necesario
}

