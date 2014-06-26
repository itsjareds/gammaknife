#include "StackingAction.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

StackingAction* StackingAction::theStackingAction=NULL;
StackingAction* StackingAction::GetInstance() { return theStackingAction; }

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track* aTrack) {
#ifdef PHASESPACE
  G4ParticleDefinition* part = aTrack->GetDefinition();
  G4int Z = part->GetAtomicNumber();
  if ( Z==46 || Z==52 || Z==53 || Z==77 || Z==78|| Z==27|| Z==28 ) { // Pd(46,103) I(53,125) Os(76,192) Pt(77,192) Te(52,125)
	part->SetPDGLifeTime(nanosecond);
    part->SetPDGStable(false);
  }
  G4String particleName = part->GetParticleName();
  if (( particleName=="nu_e" ) || ( particleName=="anti_nu_e" ) ) return fKill;
//   else if ( part->GetParticleName().contains("Ni60")) return fKill;
  else if ( particleName=="Ni60[0.0]" ) return fKill;
#else
 //if ( aTrack->GetParticleDefinition()->GetParticleName() != "gamma" ) return fKill;
#endif
  
  return fUrgent;
}
