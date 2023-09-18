//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id$
//
/// \file EDDetectorConstruction.cc
/// \brief Implementation of the EDDetectorConstruction class

#include "EDDetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

// for coloring different objects
#include "G4VisAttributes.hh"
#include "G4Color.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EDDetectorConstruction::EDDetectorConstruction()
: G4VUserDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EDDetectorConstruction::~EDDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* EDDetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nistManager = G4NistManager::Instance();

  // Build materials
  G4Material* galactic = nistManager->FindOrBuildMaterial("G4_Galactic");
  G4Material* air = nistManager->FindOrBuildMaterial("G4_AIR");
  G4Material* CsI = nistManager->FindOrBuildMaterial("G4_CESIUM_IODIDE");
  G4Material* argon = nistManager->FindOrBuildMaterial("G4_Ar");
  G4Material* copper = nistManager->FindOrBuildMaterial("G4_Cu");
       // There is no need to test if materials were built/found
       // as G4NistManager would issue an error otherwise
       // Try the code with "XYZ".      
  
  // Option to switch on/off checking of volumes overlaps
   G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double hx = 10*m;
  G4double hy = 3.*m;
  G4double hz = 10*m;
  
  // world volume
  G4Box* worldS = new G4Box("World", hx, hy, hz); 
      
  G4LogicalVolume* worldLV                         
    = new G4LogicalVolume(worldS, galactic, "World");
                                   
  G4VPhysicalVolume* worldPV
    = new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      worldLV,               //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  //
  // Tube
  //
  G4double rmin = 0.;
  G4double rmax = 1.*m;
  hz = 1.*m;
  G4double phimin = 0.;
  G4double dphi = 360.*deg;
  
  // tube volume
  G4VSolid* tubeS = new G4Tubs("Tube", rmin, rmax, hz, phimin, dphi);
  
  G4LogicalVolume* tubeLV
    = new G4LogicalVolume(tubeS, galactic, "Tube");
 
  new G4PVPlacement(0, 
                    G4ThreeVector(),       //at (0,0,0)
                    tubeLV,                //its logical volume
                    "Tube",                //its name
                    worldLV,               //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking

  //always return the physical World
  //

  //First arm construction
  G4double posXarm = 0.*cm;
  G4double posYarm = 0.*cm;
  G4double posZarm = -5.*m;
  G4ThreeVector position(posXarm,posYarm,posZarm);
  G4double sizeXarm = 1.5*m;
  G4double sizeYarm = 1.0*m;
  G4double sizeZarm = 3.0*m;
  //armvolume
  G4Box* armS = new G4Box("arm1", sizeXarm, sizeYarm,sizeZarm);
  G4LogicalVolume* armLV = new G4LogicalVolume(armS,air,"arm");
  G4VPhysicalVolume* armPV = new G4PVPlacement(0,
  					      position,
                                              armLV,
                                              "arm1",
                                              worldLV,
                                              false,
                                              1);

  //Second arm construction
  G4double posZ2arm = 5.*m;
  G4ThreeVector position2(posXarm,posYarm,posZ2arm);
  //armvolume
  G4Box* arm2S = new G4Box("arm1", sizeXarm, sizeYarm,sizeZarm);
  G4LogicalVolume* arm2LV = new G4LogicalVolume(armS,air,"arm");
  G4VPhysicalVolume* arm2PV = new G4PVPlacement(0,
                                              position2,
                                              arm2LV,
                                              "arm2",
                                              worldLV,
                                              false,
                                              1);

  //Calorimeter
  G4double posZcal = 2.0*m;
  G4ThreeVector positionCal(0,0,posZcal);
  
  G4double sizeXcal =  1.5*m;
  G4double sizeYcal = 30.*cm;
  G4double sizeZcal = 15.*cm;

  //calorimeter volume
  G4Box* calorimeterS = new G4Box("calorimter1",sizeXcal, sizeYcal, sizeZcal);
  G4LogicalVolume* calorimeterLV = new G4LogicalVolume(calorimeterS,CsI,"calorimeter");
  G4VPhysicalVolume* calorimeterPV = new G4PVPlacement(0,
                                                       positionCal,
                                                       calorimeterLV,
                                                       "calorimeter",
                                                       arm2LV,
                                                       false,
                                                       1);

  // yellow color creation
  G4Color yellow(1.0, 1.0, 0.0);

  // creating visual aesthetics
  G4VisAttributes* calorimeterVisAtt = new G4VisAttributes(yellow);

  // setting up aesthetics to the calorimeter
  calorimeterLV->SetVisAttributes(calorimeterVisAtt);


  //Calorimeter layers
  G4double layerX = 1.5*m;
  G4double layerY = 30.*cm; 
  G4double layerZ = 1.9*cm;
  G4double gapL = 0.1*cm;

  G4Box* layerS = new G4Box("layer",layerX,layerY,layerZ);
  G4LogicalVolume* layerLV = new G4LogicalVolume(layerS,CsI,"layer");

  for(int i=0;i<15;i++){
  	G4double posZlay = -15.*cm + i*(layerZ+gapL);
  	G4double posXlay = 0.*cm;
  	G4double posYlay = 0.*cm;
  	
  	G4VPhysicalVolume* layerPV = new G4PVPlacement(0,
                                 G4ThreeVector(posXlay,posYlay,posZlay),
                                 layerLV,
                                 "layer",
                                 calorimeterLV,
                                 false,
                                 i);

    // coloring the layers
    layerLV->SetVisAttributes(calorimeterVisAtt);
  }
  

  //Drift Chambers 
  //size of chamber
  G4int capas = 5;
  G4double sizeZch =  1.*cm;
  G4double sizeYch = 30.*cm;
  G4double sizeXch = 1.5*m;
  G4double gap = 50*cm;

  // green color creation
  G4Color green(0.0, 1.0, 0.0);

  // creating visual aesthetics for the chamber
  G4VisAttributes* chamberVisAtt = new G4VisAttributes(green);

  G4Box* chamberS = new G4Box("chamber1",sizeXch,sizeYch,sizeZch);
  G4LogicalVolume* chamberLV = new G4LogicalVolume(chamberS,argon,"chamber1");
  
  for (int i=0;i<5;i++){
  	G4double posZch = -2*gap + i*(sizeZch+gap);
  	G4double posXch = 0.0*cm;
  	G4double posYch = 0.0*cm;

  	G4VPhysicalVolume* chamberPV = new G4PVPlacement(0,
                                  G4ThreeVector(posXch, posYch, posZch),
                                  chamberLV,
                                  "chamber1",
                                  armLV,
                                  false,
                                  i);

    // setting up aesthetics to the chambers
    chamberLV->SetVisAttributes(chamberVisAtt);
  }
  for (int i=0;i<5;i++){
        G4double posZch = -2*gap + i*(sizeZch+gap);
        G4double posXch = 0.0*cm;
        G4double posYch = 0.0*cm;

        G4VPhysicalVolume* chamberPV = new G4PVPlacement(0,
                                  G4ThreeVector(posXch, posYch, posZch),
                                  chamberLV,
                                  "chamber2",
                                  arm2LV,
                                  false,
                                  i);
        // setting up aesthetics to the chambers
        chamberLV->SetVisAttributes(chamberVisAtt);
  }

  //wire
  G4double sizeZwi =  0.1*mm;
  G4double sizeYwi = 30.*cm;
  G4double sizeXwi = 1.5*m;

  G4Box* wireS = new G4Box("wire",sizeXwi,sizeYwi,sizeZwi);
  G4LogicalVolume* wireLV = new G4LogicalVolume(wireS,copper,"wire1");
  G4VPhysicalVolume* wirePV = new G4PVPlacement(0,
                                                  G4ThreeVector(),
                                                  wireLV,
                                                  "wire1",
                                                  chamberLV,
                                                  false,
                                                  1);
  return worldPV;
}

//....oooOO 0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
