#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"

class G4Run;

class RunAction : public G4UserRunAction {
public:
    RunAction();
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run* run);
    virtual void EndOfRunAction(const G4Run* run);
};

#endif // RUNACTION_HH
