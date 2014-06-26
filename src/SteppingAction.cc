#include "G4Step.hh"
#include "G4RegularNavigationHelper.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4VProcess.hh"
#include "TFile.h"
// #include "LinearTrackLengthEstimator.hh"
#include "SteppingAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
SteppingAction *SteppingAction::theSteppingAction=NULL;

SteppingAction::~SteppingAction() {
  theSteppingAction=NULL;
}

SteppingAction::SteppingAction(G4int thread, G4int nb) {
  theSteppingAction=this;
  gen = PrimaryGeneratorAction::GetInstance();
#ifndef PHASESPACE
  AnalogEdep = 0.;
  Edep = 0.;
#endif
}

void SteppingAction::UserSteppingAction(const G4Step* aStep) {
  G4Track *tr = aStep->GetTrack();
  G4String VolumeName = tr->GetVolume()->GetName();
  G4String proc = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName(); 
#ifdef PHASESPACE
  if ( VolumeName=="plexiPhys"  ) {
    if ( tr->GetNextVolume()->GetName()=="containerPhys" ) {
      if ( tr->GetParticleDefinition()->GetParticleName()!="gamma" ) {
        tr->SetTrackStatus(fStopAndKill);
        return;
      } else {
        G4StepPoint* postStepPoint = aStep->GetPostStepPoint();
        gen->E = postStepPoint->GetTotalEnergy();
        if ( gen->E>0 ) {
          G4ThreeVector pos = postStepPoint->GetPosition();
          gen->x = pos[0];
          gen->y = pos[1];
          gen->z = pos[2];
          G4ThreeVector mom = postStepPoint->GetMomentum();
          //gen->theta = mom.getTheta();
          //gen->phi = mom.getPhi();
          gen->t->Fill();
		  gen->dx= mom[0] / gen->E;
		  gen->dy= mom[1] / gen->E;
		  gen->dz= mom[2] / gen->E;
          
        }
        tr->SetTrackStatus(fStopAndKill);
      }
    }
    return;
  }
#else



#endif

  return;




}
