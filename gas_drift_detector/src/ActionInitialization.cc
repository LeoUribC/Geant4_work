#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
//#include "RunAction.hh"
#include "EventAction.hh"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization() {}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::Build() const {
    SetUserAction(new PrimaryGeneratorAction);
    //SetUserAction(new RunAction());
    SetUserAction(new EventAction);
    // otras acciones necesarias
}
