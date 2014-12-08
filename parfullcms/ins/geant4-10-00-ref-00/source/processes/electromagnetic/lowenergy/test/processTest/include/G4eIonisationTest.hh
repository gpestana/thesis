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
// $Id: G4eIonisationTest.hh 66241 2012-12-13 18:34:42Z gunter $
//
// Author: Maria Grazia Pia (Maria.Grazia.Pia@cern.ch)
//
// History:
// -----------
// 07 Oct 2001   MGP        Created
//
// -------------------------------------------------------------------
// Class description:
// Test of electromagnetic physics processes
// Further documentation available from http://www.ge.infn.it/geant4/lowE/index.html

// -------------------------------------------------------------------

#ifndef G4EIONISATIONTEST_HH
#define G4EIONISATIONTEST_HH 1

#include "globals.hh"
#include "G4ProcessTest.hh"

class G4VProcess;

class G4eIonisationTest : public G4ProcessTest 
{
public:

  G4eIonisationTest(const G4String& category);
  virtual ~G4eIonisationTest(); 

  protected:

  virtual G4VProcess* createProcess();
  virtual G4VProcess* createBremsstrahlung();
  virtual G4VProcess* createElectronIonisation();
  G4ParticleDefinition* createIncidentParticle();

private:
  
  // Hide copy constructor and assignment operator
  G4eIonisationTest(const G4eIonisationTest&);
  G4eIonisationTest & operator=(const G4eIonisationTest &right);

  const G4String& type;

};
 
#endif



