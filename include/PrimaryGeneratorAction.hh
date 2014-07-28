#ifndef PrimaryGeneratorAction_hh
#define PrimaryGeneratorAction_hh

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "TTree.h"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "TFile.h"
#include "TChain.h"



using namespace std;

//class G4ParticleGun;
//class VSeed;
//class TFile;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
    {
    public:
        PrimaryGeneratorAction(G4int);
        ~PrimaryGeneratorAction();
        G4double GetEmissionEnergy();
        G4ThreeVector GetEmissionPosition();
        G4ThreeVector GetEmissionDirection();
        static inline PrimaryGeneratorAction* GetInstance()
            {
            return theGenerator;
            }
        void GeneratePrimaries(G4Event* anEvent);
        G4int Getnhits()
            {
            return nPhotonsGenerated;
            }
//   VSeed* GetSeed() { return s; }

        G4int nPhotonsGenerated; // number of primary photons thrown
        G4double IrradiatedEnergy;
        G4int procId;

        TFile *f;
        TTree *t;
        TChain *ch;
        float x,y,z,theta,phi,E,dx,dy,dz;
        string volume;

    private:
        static PrimaryGeneratorAction* theGenerator;
        G4ParticleGun* particleGun;
        G4ThreeVector ParticlePosition;
        G4ThreeVector ParticleMomentum;

        G4ParticleDefinition* gamma;
        G4ParticleDefinition* positron;
        G4ParticleDefinition* electron;

//   VSeed *s;
    };

#endif
