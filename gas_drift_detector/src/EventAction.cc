
#include "EventAction.hh"

#include "G4Run.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4RootAnalysisManager.hh"

EventAction::EventAction() : G4UserEventAction(), fRun(0) {}

EventAction::~EventAction() {}

void EventAction::SetRun(G4Run* run) {
    fRun = run;
}

void EventAction::BeginOfEventAction(const G4Event* event) {
    // Acciones al inicio del evento, si es necesario
}

void EventAction::EndOfEventAction(const G4Event* event) {
    // Acciones al final del evento
    // Se puede realizar análisis de datos o acciones relacionadas con la finalización del evento
}

void EventAction::Reset() {
    // Restablecer acciones, si es necesario
}

