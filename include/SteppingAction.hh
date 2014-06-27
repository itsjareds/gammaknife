#ifndef SteppingAction_hh
#define SteppingAction_hh
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4UserSteppingAction.hh"
#include <map>
// #include "TFile.h"
// #include "TH3F.h"
// #include "TH2F.h"
// #include "TH1F.h"
using namespace std;
class PrimaryGeneratorAction;
// class LinearTrackLengthEstimator;

class SteppingAction : public G4UserSteppingAction
    {
    public:
        SteppingAction(G4int,G4int);
        ~SteppingAction();
        void UserSteppingAction(const G4Step*);
        static inline SteppingAction* GetInstance()
            {
            return theSteppingAction;
            }

        G4double AnalogEdep;
        G4double Edep;

    private:
        static SteppingAction* theSteppingAction;
        PrimaryGeneratorAction* gen;
        int thread;
//   LinearTrackLengthEstimator* LTE;
//         TFile *f;
//         TH3F *h;
//         TH2F *h2d, *h2d2;
//         TH1F *h1d, *h1d2;

        string filenamebin,filenamesquaredbin;
        G4int nb_binsX,nb_binsY;
        float size_bins; //mm
        bool energydeposit; // 0 pour GetTotalEnergyDeposit, 1 pour Pre - post step
        bool electron;
        FILE *pf;
        float *edep, *edepsquared;
        G4int nhits;
        unsigned int nEntries;
    };

#endif
