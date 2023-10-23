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
/// \file EDChamberHit.cc
/// \brief Implementation of the EDChamberHit class
//

#include "EDChamberHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Allocator<EDChamberHit>* EDChamberHitAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EDChamberHit::EDChamberHit()
  : G4VHit(),
    fLayerNumber(-1),
    fGlobalPosition(G4ThreeVector(0.0, 0.0, 0.0)),
    fGlobalTime(0.0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EDChamberHit::~EDChamberHit()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EDChamberHit::EDChamberHit(const EDChamberHit& /*right*/)
 : G4VHit() 
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// methods to set up global position and time
void EDChamberHit::SetGlobalPosition(const G4ThreeVector& pos)
{
  fGlobalPosition = pos;
}

void EDChamberHit::SetGlobalTime(G4double time)
{
  fGlobalTime = time;
}


// methods to get global position and time
const G4ThreeVector& EDChamberHit::GetGlobalPosition() const
{
  return fGlobalPosition;
}

G4double EDChamberHit::GetGlobalTime() const
{
  return fGlobalTime;
}


const EDChamberHit& EDChamberHit::operator=(const EDChamberHit& /*right*/)
{
  return *this;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int EDChamberHit::operator==(const EDChamberHit& right) const
{
  return ( this == &right ) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EDChamberHit::Print()
{  
  G4cout << "Chamber hit in layer: " << fLayerNumber << G4endl;
  G4cout << "Global Position (x, y, z): " << fGlobalPosition.x() << ", " << fGlobalPosition.y() << ", " << fGlobalPosition.z() << G4endl;
  G4cout << "Global Time: " << fGlobalTime << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
