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
// $Id: F02FieldMessenger.cc 66356 2012-12-18 09:02:32Z gcosmo $
//
// 

#include "F02FieldMessenger.hh"

#include "F02ElectroMagneticField.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

//////////////////////////////////////////////////////////////////////////////

F02FieldMessenger::F02FieldMessenger(F02ElectroMagneticField* pEMfield)
  :fEMfield(pEMfield)
{ 
  F02detDir = new G4UIdirectory("/field/");
  F02detDir->SetGuidance("F02 field tracking control.");

  StepperCmd = new G4UIcmdWithAnInteger("/field/setStepperType",this);
  StepperCmd->SetGuidance("Select stepper type for electric field");
  StepperCmd->SetParameterName("choice",true);
  StepperCmd->SetDefaultValue(4);
  StepperCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

 
  UpdateCmd = new G4UIcmdWithoutParameter("/field/update",this);
  UpdateCmd->SetGuidance("Update calorimeter geometry.");
  UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  UpdateCmd->SetGuidance("if you changed geometrical value(s).");
  UpdateCmd->AvailableForStates(G4State_Idle);
      
  MagFieldCmd = new G4UIcmdWithADoubleAndUnit("/field/setFieldZ",this);  
  MagFieldCmd->SetGuidance("Define magnetic field.");
  MagFieldCmd->SetGuidance("Magnetic field will be in Z direction.");
  MagFieldCmd->SetParameterName("Bz",false,false);
  MagFieldCmd->SetDefaultUnit("tesla");
  MagFieldCmd->AvailableForStates(G4State_Idle); 
 
  MinStepCmd = new G4UIcmdWithADoubleAndUnit("/field/setMinStep",this);  
  MinStepCmd->SetGuidance("Define minimal step");
  MinStepCmd->SetGuidance("Magnetic field will be in Z direction.");
  MinStepCmd->SetParameterName("min step",false,false);
  MinStepCmd->SetDefaultUnit("mm");
  MinStepCmd->AvailableForStates(G4State_Idle);  
       
  AbsMaterCmd = new G4UIcmdWithAString("/field/setAbsMat",this);
  AbsMaterCmd->SetGuidance("Select Material of the Absorber.");
  AbsMaterCmd->SetParameterName("choice",true);
  AbsMaterCmd->SetDefaultValue("Xe");
  AbsMaterCmd->AvailableForStates(G4State_Idle);


}

///////////////////////////////////////////////////////////////////////////////

F02FieldMessenger::~F02FieldMessenger()
{
  delete StepperCmd;
  delete MagFieldCmd;
  delete MinStepCmd;
  delete F02detDir;
  delete UpdateCmd;

  delete AbsMaterCmd; 
}

////////////////////////////////////////////////////////////////////////////
//
//

void F02FieldMessenger::SetNewValue( G4UIcommand* command, G4String newValue)
{ 
  if( command == StepperCmd )
  { 
    fEMfield->SetStepperType(StepperCmd->GetNewIntValue(newValue));
  }  
  if( command == UpdateCmd )
  { 
    fEMfield->UpdateField(); 
  }
  if( command == MagFieldCmd )
  { 
    fEMfield->SetFieldValue(MagFieldCmd->GetNewDoubleValue(newValue));
  }
  if( command == MinStepCmd )
  { 
    fEMfield->SetMinStep(MinStepCmd->GetNewDoubleValue(newValue));
  }
}

//
//
/////////////////////////////////////////////////////////////////////////



























