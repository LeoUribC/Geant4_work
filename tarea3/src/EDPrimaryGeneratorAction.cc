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
/// \file EDPrimaryGeneratorAction.cc
/// \brief Implementation of the EDPrimaryGeneratorAction class

#include "EDPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryParticle.hh"
#include "G4PrimaryVertex.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EDPrimaryGeneratorAction::EDPrimaryGeneratorAction()
{
  //this function is called at the begining of ecah event
  //

  // Define particle properties
  G4String particleName = "proton";
  //G4String particleName = "geantino";
  G4ThreeVector position(0, 0, -9.*m);   
  G4ThreeVector momentum(0, 0, 1.*GeV);
  


  G4ParticleGun* ParticleGun = new G4ParticleGun();
  
  // Get particle definition from G4ParticleTable
  G4ParticleDefinition* particleDefinition
    = G4ParticleTable::GetParticleTable()->FindParticle("proton");

  ParticleGun->SetParticleDefinition(particleDefinition);
  ParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  ParticleGun->SetParticleEnergy(3.0*GeV);  
  // Create primary particle
  G4PrimaryParticle* primaryParticle = new G4PrimaryParticle(particleDefinition);
  primaryParticle->SetMomentum(momentum.x(), momentum.y(), momentum.z());
  primaryParticle->SetMass(particleDefinition->GetPDGMass());
  primaryParticle->SetCharge( particleDefinition->GetPDGCharge());

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EDPrimaryGeneratorAction::~EDPrimaryGeneratorAction()
{
  delete ParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EDPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  
  G4double worldZHalfLength = 0;
  G4double time = 0;
  G4LogicalVolume* worldLV
    = G4LogicalVolumeStore::GetInstance()->GetVolume("World");
  G4Box* worldBox = nullptr;
  if ( worldLV ) worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());
  if ( worldBox ) worldZHalfLength = worldBox->GetZHalfLength();
  else  {
    G4cerr << "World volume of box not found." << G4endl;
    G4cerr << "Perhaps you have changed geometry." << G4endl;
    G4cerr << "The gun will be place in the center." << G4endl;
  }
  ParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -worldZHalfLength))
  ParticleGun->GeneratePrimaryVertex(anEvent);

  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

