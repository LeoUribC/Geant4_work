#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4ElectricField.hh"
#include "G4UniformElectricField.hh"
#include "G4Element.hh"
#include "G4Tubs.hh"
#include "G4SDManager.hh"

DetectorConstruction::DetectorConstruction() : fElectricField(nullptr) {}

DetectorConstruction::~DetectorConstruction() {
    delete fElectricField;
}

G4VPhysicalVolume* DetectorConstruction::Construct() {

    // Obtener el material de argón del NIST Material Database
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* argon = nistManager->FindOrBuildMaterial("G4_Ar");

    // Dimensiones del detector de argón
    G4double detectorSize = 10.0 * cm; // Ejemplo de tamaño del detector (10x10x10 cm³)

    // Crear un volumen de forma cúbica para el detector de argón
    G4Box* solidDetector = new G4Box("ArgonDetector", detectorSize, detectorSize, detectorSize);

    // Crear un volumen lógico para el detector de argón
    G4LogicalVolume* logicDetector = new G4LogicalVolume(solidDetector, argon, "ArgonDetectorLV");

    // Crear un volumen físico para el detector de argón
    G4VPhysicalVolume* physiDetector = new G4PVPlacement(nullptr,
                                                         G4ThreeVector(),
                                                         logicDetector,
                                                         "ArgonDetectorPV",
                                                         nullptr, false, 0);

    // Crear el electrodo de deriva (un cilindro dentro del detector de argón)
    G4double electrodeRadius = 1.0 * cm; // Radio del electrodo
    G4double electrodeLength = 8.0 * cm; // Longitud del electrodo
    G4Tubs* solidElectrode = new G4Tubs("DriftElectrode", 0.0, electrodeRadius,
                                        electrodeLength / 2.0, 0.0, 2.0 * CLHEP::pi);

    // Se declara el material cobre para el electrodo
    G4Material* electrodeMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");

    // volumen logico del electrodo
    G4LogicalVolume* logicElectrode = new G4LogicalVolume(solidElectrode, electrodeMaterial, "DriftElectrodeLV");

    // Colocar el electrodo de deriva dentro del detector de argón
    new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, 1.0 * cm),
                      logicElectrode, "DriftElectrodePV", logicDetector, false, 0);

    // Asignar el detector sensible al detector de argón (nueva adicion)
    G4VSensitiveDetector* detectorSD = new SensitiveDetector("ArgonSD");
    G4SDManager::GetSDMpointer()->AddNewDetector(detectorSD);
    logicDetector->SetSensitiveDetector(detectorSD);

    // Antes de la creación del campo eléctrico
    //G4FieldManager* fieldMgr = new G4FieldManager();
    //fieldMgr->SetDetectorField(fElectricField);
    //fieldMgr->CreateChordFinder(fElectricField);

    // Crear un campo eléctrico uniforme (por ejemplo, en dirección z)
    //G4double fieldValue = 1.0 * kilovolt / centimeter; // Modificar según necesidades
    //fElectricField = new G4UniformElectricField(G4ThreeVector(0.0, 0.0, fieldValue));

    // Asignar el campo eléctrico al detector de argón
    //logicDetector->SetFieldManager(fieldMgr, true);

    return physiDetector; // Retornar el volumen físico del detector
}

