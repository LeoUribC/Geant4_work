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

#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryParticle.hh"
#include "G4PrimaryVertex.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "G4ParticleGun.hh"
#include "Randomize.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(),
      fParticleGun(0),
      fRandom(true) 
{
    std::vector<G4String> particleNames = {"mu-","proton","gamma"};
    G4int nofParticles = 1;

    for (G4String ParticleName : particleNames) {
        fParticleGun = new G4ParticleGun(nofParticles);
        G4String particleName = ParticleName;
        G4ThreeVector position(-0.2*m,2.9*m,-1.*m);
        G4ThreeVector momentum(0,0,1.*GeV);

        G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
        G4ParticleDefinition *particle
        = particleTable->FindParticle(ParticleName);
       fParticleGun->SetParticleDefinition(particle);
       fParticleGun->SetParticlePosition(position);
       fParticleGun->SetParticleMomentum(momentum);

       //delete fParticleGun;

   }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  //this function is called at the begining of ecah event  //

  if(fRandom){
    G4double dtheta = 10.*deg;
    G4double dphi = 50.*deg;
    G4double theta = G4UniformRand()*dtheta;
    G4double phi = G4UniformRand()*dphi;
    fParticleGun->SetParticleMomentumDirection(
    G4ThreeVector(theta, -1, phi));

  }
  else{
     fParticleGun->SetParticleMomentumDirection(
      G4ThreeVector(0,-1,0));
  }
  fParticleGun->GeneratePrimaryVertex(event);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

