#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ElectricField.hh"
#include "G4UniformElectricField.hh"
#include "SensitiveDetector.hh" // Se añade el header del detector sensible

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

private:
    G4Material* DefineArgonGas(); // Método para definir el material de argón
    G4ElectricField* fElectricField; // Variable miembro para el campo eléctrico
};

#endif // DETECTORCONSTRUCTION_HH
