#include "G4ParticleDefinition.hh"
#include "G4ProductionCutsTable.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "PhysicsList.hh"

// radioactive decay
// #ifdef PHASESPACE
#include "G4IonConstructor.hh"
#include "G4RadioactiveDecay.hh"
#include "G4RadioactiveDecayPhysics.hh"
// #endif

#include "G4LossTableManager.hh"
#include "G4EmProcessOptions.hh"
#include "G4VAtomDeexcitation.hh"
#include "G4UAtomicDeexcitation.hh"

// gamma
#include "G4PEEffectFluoModel.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4LivermorePhotoElectricModel.hh"
#include "G4ComptonScattering.hh"
#include "G4LivermoreComptonModel.hh"
#include "G4GammaConversion.hh"
#include "G4LivermoreGammaConversionModel.hh"
#include "G4RayleighScattering.hh"
#include "G4LivermoreRayleighModel.hh"
// e-
#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4LivermoreIonisationModel.hh"
#include "G4eBremsstrahlung.hh"
#include "G4LivermoreBremsstrahlungModel.hh"
// e+
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

#include "G4VPhysicsConstructor.hh"
#include "G4EmStandardPhysics_option3.hh"

#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"
#include "G4hMultipleScattering.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"


PhysicsList::PhysicsList(): G4VUserPhysicsList()
    {
    SetVerboseLevel(1);
    }

PhysicsList::~PhysicsList()
    {
    G4cout << "PhysicsList::Delete" << G4endl;
    }

void PhysicsList::ConstructParticle()
    {
  raddecayList = new G4RadioactiveDecayPhysics();
    // In this method, static member functions should be called for all particles which you want to use.
    // This ensures that objects of these particle types will be created in the program.
    ConstructBosons();
    ConstructLeptons();
// #ifdef PHASESPACE
    G4IonConstructor iConstructor;
    iConstructor.ConstructParticle();
// #endif
    }

// photons
void PhysicsList::ConstructBosons()
    {
    G4Gamma::GammaDefinition();
    }

// leptons e+ e-
void PhysicsList::ConstructLeptons()
    {
    G4Electron::ElectronDefinition();
    G4Positron::PositronDefinition();
 #ifdef PHASESPACE
   G4NeutrinoE::NeutrinoEDefinition();
   G4AntiNeutrinoE::AntiNeutrinoEDefinition();
 #endif
    }

void PhysicsList::ConstructProcess()
    {
 #ifdef PHASESPACE
    // Decay
  	G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();
    radioactiveDecay->SetHLThreshold(nanosecond);
    radioactiveDecay->SetICM(true);
    radioactiveDecay->SetARM(false);
  	G4ProcessManager* pmanager = G4GenericIon::GenericIon()->GetProcessManager();
  	pmanager->AddProcess(radioactiveDecay,0,-1,1);

  // Deexcitation (in case of Atomic Rearangement)
  //
  G4UAtomicDeexcitation* de = new G4UAtomicDeexcitation();
  de->SetFluo(true);
  de->SetAuger(true);
  de->SetPIXE(false);
  G4LossTableManager::Instance()->SetAtomDeexcitation(de);

	raddecayList->ConstructProcess();

 #endif

    AddTransportation();
    ConstructEM();
    }

void PhysicsList::ConstructEM()
    {
    theParticleIterator->reset();
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
    while ( (*theParticleIterator)() )
        {

        G4ParticleDefinition* particle = theParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();

        // Photon
        if (particleName == "gamma")
            {
      ph->RegisterProcess(new G4PhotoElectricEffect, particle);
      ph->RegisterProcess(new G4ComptonScattering,   particle);
      ph->RegisterProcess(new G4GammaConversion,     particle);
            // Electron
            }
        else if (particleName == "e-")
            {

      ph->RegisterProcess(new G4eMultipleScattering, particle);
      ph->RegisterProcess(new G4eIonisation,   particle);
      ph->RegisterProcess(new G4eBremsstrahlung,     particle);

/*
      G4eMultipleScattering* msc = new G4eMultipleScattering();
      msc->SetStepLimitType(fUseDistanceToBoundary);
      pmanager->AddProcess(msc,-1,1,1);

      // Ionisation
      G4eIonisation* eIonisation = new G4eIonisation();
      eIonisation->SetEmModel(new G4LivermoreIonisationModel());
      eIonisation->SetStepFunction(0.2,100*um); //improved precision in tracking
      pmanager->AddProcess(eIonisation,-1,2,2);

      // Bremsstrahlung
      G4eBremsstrahlung* eBremsstrahlung = new G4eBremsstrahlung();
      eBremsstrahlung->SetEmModel(new G4LivermoreBremsstrahlungModel());
      pmanager->AddProcess(eBremsstrahlung,-1,-3,3);
*/
            // Positron
            }
        else if (particleName == "e+")
            {


            }
        else if (particleName == "GenericIon")
            {
      ph->RegisterProcess(new G4hIonisation, particle);
      ph->RegisterProcess(new G4ionIonisation,   particle);
      ph->RegisterProcess(new G4hMultipleScattering,     particle);
      ph->RegisterProcess(new G4hBremsstrahlung,   particle);
      ph->RegisterProcess(new G4hPairProduction,     particle);
            }
        }

  G4EmProcessOptions emOptions;
  emOptions.SetFluo(true);
  emOptions.SetAuger(true);
  emOptions.SetPIXE(true);
  // Deexcitation
  G4VAtomDeexcitation* de = new G4UAtomicDeexcitation();
  de->SetFluo(true);
  de->SetAuger(true);
  de->SetPIXE(true);
  G4LossTableManager::Instance()->SetAtomDeexcitation(de);

    }

void PhysicsList::SetCuts()
    {
    // The production threshold is fixed to 0.1 mm for all the particles
    // Secondary particles with a range bigger than 0.1 mm are generated;
    // otherwise their energy is considered deposited locally

    defaultCutValue = 0.1*um;// 0.1 * mm;

    const G4double cutForGamma = defaultCutValue;
    const G4double cutForElectron = defaultCutValue;//defaultCutValue;
    const G4double cutForPositron = defaultCutValue;

    SetCutValue(cutForGamma,"gamma");
    SetCutValue(cutForElectron,"e-");
    SetCutValue(cutForPositron,"e+");

    // Set the secondary production cut lower than 990. eV
    // Very important for high precision of lowenergy processes at low energies

    G4double lowLimit = 990 *eV;
    G4double highLimit = 100 * MeV;
    G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(lowLimit,highLimit);

    /*if (verboseLevel>0)*/
    DumpCutValuesTable();
    }
