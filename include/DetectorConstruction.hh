#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh

#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

class G4VPhysicalVolume;
class G4Material;

class DetectorConstruction : public G4VUserDetectorConstruction
    {
    public:
        DetectorConstruction();
        ~DetectorConstruction();

        G4VPhysicalVolume* Construct();
        static inline DetectorConstruction* GetInstance()
            {
            return theDetector;
            }

    private:
        static DetectorConstruction* theDetector;
        G4Material* Water;

        // volumes logiques
        //
        G4LogicalVolume* World_log;
        G4LogicalVolume* Cible_log, *ni_log, *cu_log, *caps_log, *gap_log, *alu_log, *RCap_log,* LCap_log, *RGap_log,* LGap_log, *RAlu_log,* LAlu_log, *Core_log, *scoring_log, *au_log, *be_log, *n_log, *betube_log, *nitube_log;

        // volumes physiques
        //
        G4VPhysicalVolume* World_phys;
        G4VPhysicalVolume* Cible_phys, *Caps_phys, *gap_phys, *alu_phys,*RCap_phys,*LCap_phys,*RGap_phys,*LGap_phys, *RAlu_phys,*LAlu_phys, *ni_phys,*cu_phys, *core_phys, *scoring_phys, *Au_phys, *Be_phys, *N_phys, *Betube_phys, *Nitube_phys;

    };

#endif
