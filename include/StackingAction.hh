#ifndef StackingAction_hh
#define StackingAction_hh

#include "G4TrackStatus.hh"
#include "G4UserStackingAction.hh"

class G4Track;

class StackingAction : public G4UserStackingAction {
public:
  static StackingAction* GetInstance();
  StackingAction() { theStackingAction=this; };
  ~StackingAction(){};
  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*);

private:
  static StackingAction* theStackingAction;
};

#endif
