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
// $Id: test40.cc 75593 2013-11-04 12:35:51Z gcosmo $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "Randomize.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "TrackingAction.hh"
#include "SteppingAction.hh"
#include "SteppingVerbose.hh"
#include "ActionInitialization.hh"

#include <sstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv) {

  //choose the Random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);

  //my Verbose output class
  G4VSteppingVerbose::SetInstance(new SteppingVerbose);

  DetectorConstruction* detector = new DetectorConstruction();

  // Number of threads is defined via 3nd argument
  G4String nn = "";

#ifdef G4MULTITHREADED  
  if (argc==3) { nn = argv[2]; }

  if("" == nn) {
    // Number of threads is defined via environment variable
    char* path = getenv("G4NUMBEROFTHREADS");
    if(path) { nn = G4String(path); }
  }
#endif

  G4RunManager * runManager = 0;
  G4MTRunManager * runManagerMT = 0;

  // MT mode
  if("" != nn) {
    runManagerMT = new G4MTRunManager();
    G4int N = 0;
    std::istringstream is(nn);
    is >> N;
    if(N < 1) { N = 1; }
    runManagerMT->SetNumberOfThreads(N);

    runManagerMT->SetUserInitialization(detector);
    runManagerMT->SetUserInitialization(new PhysicsList());

    PrimaryGeneratorAction* primary = new PrimaryGeneratorAction(detector);//Master instance
    runManagerMT->SetUserInitialization(new ActionInitialization(detector, 
								 primary));

    G4cout << "##### test40 started for " << N << " threads" 
	   << " #####" << G4endl;

    // sequential mode
  } else {
    runManager = new G4RunManager();

    // set mandatory initialization classes
    runManager->SetUserInitialization(detector);
    runManager->SetUserInitialization(new PhysicsList());
  
    PrimaryGeneratorAction* primary = new PrimaryGeneratorAction(detector);
    runManager->SetUserAction(primary);
    
    // set user action classes
    RunAction* RunAct = new RunAction(detector,primary);
    runManager->SetUserAction(RunAct);
    runManager->SetUserAction(new EventAction   (RunAct));
    runManager->SetUserAction(new TrackingAction(RunAct));
    runManager->SetUserAction(new SteppingAction(detector,RunAct)); 

    G4cout << "##### test40 started in sequential mode" 
	   << " #####" << G4endl;

  }

  // get the pointer to the User Interface manager 
  G4UImanager* UI = G4UImanager::GetUIpointer();  

  if (argc==1)   // Define UI terminal for interactive mode.
    {
      G4UIsession * session = 0;
#ifdef G4UI_USE_TCSH
      session = new G4UIterminal(new G4UItcsh);      
#else
      session = new G4UIterminal();
#endif           
      session->SessionStart();
      delete session;
    }
  else           // Batch mode
    { 
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UI->ApplyCommand(command+fileName);
    }

  // job termination
  delete runManager;
  delete runManagerMT;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
