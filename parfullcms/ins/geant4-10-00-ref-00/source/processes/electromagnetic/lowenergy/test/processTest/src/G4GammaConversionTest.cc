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
// $Id: G4GammaConversionTest.cc 66241 2012-12-13 18:34:42Z gunter $
//
// Author: Maria Grazia Pia (Maria.Grazia.Pia@cern.ch)
//
// History:
// -----------
// 07 Oct 2001   MGP        Created
//
// -------------------------------------------------------------------
// Class description:
// Test DoIt method of physics processes
// Further documentation available from http://www.ge.infn.it/geant4/lowE/index.html

// -------------------------------------------------------------------

#include "globals.hh"
#include "G4GammaConversionTest.hh"
#include "G4VProcess.hh"

#include "G4LowEnergyGammaConversion.hh"
//#include "G4LowEnergyPolarizedGammaConversion.hh"

#include "G4GammaConversion.hh"

#include "G4LowEnergyBremsstrahlung.hh"
#include "G4eBremsstrahlung.hh"

#include "G4LowEnergyIonisation.hh"
#include "G4eIonisation.hh"

G4GammaConversionTest::G4GammaConversionTest(const G4String& category, G4bool isPolarised)
  :type(category), polarised(isPolarised)
{ }

G4GammaConversionTest:: ~G4GammaConversionTest()
{ }

G4VProcess* G4GammaConversionTest::createElectronIonisation()
{
  G4VProcess* testProcess = 0;
  if (type == "lowE")
    {
      testProcess = new G4LowEnergyIonisation;
    }
  else if (type == "standard")
    {
      testProcess = new G4eIonisation;
    }
  return testProcess;
}

G4VProcess* G4GammaConversionTest::createBremsstrahlung()
{
  G4VProcess* testProcess = 0;
  if (type == "lowE")
    {
      testProcess = new G4LowEnergyBremsstrahlung;
    }
  else if (type == "standard")
    {
      testProcess = new G4eBremsstrahlung;
    }
  return testProcess;  
}

G4VProcess* G4GammaConversionTest::createProcess()
{
  G4VProcess* testProcess = 0;
  if (type == "lowE" && (!polarised))
    {
      testProcess = new G4LowEnergyGammaConversion;
    }
  else if (type == "lowE" && polarised)
    {
      G4Exception("Polarised LowE process not available yet");
      //      testProcess = new G4LowEnergyPolarizedGammaConversion;
    }  
  else if (type == "standard" && (!polarised))
    {
      testProcess = new G4GammaConversion;
    }
  else if (type == "standard" && polarised)
    {
      G4Exception("Standard process not available");
    }
  return testProcess;  
}


