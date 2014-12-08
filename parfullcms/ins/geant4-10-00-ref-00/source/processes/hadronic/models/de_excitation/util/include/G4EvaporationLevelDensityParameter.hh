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
// $Id: G4EvaporationLevelDensityParameter.hh 68724 2013-04-05 09:26:32Z gcosmo $
//
// Hadronic Process: Nuclear De-excitations
// by V. Lara (Oct 1998) 
//
// Modified:
// 21.03.2013 V.Ivanchenko redesigned and commented out unused part

#ifndef G4EvaporationLevelDensityParameter_h
#define G4EvaporationLevelDensityParameter_h 1

#include "G4VLevelDensityParameter.hh"
//#include "G4CameronTruranHilfShellCorrections.hh"

class G4EvaporationLevelDensityParameter : public G4VLevelDensityParameter
{
public:

  G4EvaporationLevelDensityParameter();

  virtual ~G4EvaporationLevelDensityParameter();

  inline 
  G4double LevelDensityParameter(G4int A, G4int/*Z*/, G4double /*U*/) const
  {
    return static_cast<G4double>(A)/10.;
  }

private:  
	
  G4EvaporationLevelDensityParameter(const G4EvaporationLevelDensityParameter &right);

  const G4EvaporationLevelDensityParameter & operator=(const G4EvaporationLevelDensityParameter &right);
  G4bool operator==(const G4EvaporationLevelDensityParameter &right) const;
  G4bool operator!=(const G4EvaporationLevelDensityParameter &right) const;
  
  /*
private:
  inline G4double ShellCorrection(G4int Z, G4int N) const
  { 
    return SPtr->GetShellZ(Z) + SPtr->GetShellN(N);
  }

  static const G4double ConstEvapLevelDensityParameter;
  static const G4double alpha;
  static const G4double beta;
  static const G4double gamma;
  static const G4double Bs;

  G4CameronTruranHilfShellCorrections* SPtr;
  */	  		

};

#endif
