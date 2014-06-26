#ifndef PhysicsList_hh
#define PhysicsList_hh

#include "G4VUserPhysicsList.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4VModularPhysicsList.hh"
class PhysicsList: public G4VUserPhysicsList
    {
    public:
        PhysicsList();
        ~PhysicsList();

    protected:
        void ConstructParticle();
        void ConstructProcess();
        void ConstructBosons();
        void ConstructLeptons();
        void SetCuts();

    private:
        void ConstructEM();
 		G4VPhysicsConstructor*  raddecayList;
    };

#endif
