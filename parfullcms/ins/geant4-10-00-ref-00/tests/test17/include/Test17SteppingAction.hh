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
// Class Description:
// Actions on each step are defined
// Class Description - end
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef Test17SteppingAction_h
#define Test17SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4ios.hh"
#include "globals.hh"

class Test17RunAction;
class Test17EventAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class Test17SteppingAction : public G4UserSteppingAction
{
public: // Without description

    Test17SteppingAction(Test17EventAction*,
                      Test17RunAction* );
   ~Test17SteppingAction();

    void UserSteppingAction(const G4Step*);

  private:
    Test17EventAction*          eventaction;
    Test17RunAction*            runaction;

    G4int IDnow,IDold;
    G4bool prim;

};

#endif