#include "EventAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"

EventAction::EventAction() : G4UserEventAction() {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event* /*event*/) {
    // Acciones al inicio del evento, si es necesario
}

void EventAction::EndOfEventAction(const G4Event* event) {
    // Acciones al final del evento
    // Se puede realizar análisis de datos o acciones relacionadas con la finalización del evento
}
