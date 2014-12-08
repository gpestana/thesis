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
// $Id: Tst33TimedApplication.cc 66358 2012-12-18 09:07:19Z gcosmo $
// GEANT4 tag 
//
// ----------------------------------------------------------------------
// GEANT 4 class source file
//
// Tst33TimedApplication.cc
//
// ----------------------------------------------------------------------

#include "Tst33TimedApplication.hh"
#include "G4RunManager.hh"
#include "Tst33TimedEventAction.hh"

Tst33TimedApplication::Tst33TimedApplication(G4int time)
  : fTime(time)
{}

Tst33TimedApplication::~Tst33TimedApplication()
{}

Tst33VEventAction *Tst33TimedApplication::CreateEventAction()
{
  return new Tst33TimedEventAction(fTime);
}

G4UserRunAction *Tst33TimedApplication::CreateRunAction()
{
  return 0;
}
