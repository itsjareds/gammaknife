#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4Gamma.hh"
#include "G4Geantino.hh"
#include "Randomize.hh"
#include "SteppingAction.hh"
#include "TFile.h"
#include "TTree.h"
#include "PrimaryGeneratorAction.hh"
#include <stdlib.h>
#include <stdio.h>
#include "G4RandomDirection.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include <G4IonTable.hh>

G4double PrimaryGeneratorAction::GetEmissionEnergy() {
  return 1.25*MeV;
}


G4ThreeVector PrimaryGeneratorAction::GetEmissionPosition() {

  G4ThreeVector v;
  G4double radius = 2.5908*mm;
  G4double length = 30.2588*mm;
  G4double   rad = G4UniformRand() * radius;   
  G4double angle = G4UniformRand() * 6.28318f;     
  v[0] = cos(angle) * rad;
  v[1] = sin(angle) * rad; 
  v[2] = G4UniformRand()*length - length/2.0;
  v[2] -= 89.3869*mm ;

  return v;//G4ThreeVector(0.3*mm,0,2*mm);
}

G4ThreeVector PrimaryGeneratorAction::GetEmissionDirection() {
  //WARINING  ISOTROPIC DISTRIBUTION
  //return G4ThreeVector(0,0,1);
  return G4RandomDirection();
}

PrimaryGeneratorAction* PrimaryGeneratorAction::theGenerator = NULL;

PrimaryGeneratorAction::~PrimaryGeneratorAction(){
  G4cout << "PrimaryGeneratorAction::Delete"<<G4endl;
  G4cout << "nPhotonsGenerated "<<nPhotonsGenerated<<G4endl;
  TString filename = Form("PhaseSpace.%d.root",thread);
  f = new TFile(filename,"recreate");
  t->Write();
  f->Close();


  delete particleGun;
  theGenerator = NULL;

// G4cout<<__LINE__<<G4endl;
}

PrimaryGeneratorAction::PrimaryGeneratorAction(G4int _thread) {
  theGenerator = this;
  thread = _thread;
  nPhotonsGenerated = 0;
  IrradiatedEnergy = 0.;

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  gamma = particleTable->FindParticle("gamma");
  positron = particleTable->FindParticle("e+");
  electron = particleTable->FindParticle("e-");



#ifdef PHASESPACE
  
  particleGun = new G4ParticleGun(1);
  // particleGun->SetParticleEnergy(GetEmissionEnergy());
  // particleGun->SetParticlePosition(GetEmissionPosition());
  // particleGun->SetParticleMomentumDirection(GetEmissionDirection());
  
  particleGun->SetParticleEnergy(0*eV);
  particleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));


//   particleGun->SetParticleDefinition(G4Gamma::Gamma());
G4cout<<"Creation PhaseSpace ..."<<G4endl;
  t = new TTree("PhaseSpace","PhaseSpace");
  t->Branch("Ekine",&E,"Ekine/F");
  t->Branch("X",&x,"X/F");
  t->Branch("Y",&y,"Y/F");
  t->Branch("Z",&z,"Z/F");
  t->Branch("dX",&dx,"dX/F");
  t->Branch("dY",&dy,"dY/F");
  t->Branch("dZ",&dz,"dZ/F");

#else

  ch = new TChain("PhaseSpace");

  ch->Add("PhaseSpace.root");
  ch->SetBranchStatus("*",0);
  ch->SetBranchStatus("Ekine",1);
  ch->SetBranchStatus("X",1);
  ch->SetBranchStatus("Y",1);
  ch->SetBranchStatus("Z",1);
  ch->SetBranchStatus("dX",1);
  ch->SetBranchStatus("dY",1);
  ch->SetBranchStatus("dZ",1);

  ch->SetBranchAddress("Ekine",&E);
  ch->SetBranchAddress("X",&x);
  ch->SetBranchAddress("Y",&y);
  ch->SetBranchAddress("Z",&z);
  ch->SetBranchAddress("dX",&dx);
  ch->SetBranchAddress("dY",&dy);
  ch->SetBranchAddress("dZ",&dz);
  
  
  G4cout<<"Read PhaseSpace ..."<<G4endl;
  particleGun = new G4ParticleGun();
  particleGun->SetParticleDefinition(G4Gamma::Gamma());


  
    G4cout<<"PhaseSpace read"<<G4endl;
#endif
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

#ifdef PHASESPACE
  /*
if ( particleGun->GetParticleDefinition()==G4Geantino::Geantino() ) {
G4int Z = 27, A = 60;
G4double excitEnergy = 0.*keV;
G4double ionCharge = 0.*eplus;
G4ParticleDefinition* ion = G4ParticleTable::GetParticleTable()->GetIon(Z,A,excitEnergy);
//G4ParticleDefinition* ion = G4IonTable::FindIon(Z,A,excitEnergy);

particleGun->SetParticleDefinition(ion);
particleGun->SetParticleCharge(ionCharge);
  }
*/
  particleGun->SetParticleEnergy( GetEmissionEnergy() );
  particleGun->SetParticleDefinition(gamma);


  particleGun->SetParticlePosition( GetEmissionPosition());
  particleGun->SetParticleMomentumDirection(GetEmissionDirection());

#else

  ch->LoadTree(nPhotonsGenerated);
  ch->GetEntry( nPhotonsGenerated );
  ParticlePosition = G4ThreeVector(x,y,z);
  ParticleMomentum = G4ThreeVector(dx,dy,dz); //.setRThetaPhi(1.,theta,phi);
  particleGun->SetParticlePosition( ParticlePosition );
  particleGun->SetParticleMomentumDirection( ParticleMomentum );
  particleGun->SetParticleEnergy( E );

#endif

  if(nPhotonsGenerated % 100000 == 0) G4cout<<"Particle .... "<<nPhotonsGenerated<<G4endl;
  particleGun->GeneratePrimaryVertex( anEvent );
  IrradiatedEnergy += E;
  nPhotonsGenerated++;
}
