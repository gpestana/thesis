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
#define test31PrimaryGeneratorAction_CPP 

//---------------------------------------------------------------------------
//
// ClassName:   test31PrimaryGeneratorAction
//  
// Description: Generate primary beam 
//
// Authors:    0.6.04.01 V.Ivanchenko
//
// Modified:
//
//----------------------------------------------------------------------------
//

#include "test31PrimaryGeneratorAction.hh"
#include "test31PrimaryGeneratorMessenger.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "test31Histo.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

test31PrimaryGeneratorAction::test31PrimaryGeneratorAction()
{
  InitializeMe();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void test31PrimaryGeneratorAction::InitializeMe()
{
  theMessenger = new test31PrimaryGeneratorMessenger(this);
  particleGun = new G4ParticleGun();

  counter = 0;
  verbose = 0;

  x0 = 0.0; 
  y0 = 0.0;
  z0 = 0.0;
  sigmaX = 0.0;
  sigmaY = 0.0;
  sigmaZ = 0.0;
  sigmaE = 0.0;

  minCosTheta = 1.0;
  energy      = 10.0*MeV;
  minE        = energy;
  maxE        = energy;
  minBeta     = 0.0;
  maxBeta     = 1.0;

  position  = G4ThreeVector(x0,y0,z0);
  direction = G4ThreeVector(0.0,0.0,1.0);

  m_gauss = true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

test31PrimaryGeneratorAction::~test31PrimaryGeneratorAction()
{
  delete particleGun;
  delete theMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void test31PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  test31Histo* man = test31Histo::GetPointer();
  verbose = man->GetVerbose();
  counter = man->Event();

  // Simulation of beam position
  G4double x = x0;
  G4double y = y0;
  G4double z = z0;
  if(0.0 < sigmaX) x += G4RandGauss::shoot(0.0,sigmaX);
  if(0.0 < sigmaY) y += G4RandGauss::shoot(0.0,sigmaY);
  if(0.0 < sigmaZ) z += G4RandGauss::shoot(0.0,sigmaZ);
  position  = G4ThreeVector(x,y,z);
  particleGun->SetParticlePosition(position);

  // Simulation of beam direction
  G4double ux = direction.x();
  G4double uy = direction.y();
  G4double uz = direction.z();

  // Beam particles are uniformly distributed over phi, cosTheta 
  if(1.0 > minCosTheta) {
    uz = minCosTheta + (1.0 - minCosTheta)*G4UniformRand() ;
    ux = std::sqrt(1.0 - uz*uz) ;
    uy = ux ;
    G4double phi = 360.0*deg*G4UniformRand() ;
    ux *= std::cos(phi) ;
    uy *= std::sin(phi) ;
    direction = G4ThreeVector(ux,uy,uz) ;
  }
 
  direction = direction.unit();
  particleGun->SetParticleMomentumDirection(direction);
  G4ParticleDefinition* particle = particleGun->GetParticleDefinition();
  G4double mass = particle->GetPDGMass();

  // Simulation of beam kinetic energy
  G4double kinEnergy = particleGun->GetParticleEnergy();

  man->SetBeamParticle(particle);
  man->SetBeamEnergy(kinEnergy);

  if(m_gauss == "flatE") kinEnergy  = minE + (maxE-minE)*G4UniformRand();

  else if(m_gauss == "flatBeta") {
         G4double beta = minBeta + (maxBeta-minBeta)*G4UniformRand();
         kinEnergy = mass*(1./std::sqrt(1. - beta*beta) - 1.);
  }
  else if(0.0 < sigmaE) kinEnergy += G4RandGauss::shoot(0.0,sigmaE);
   

  if(0.0 > kinEnergy) kinEnergy = 0.0;
  particleGun->SetParticleEnergy(kinEnergy);

  if(verbose > 0) {
    G4cout << "Event#  " << counter 
           << "  Beam particle is generated by test31PrimaryGeneratorAction " 
           << G4endl;
    G4cout << "ParticleName= " << particle->GetParticleName()  
           << "  PDGcode= " << particle->GetPDGEncoding()
           << std::setprecision(5) 
	   << "   KinEnergy(GeV)= "
	   << energy/GeV 
	   << "   x(mm)= "
	   << x/mm 
	   << " y(mm)= "
	   << y/mm 
	   << " z(mm)= "
	   << z/mm 
           << "   ux= " 
	   << ux 
	   << " uy= "
	   << uy
	   << " uz= "
	   << uz 
	   << G4endl;
    }

  particleGun->GeneratePrimaryVertex(anEvent);
  if(verbose > 1) G4cout << "test31PrimaryGeneratorAction: BeamOn" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void test31PrimaryGeneratorAction::SetBeamBeta(G4double val)
{
  G4ParticleDefinition* particle = particleGun->GetParticleDefinition();
  G4double mass = particle->GetPDGMass();
  if(val > 0. && val < 1.) energy = mass*(1./std::sqrt(1.-val*val) - 1.);
  G4cout << "test31PrimaryGeneratorAction: KinEnergy(MeV)= " 
         << energy/MeV << G4endl;
  minE = energy;
  maxE = energy;
  minBeta = val;
  maxBeta = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void test31PrimaryGeneratorAction::SetSigmaBeta(G4double val)
{
  G4ParticleDefinition* particle = particleGun->GetParticleDefinition();
  G4double mass = particle->GetPDGMass();
  if(val > 0. && val < 1.) {
    sigmaE = mass*(1./std::sqrt(1.-val*val) - 1.);
    G4double gamma = energy/mass + 1.;
    G4double beta0 = std::sqrt(1. - 1./(gamma*gamma));
    G4double beta  = beta0 + val;
    if (beta >= 1.) beta = 0.9999;
    maxBeta = beta;
    maxE = mass*(1./std::sqrt(1.-beta*beta) - 1.);
    beta  = beta0 - val;
    if (beta <= 0.) beta = 0.0001;
    minBeta = beta;
    minE = mass*(1./std::sqrt(1.-beta*beta) - 1.);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void test31PrimaryGeneratorAction::SetBeamSigmaE(G4double val) 
{
  G4ParticleDefinition* particle = particleGun->GetParticleDefinition();
  G4double mass = particle->GetPDGMass();
  sigmaE = val; 
  minE = energy - sigmaE;
  G4double gamma = minE/mass + 1.;
  minBeta = std::sqrt(1. - 1./(gamma*gamma));
  maxE = energy + sigmaE;
  gamma = maxE/mass + 1.;
  maxBeta = std::sqrt(1. - 1./(gamma*gamma));
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void test31PrimaryGeneratorAction::SetBeamEnergy(G4double val) 
{
  G4ParticleDefinition* particle = particleGun->GetParticleDefinition();
  G4double mass = particle->GetPDGMass();
  energy = val;
  minE = std::max(0.0,energy - sigmaE);
  minBeta = std::sqrt(minE*(minE + 2.0*mass))/(minE + mass);
  maxE = energy + sigmaE;
  maxBeta = std::sqrt(maxE*(maxE + 2.0*mass))/(maxE + mass);
  if(maxE < (test31Histo::GetPointer())->GetMaxEnergy())
    (test31Histo::GetPointer())->SetMaxEnergy(energy);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....







