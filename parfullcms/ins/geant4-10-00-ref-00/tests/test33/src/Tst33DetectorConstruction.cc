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
//
// $Id: Tst33DetectorConstruction.cc 66358 2012-12-18 09:07:19Z gcosmo $
//

#include "Tst33DetectorConstruction.hh"

#include "G4PVPlacement.hh"

Tst33DetectorConstruction::
Tst33DetectorConstruction()
 : fWorldVolume(0)
{;}

Tst33DetectorConstruction::~Tst33DetectorConstruction()
{;}

void Tst33DetectorConstruction::SetWorldVolume(G4VPhysicalVolume *v) {
  fWorldVolume = v;
}

G4VPhysicalVolume* Tst33DetectorConstruction::Construct()
{
  return fWorldVolume;
}