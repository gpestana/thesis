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
// $Id: test2.cc 67992 2013-03-13 10:59:57Z gcosmo $
//
// 

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "G4ScoringManager.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#include "Test2DetectorConstruction.hh"
#include "Test2ParallelWorld.hh"
#include "Test2PhysicsList.hh"
#include "Test2PrimaryGeneratorAction.hh"
#include "Test2RunAction.hh"

int main(int argc,char** argv)
{
 // Construct the run manager
 //
 G4RunManager * runManager = new G4RunManager;
 G4ScoringManager * scManager = G4ScoringManager::GetScoringManager();
 scManager->SetVerboseLevel(0);

 // Set mandatory initialization classes
 //
 // Sensitivity Type = 0 none
 //                    1 PrimitiveScorer
 //                    2 SensitiveDetector
 // mass world
 Test2DetectorConstruction* detector = new Test2DetectorConstruction;
 detector->SetSensitivityType(2);
 Test2ParallelWorld* parallel = new Test2ParallelWorld("ParallelScoringWorld");
 parallel->SetSensitivityType(1);
 // parallel world
 detector->RegisterParallelWorld(parallel);
 runManager->SetUserInitialization(detector);

  //
 G4VUserPhysicsList* physics = new Test2PhysicsList;
 runManager->SetUserInitialization(physics);
    
 // Set user action classes
 //
 G4VUserPrimaryGeneratorAction* gen_action = new Test2PrimaryGeneratorAction;
 runManager->SetUserAction(gen_action);
 //
 G4UserRunAction* run_action = new Test2RunAction;
 runManager->SetUserAction(run_action);
  
#ifdef G4VIS_USE
 // Visualization manager
 //
 G4VisManager* visManager = new G4VisExecutive;
 visManager->Initialize();
#endif
    
 // Initialize G4 kernel
 //
 runManager->Initialize();
  
 // Get the pointer to the User Interface manager
 //
 G4UImanager* UI = G4UImanager::GetUIpointer();  

 if (argc==1)   // Define UI session for interactive mode
 {
   G4UIsession* session=0;
  
   // G4UIterminal is a (dumb) terminal
   //
#ifdef G4UI_USE_TCSH
   session = new G4UIterminal(new G4UItcsh);      
#else
   session = new G4UIterminal();
#endif    
      
//   UI->ApplyCommand("/control/execute vis.mac");    
   session->SessionStart();

   delete session;
 }
 else           // Batch mode
 { 
   G4String command = "/control/execute ";
   G4String fileName = argv[1];
   UI->ApplyCommand(command+fileName);
 }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !

#ifdef G4VIS_USE
 delete visManager;
#endif
 delete runManager;

 return 0;
}
