
#include "RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4RootAnalysisManager.hh"

RunAction::RunAction() : G4UserRunAction() {}

RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run* run) {
    G4RootAnalysisManager* analysisManager = G4RootAnalysisManager::Instance();
    G4String fileName = "datos_simulacion.root"; // Nombre del archivo .root
    analysisManager->OpenFile(fileName);

    // Crear histogramas según datos a registrar
    analysisManager->CreateH1("Energia", "Histograma de Energia", 100, 0., 100.);
    analysisManager->CreateH1("Trayectoria", "Histograma de Trayectoria", 100, 0., 100.);
}

void RunAction::EndOfRunAction(const G4Run* run) {
    G4RootAnalysisManager* analysisManager = G4RootAnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}

