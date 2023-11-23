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
/// \file EDChamberHit.hh
/// \brief Definition of the EDChamberHit class
//


#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class HumanHit : public G4VHit
{
  public:
    HumanHit();
    virtual ~HumanHit();
    HumanHit(const HumanHit& right);
    const HumanHit& operator=(const HumanHit& right);
    int operator==(const HumanHit &right) const;

    inline void* operator new(size_t);
    inline void  operator delete(void* hit);

    virtual void Print();
    virtual void Draw();

    // setter methods
    void SetOrgan(G4String name) { fOrganName = name; }
    void SetTime(G4double time)       { fTime = time; }
    void SetPosition(G4ThreeVector position) { fPosition = position; }

    // getter methods
    G4String       GetOrganName() const   { return fOrganName;}
    G4double       GetTime() const        { return fTime; }
    G4ThreeVector  GetPosition() const    { return fPosition; } 

  private:
    // data members
    G4String       fOrganName;
    G4double       fTime;
    G4ThreeVector  fPosition;
};

typedef G4THitsCollection<HumanHit> HumanHitsCollection;

extern G4Allocator<HumanHit>* HumanHitAllocator;

inline void* HumanHit::operator new(size_t)
{
  if (! HumanHitAllocator)
        HumanHitAllocator = new G4Allocator<HumanHit>;
  return (void*)HumanHitAllocator->MallocSingle();
}

inline void HumanHit::operator delete(void* hit)
{
  HumanHitAllocator->FreeSingle((HumanHit*) hit);
}



