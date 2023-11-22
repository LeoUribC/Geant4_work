#ifndef SENSITIVEDETECTOR_HH
#define SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"

class G4Step;

class SensitiveDetector : public G4VSensitiveDetector {
public:
    SensitiveDetector(const G4String& name);
    virtual ~SensitiveDetector();

    virtual void Initialize(G4HCofThisEvent* hitsCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void EndOfEvent(G4HCofThisEvent* hitsCollection);
};

#endif // SENSITIVEDETECTOR_HH
