#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PhantomParameterisation.hh"
#include "G4PVParameterised.hh"
#include "G4VisAttributes.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
// #include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "G4UnionSolid.hh"
// #include "G4GDMLParser.hh"

#include "G4PhysicalConstants.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4EllipticalCone.hh"
#include "G4SubtractionSolid.hh"
#include "G4Cons.hh"

//#define COLL4
//#define COLL8
#define COLL14
//#define COLL18

DetectorConstruction* DetectorConstruction::theDetector=NULL;
DetectorConstruction::~DetectorConstruction()
    {
    G4cout << "DetectorConstruction::Delete";
    theDetector=NULL;
    G4cout << " ... done" << G4endl;
    }

DetectorConstruction::DetectorConstruction()
    {
    theDetector=this;

    // Define Materials
    G4NistManager* man = G4NistManager::Instance();
    G4Element* elH = man->FindOrBuildElement(1);
    G4Element* elO = man->FindOrBuildElement(8);
//   Water = new G4Material("Water",0.998*g/cm3,2);
//   Water->AddElement(elH,2);
//   Water->AddElement(elO,1);
    Water = man->FindOrBuildMaterial("G4_WATER");
    }

G4VPhysicalVolume* DetectorConstruction::Construct()
    {
  G4cout << "DetectorConstruction::Construct" << G4endl;


  G4double A;  // masse molaire
  G4double Z;  // numero atomique

  G4double density, temperature, pressure;

  A = 14.01*g/mole;
  Z = 7.;
  G4Element* elN = new G4Element("Nitrogen","N",Z ,A);

  A = 16.00*g/mole;
  Z = 8.;
  G4Element* elO = new G4Element("Oxygen","O",Z ,A);

  A = 1.00*g/mole;
  Z = 1.;
  G4Element* elH = new G4Element("Hydrogen","H",Z ,A);


  // Definition des materiaux //

  density = 1.290*mg/cm3;


  G4Colour  white   (1.0, 1.0, 1.0);   // white
  G4Colour  gray    (0.5, 0.5, 0.5);   // gray
  G4Colour  black   (0.0, 0.0, 0.0);   // black
  G4Colour  brown   (0.45,0.25,0.0);   // G4 logo brown
  G4Colour  red     (1.0, 0.0, 0.0);   // red
  G4Colour  green   (0.0, 1.0, 0.0);   // green
  G4Colour  blue    (0.0, 0.0, 1.0);   // blue
  G4Colour  cyan    (0.0, 1.0, 1.0);   // cyan
  G4Colour  magenta (1.0, 0.0, 1.0);   // magenta
  G4Colour  yellow  (1.0, 1.0, 0.0);   // yellow

  // L'objet materiau peut etre defini de plusieurs manieres
  // On peut le definir lors de l'instantiation
  // par une densite et un nombre d'elements qui le compose
  // exemple : l'air est compose de 2 elements : oxygene et azote

  //   G4Material* Air = new G4Material("Air",density,2);

  // On definit les elements du materiau avec la methode AddElement
  // dont le 2eme argument F est :
  // - une fraction massique si F est reel
  // - un coefficient stoechiometrique si F est entier

  //   Air->AddElement(elN, 0.7);
  //   Air->AddElement(elO, 0.3);

  //Definition du materiau eau

  density = 1.0*g/cm3;

  G4Material* Eau = new G4Material("Eau",density,2);

  Eau->AddElement(elH, 2);
  Eau->AddElement(elO, 1);

  // Definition du materiau "Vide"

  density = universe_mean_density;
  pressure = 3.e-18*pascal;
  temperature = 2.73*kelvin;
  A=1.01*g/mole;
  Z = 1.;
  G4Material*  Vide = new G4Material("Galactic", Z, A,density,kStateGas,temperature,pressure);

  G4double World_x = 300*mm;
  G4double World_y = 300*mm;
  G4double World_z = 300*mm;

  // un volume est defini en 3 etapes :
  // - definition de la forme
  // - definition du volume "logique" = forme + materiau
  // - definition du volume "physique" = volume logique + position
  G4Material* Air = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");

  G4Box* World_box = new G4Box("World_box",World_x,World_y,World_z);

  World_log = new G4LogicalVolume(World_box,Vide,"World_log",0,0,0);

  World_phys = new G4PVPlacement(0,G4ThreeVector(),World_log,"World_phys",0,false,0);


  G4int nel;
  G4double  a, z;
  G4String name, symbol;
  G4Element* el_H  = new G4Element(name="H",symbol="H" , z= 1., a= 1.01*g/mole);
  G4Element* el_C  = new G4Element(name="C"  ,symbol="C" , z= 6., a= 12.01*g/mole);
  G4Element* el_O  = new G4Element(name="O"  ,symbol="O" , z= 8., a= 16.00*g/mole);
  G4Element* el_I  = new G4Element(name="I", symbol="I", z=53.0,a=126.90447*g/mole);

  G4Element* el_Al = new G4Element(name="Al",symbol="Al",z=13.0,a=26.98*g/mole);
  G4Element* el_Au = new G4Element(name="Au",symbol="Au",z=79.0,a=196.967*g/mole);
  G4Element* el_Ni = new G4Element(name="Ni",symbol="Ni",z=28.0,a=58.693*g/mole);
  G4Element* el_Cu = new G4Element(name="Cu",symbol="Cu",z=29.0,a=63.39*g/mole);
  G4Element* el_Ti = new G4Element(name="Ti",symbol="Ti",z=22.0,a=47.867*g/mole);
  G4Element* el_Be = new G4Element(name="Be",symbol="Be",z=4.0, a=9.012*g/mole);
  G4Element* el_Fe = new G4Element("Iron", symbol="Fe", z=26., a=55.845*g/mole);
  G4Element* el_Cr = new G4Element(name="Cr",symbol="Cr",z=24.0,a=51.996*g/mole);
  G4Element* el_N = new G4Element(name="N",symbol="N",z=7.0, a=14.01*g/mole);
  G4Element* el_W  = new G4Element("Tungsten", symbol="W", z=74., a=183.84*g/mole);

  G4Material* mat_Ti =  new G4Material(name="mat_Ti",density=4.54*g/cm3,nel=1);
  mat_Ti->AddElement(el_Ti,1);

  G4Material* mat_Alu = new G4Material(name="mat_Alu",density=2.7*g/cm3,nel=1);
  mat_Alu->AddElement(el_Al,1);

  G4Material* mat_Au = new G4Material(name="mat_Au",density=19.3*g/cm3,nel=1);
  mat_Au->AddElement(el_Au,1);

  G4Material* mat_Cu = new G4Material(name="mat_Cu",density=8.96*g/cm3,nel=1);
  mat_Cu->AddElement(el_Cu,1);

  G4Material* mat_Ni = new G4Material(name="mat_Ni",density=8.902*g/cm3,nel=1);
  mat_Ni->AddElement(el_Ni,1);

  G4Material* mat_Be = new G4Material(name="mat_Be",density=1.848*g/cm3,nel=1);
  mat_Be->AddElement(el_Ni,1);

  G4Material* mat_nitrure = new G4Material(name="mat_Nitrure",density=4.91*g/cm3,nel=2);
  mat_nitrure->AddElement(el_N,1);
  mat_nitrure->AddElement(el_Cr,1);

  G4Material* mat_iron = new G4Material("mat_iron", density=7.874*g/cm3, nel=1);
  mat_iron->AddElement(el_Fe, 1);

  G4Material* mat_tungsten = new G4Material("Tungsten", density=19.25*g/cm3, nel=1);
  mat_tungsten->AddElement(el_W, 1);


  G4Material * mat_plexiglas = new G4Material("Plexiglas", density= 1.19*g/cm3, nel=3);
  mat_plexiglas->AddElement(el_H, 0.0805);
  mat_plexiglas->AddElement(el_C, 0.5999);
  mat_plexiglas->AddElement(el_O, 0.3196);

#ifdef PHASESPACE

  //################################################################
  // Define the collimator geometry
  //################################################################


  //####device container
  G4double containerOuterDiam= 107.6352*mm;
  G4double containerHeight = 50.0126*mm + 51.5*2*mm + 89*mm + 1.5*mm;
  G4double containerPosX=0.0*mm;
  G4double containerPosY=0.0*mm;
  G4double containerPosZ=0.0*mm;

  G4Tubs* containerSolid = new G4Tubs("containerSolid", 0, containerOuterDiam/2., containerHeight/2., 0.0, 2.0*pi);

  G4VisAttributes* container_att = new G4VisAttributes(yellow);
  G4LogicalVolume* container = new G4LogicalVolume(containerSolid, Air, "container",0,0,0);

  container->SetVisAttributes(container_att);
  G4RotationMatrix* zero_rotation = new G4RotationMatrix();
  G4PVPlacement* containerPhys = new G4PVPlacement(zero_rotation, G4ThreeVector(containerPosX,containerPosY,containerPosZ), container, "containerPhys", World_log, false, 0);


  //####outer container

  G4double largestTubeInnerDiam=12.1412;
  G4double largestTubeOuterDiam=27.6351;
  G4double largestTubeHeight = 50.0126;
  G4double largestTubePosX=0.0;
  G4double largestTubePosY=0.0;
  G4double largestTubePosZ=largestTubeHeight/2 - containerHeight/2;

  G4Tubs* largestTube = new G4Tubs("largestTube", largestTubeInnerDiam/2, largestTubeOuterDiam/2, largestTubeHeight/2., 0.0, 2.0*pi);
  G4VisAttributes* largestTube_att = new G4VisAttributes(red);
  //uncomment later
  G4LogicalVolume* largestTubeLogic = new G4LogicalVolume(largestTube, /*material=*/mat_iron, /*name=*/"largestTubeLogic");
  largestTubeLogic->SetVisAttributes(largestTube_att);
      //, /*color=*/skin);
  //uncomment later
  G4PVPlacement* largestTubePhys = new G4PVPlacement(zero_rotation, G4ThreeVector(largestTubePosX,largestTubePosY,largestTubePosZ), largestTubeLogic, "largestTubePhys", container, false, 0);


  //####middle container

  G4double middleTubeInnerDiam=7.112;
  G4double middleTubeOuterDiam=11.6078;
  G4double middleTubeHeight=36.4236;
  G4double middleTubePosX=0.0;
  G4double middleTubePosY=0.0;
  G4double middleTubePosZ= ( (largestTubeHeight-middleTubeHeight)/2 - 1.4224 + largestTubeHeight/2 ) - containerHeight/2;

  G4Tubs* middleTube = new G4Tubs("middleTube", middleTubeInnerDiam/2, middleTubeOuterDiam/2, middleTubeHeight/2., 0.0, 2.0*pi);
  G4VisAttributes* middleTube_att = new G4VisAttributes(blue);
  //uncomment later
  G4LogicalVolume* middleTubeLogic = new G4LogicalVolume(middleTube, /*material=*/mat_iron, /*name=*/"middleTubeLogic");
  middleTubeLogic->SetVisAttributes(middleTube_att);
      //, /*color=*/fat);
  //uncomment later
  G4PVPlacement* middleTubePhys = new G4PVPlacement(zero_rotation, G4ThreeVector(middleTubePosX,middleTubePosY,middleTubePosZ), middleTubeLogic, "middleTubePhys", container, false, 0);
  //middleTubeLogic.SetForceWireFrame(1)

  //#sourceAssembly.AddPlacedVolume( middleTubeLogic, pos=(middleTubePosX,middleTubePosY,middleTubePosZ) )


  //####inner container

  G4double smallestTubeInnerDiam=2.5908;
  G4double smallestTubeOuterDiam=6.604;
  G4double smallestTubeHeight=32.9438;
  G4double smallestTubePosX=0.0;
  G4double smallestTubePosY=0.0;
  G4double smallestTubePosZ=( (largestTubeHeight-smallestTubeHeight) /2 - 1.4224 -0.4064 + largestTubeHeight/2 ) - containerHeight/2;

  G4Tubs* smallestTube = new G4Tubs("smallestTube", smallestTubeInnerDiam/2, smallestTubeOuterDiam/2, smallestTubeHeight/2., 0.0, 2.0*pi);
  G4VisAttributes* smallestTubeLogic_att = new G4VisAttributes(green);

  G4LogicalVolume* smallestTubeLogic = new G4LogicalVolume(smallestTube, mat_iron, "smallestTubeLogic");

  smallestTubeLogic->SetVisAttributes(smallestTubeLogic_att);

  G4PVPlacement* smallestTubePhys = new G4PVPlacement(zero_rotation, G4ThreeVector(smallestTubePosX,smallestTubePosY, smallestTubePosZ), smallestTubeLogic, "smallestTubePhys", container, false, 0);


  //####cap of the outer container

  G4double largestCapInnerDiam=8;
  //#largestCapOuterDiam=27.6351
  G4double largestCapOuterDiam=middleTubeOuterDiam;
  G4double largestCapHeight=1.4224;
  G4double largestCapPosX=0.0;
  G4double largestCapPosY=0.0;
  G4double largestCapPosZ=(largestTubeHeight/2 - 1.4224/2 + largestTubeHeight/2) - containerHeight/2;

  G4Tubs* largestCap = new G4Tubs("largestCap", largestCapInnerDiam/2, largestCapOuterDiam/2, largestCapHeight/2., 0.0, 2.0*pi);
  G4VisAttributes* largestCapLogic_att = new G4VisAttributes(white);

  G4LogicalVolume* largestCapLogic = new G4LogicalVolume(largestCap, /*material=*/mat_iron, /*name=*/"largestCapLogic");
  largestCapLogic->SetVisAttributes(largestCapLogic_att);

  G4PVPlacement* largestCapPhys = new G4PVPlacement(zero_rotation, G4ThreeVector(largestCapPosX,largestCapPosY,largestCapPosZ), largestCapLogic, "largestCapPhys", container, false, 0);
  //largestCapLogic.SetForceWireFrame(1)

  //#sourceAssembly.AddPlacedVolume( largestCapLogic, pos=(largestCapPosX,largestCapPosY,largestCapPosZ) )



  //####cap of the middle container

  G4double middleCapInnerDiam=0;
  //#middleCapOuterDiam=11.6078;
  G4double middleCapOuterDiam=smallestTubeOuterDiam;
  G4double middleCapHeight=0.4064;
  G4double middleCapPosX=0.0;
  G4double middleCapPosY=0.0;
  G4double middleCapPosZ=( (largestTubeHeight -middleCapHeight)/2 - largestCapHeight + largestTubeHeight/2 ) - containerHeight/2;

  G4Tubs* middleCap = new G4Tubs("middleCap", middleCapInnerDiam/2, middleCapOuterDiam/2, middleCapHeight/2., 0.0, 2.0*pi);
  G4VisAttributes* middleCapLogic_att = new G4VisAttributes(magenta);

  G4LogicalVolume* middleCapLogic = new G4LogicalVolume(middleCap, /*material=*/mat_iron, /*name=*/"middleCapLogic");

  middleCapLogic->SetVisAttributes(middleCapLogic_att);
  G4PVPlacement* middleCapPhys = new G4PVPlacement(zero_rotation, G4ThreeVector(middleCapPosX,middleCapPosY,middleCapPosZ), middleCapLogic, "middleCapPhys", container, false, 0);
  //middleCapLogic.SetForceWireFrame(1)

  //#sourceAssembly.AddPlacedVolume( middleCapLogic, pos=(middleCapPosX,middleCapPosY,middleCapPosZ) )


  //####cap of the inner container

  G4double smallestCapInnerDiam=0. * mm;
  G4double smallestCapOuterDiam=2.5908 * mm;
  G4double smallestCapHeight=0.685 * mm;
  G4double smallestCapPosX=0.0 * mm;
  G4double smallestCapPosY=0.0 * mm;
  G4double smallestCapPosZ=( (50.0126*mm - 32.9438*mm ) /2.*mm - 1.4224*mm -0.4064*mm  + (smallestTubeHeight - smallestCapHeight )/2. + largestTubeHeight/2. ) - containerHeight/2.;

  G4Tubs* smallestCap = new G4Tubs("smallestCap", smallestCapInnerDiam/2, smallestCapOuterDiam/2, smallestCapHeight/2., 0.0, 2.0*pi);

  G4EllipticalCone* smallestCapCone = new G4EllipticalCone( "smallestCapCone", smallestCapOuterDiam/2, smallestCapOuterDiam/2, 0.7/2, 0.7/2);

  G4SubtractionSolid* smallestCapSolid = new G4SubtractionSolid("smallestCap-smallestCapCone", smallestCap, smallestCapCone);
  G4VisAttributes* smallestCapSolid_att = new G4VisAttributes(cyan);

  G4LogicalVolume* smallestCapLogic = new G4LogicalVolume(smallestCapSolid, /*material=*/mat_iron, /*name=*/"smallestCapLogic");
  smallestCapLogic->SetVisAttributes(smallestCapSolid_att);

  G4PVPlacement* smallestCapPhys = new G4PVPlacement(zero_rotation, G4ThreeVector(smallestCapPosX,smallestCapPosY,smallestCapPosZ), smallestCapLogic, "smallestCapPhys", container, false, 0);
  //smallestCapLogic.SetForceSolid(1)

  //#sourceAssembly.AddPlacedVolume( smallestCapLogic, pos=(smallestCapPosX,smallestCapPosY,smallestCapPosZ) )



  //####backcap of the outer container

  G4double largestBackCapInnerDiam=0. * mm;
  //#largestBackCapOuterDiam=27.6352;
  G4double largestBackCapOuterDiam=middleTubeOuterDiam;
  G4double largestBackCapHeight=2.2606 * mm;
  G4double largestBackCapPosX=0.0 * mm;
  G4double largestBackCapPosY=0.0 * mm;
  G4double largestBackCapPosZ= (-largestTubeHeight/2. + largestBackCapHeight/2.  + largestTubeHeight/2.) -containerHeight/2.;

  G4Tubs* largestBackCap = new G4Tubs("largestBackCap", largestBackCapInnerDiam/2., largestBackCapOuterDiam/2., largestBackCapHeight/2., 0.0, 2.0*pi);
  G4VisAttributes* largestBackCapLogic_att = new G4VisAttributes(yellow);

  G4LogicalVolume* largestBackCapLogic = new G4LogicalVolume(largestBackCap, /*material=*/mat_iron, /*name=*/"largestBackCapLogic");
  largestBackCapLogic->SetVisAttributes(largestBackCapLogic_att);
  G4PVPlacement* largestBackCapPhys = new G4PVPlacement(zero_rotation, G4ThreeVector(largestBackCapPosX,largestBackCapPosY,largestBackCapPosZ), largestBackCapLogic, "largestBackCapPhys", container, false, 0);
  //largestBackCapLogic.SetForceWireFrame(1)

  //#sourceAssembly.AddPlacedVolume( largestBackCapLogic, pos=(largestBackCapPosX,largestBackCapPosY,largestBackCapPosZ) )


  //####backcap of the middle container

  G4double middleBackCapInnerDiam=0. * mm;
  //#middleBackCapOuterDiam=11.6078
  G4double middleBackCapOuterDiam=smallestTubeOuterDiam;
  G4double middleBackCapHeight=2.0574 * mm;
  G4double middleBackCapPosX=0.0 * mm;
  G4double middleBackCapPosY=0.0 * mm;
  G4double middleBackCapPosZ=( middleTubePosZ-middleTubeHeight/2. + middleBackCapHeight/2. );

  G4Tubs* middleBackCap = new G4Tubs("middleBackCap", middleBackCapInnerDiam/2., middleBackCapOuterDiam/2., middleBackCapHeight/2., 0.0, 2.0*pi);
  G4VisAttributes* middleBackCapLogic_att = new G4VisAttributes(green);

  G4LogicalVolume* middleBackCapLogic = new G4LogicalVolume(middleBackCap, /*material=*/mat_iron, /*name=*/"middleBackCapLogic");

  middleBackCapLogic->SetVisAttributes(middleBackCapLogic_att);
  G4PVPlacement* middleBackCapPhys = new G4PVPlacement(zero_rotation, G4ThreeVector(middleBackCapPosX,middleBackCapPosY,middleBackCapPosZ), middleBackCapLogic, "middleBackCapPhys", container, false, 0);


  //####backcap of the inner container

  G4double smallestBackCapInnerDiam=0. * mm;
  //#smallestBackCapOuterDiam=6.64
  G4double smallestBackCapOuterDiam=smallestTubeInnerDiam;
  G4double smallestBackCapHeight=2. * mm;
  G4double smallestBackCapPosX=0.0 * mm;
  G4double smallestBackCapPosY=0.0 * mm;
  G4double smallestBackCapPosZ=( smallestTubePosZ - smallestTubeHeight/2. + smallestBackCapHeight/2. );

  G4Tubs* smallestBackCap = new G4Tubs("smallestBackCap", smallestBackCapInnerDiam/2., smallestBackCapOuterDiam/2., smallestBackCapHeight/2., 0.0, 2.0*pi);
  G4VisAttributes* smallestBackCapLogic_att = new G4VisAttributes(white);

  G4LogicalVolume* smallestBackCapLogic = new G4LogicalVolume(smallestBackCap, /*material=*/mat_iron, /*name=*/"smallestBackCapLogic");
  smallestBackCapLogic->SetVisAttributes(smallestBackCapLogic_att);

  G4PVPlacement* smallestBackCapPhys = new G4PVPlacement(zero_rotation, G4ThreeVector(smallestBackCapPosX,smallestBackCapPosY,smallestBackCapPosZ), smallestBackCapLogic, "smallestBackCapPhys", container, false, 0);

  //####Cobalt filling

  G4double cobaltInnerDiam=0. * mm;
  G4double cobaltOuterDiam=smallestTubeInnerDiam;
  G4double cobaltHeight=smallestTubeHeight - smallestBackCapHeight - smallestCapHeight;
  G4double cobaltPosX=0.0 * mm;
  G4double cobaltPosY=0.0 * mm;
  G4double cobaltPosZ=( smallestTubePosZ + (smallestTubeHeight - cobaltHeight )/2. - smallestCapHeight  )*mm;


  G4Tubs* cobalt = new G4Tubs("cobalt", cobaltInnerDiam/2., cobaltOuterDiam/2., cobaltHeight/2., 0.0, 2.0*pi);
  G4VisAttributes* cobaltLogic_att = new G4VisAttributes(black);

  G4LogicalVolume* cobaltLogic = new G4LogicalVolume(cobalt, /*material=*/mat_iron, /*name=*/"cobaltLogic");
  cobaltLogic->SetVisAttributes(cobaltLogic_att);
  G4PVPlacement* cobaltPhys = new G4PVPlacement(zero_rotation, G4ThreeVector(cobaltPosX,cobaltPosY,cobaltPosZ), cobaltLogic, "cobaltPhys", container, false, 0);
  //cobaltLogic.SetForceWireFrame(1)

  //#sourceAssembly.AddPlacedVolume( cobaltLogic, pos=(cobaltPosX,cobaltPosY,cobaltPosZ) )



  //####Tungsten plug
  //note: units converted in->mm from spec sheet

  G4double tungstenPlugInnerDiam=0. * mm;
  G4double tungstenPlugOuterDiam=12.0142 * mm;
  G4double tungstenPlugHeight=9.271 * mm;
  G4double tungstenPlugPosX=0.0 * mm;
  G4double tungstenPlugPosY=0.0 * mm;
  G4double tungstenPlugPosZ=(middleTubePosZ-middleTubeHeight/2. -tungstenPlugHeight/2. );

  G4Tubs* tungstenPlug = new G4Tubs("tungstenPlug", tungstenPlugInnerDiam/2., tungstenPlugOuterDiam/2., tungstenPlugHeight/2., 0.0, 2.0*pi);
  G4VisAttributes* tungstenPlugLogic_att = new G4VisAttributes(red);

  G4LogicalVolume* tungstenPlugLogic = new G4LogicalVolume(tungstenPlug, /*material=*/mat_tungsten, /*name=*/"tungstenPlugLogic");
      //, /*color=*/skin);
  //uncomment later
  tungstenPlugLogic->SetVisAttributes(tungstenPlugLogic_att);
  G4PVPlacement* tungstenPlugPhys = new G4PVPlacement(zero_rotation, G4ThreeVector(tungstenPlugPosX,tungstenPlugPosY,tungstenPlugPosZ), tungstenPlugLogic, "tungstenPlugPhys", container, false, 0);
  //tungstenPlugLogic.SetForceWireFrame(1)

  //#sourceAssembly.AddPlacedVolume( tungstenPlugLogic, pos=(tungstenPlugPosX,tungstenPlugPosY,tungstenPlugPosZ) )


  //####primary coll

  G4double primaryCollInnerDiam=6.5 * mm;
  G4double primaryCollOuterDiam=25. * mm;
  G4double primaryCollHeight=51.5 * mm;
  G4double primaryCollPosX=0.0 * mm;
  G4double primaryCollPosY=0.0 * mm;
  G4double primaryCollPosZ= (50.0126 + primaryCollHeight  + largestTubeHeight - containerHeight) * mm / 2.;

  G4Tubs* primaryColl = new G4Tubs("primaryColl", primaryCollInnerDiam/2., primaryCollOuterDiam/2., primaryCollHeight/2., 0.0, 2.0*pi);
  //uncomment later
  G4VisAttributes* primaryCollLogic_att = new G4VisAttributes(red);
  G4LogicalVolume* primaryCollLogic = new G4LogicalVolume(primaryColl, /*material=*/mat_tungsten, /*name=*/"primaryCollLogic");

  primaryCollLogic->SetVisAttributes(primaryCollLogic_att);
  G4PVPlacement* primaryCollPhys = new G4PVPlacement(zero_rotation, G4ThreeVector(primaryCollPosX,primaryCollPosY,primaryCollPosZ), primaryCollLogic, "primaryCollPhys", container, false, 0);
  //primaryCollLogic.SetForceWireFrame(1)

  //sourceAssembly.AddPlacedVolume( primaryCollLogic, pos=(primaryCollPosX,primaryCollPosY,primaryCollPosZ) )



  G4double primaryColl2InnerDiam=6.5 * mm;
  G4double primaryColl2OuterDiam=25. * mm;
  G4double primaryColl2Height=51.5 * mm;
  G4double primaryColl2PosX=0.0 * mm;
  G4double primaryColl2PosY=0.0 * mm;
  G4double primaryColl2PosZ=( primaryCollPosZ +  primaryColl2Height ) * mm;

  G4Tubs* primaryColl2 = new G4Tubs("primaryColl2", primaryColl2InnerDiam/2., primaryColl2OuterDiam/2., primaryColl2Height/2., 0.0, 2.0*pi);

  G4VisAttributes* primaryColl2Logic_att = new G4VisAttributes(blue);
  G4LogicalVolume* primaryColl2Logic = new G4LogicalVolume(primaryColl2, /*material=*/mat_tungsten, /*name=*/"primaryColl2Logic");

  primaryColl2Logic->SetVisAttributes(primaryColl2Logic_att);
  G4PVPlacement* primaryColl2Phys = new G4PVPlacement(zero_rotation, G4ThreeVector(primaryColl2PosX,primaryColl2PosY,primaryColl2PosZ), primaryColl2Logic, "primaryColl2Phys", container, false, 0);
  //primaryColl2Logic.SetForceWireFrame(1)

  //sourceAssembly.AddPlacedVolume( primaryColl2Logic, pos=(primaryColl2PosX,primaryColl2PosY,primaryColl2PosZ) )

  G4double collOuterDiam=20. * mm;
  G4double collHeight=89. * mm;
  G4double collPosX=0.0 * mm;
  G4double collPosY=0.0 * mm;
  G4double collPosZ=( primaryColl2PosZ + collHeight/2. + primaryColl2Height/2. + 1.5 );

//####Secondary collimator 4/8/14/18 mm
  G4Tubs* collbody = new G4Tubs("collbody", 0.0, collOuterDiam/2, collHeight/2, 0.0, 2.0*pi);

  G4Cons* collconeontheleft = new G4Cons("collconeontheleft",0.0, 7.85*mm/2, 0.0, 9.0*mm/2, 1.0*mm/2, 0.0, 2.0*pi);
#if defined COLL4
  //FIXME: get correct dimensions
  collconeontheleft = new G4Cons("collconeontheleft",0.0, 2.61*mm/2, 0.0, 3.75*mm/2, 1.0*mm/2, 0.0, 2.0*pi);
  G4Cons* collconeinthemiddle = new G4Cons("collconeinthemiddle",0.0, 2.6*mm/2, 0.0, 2.6*mm/2, collHeight/2, 0.0, 2.0*pi);
  //FIXME: get correct dimensions
  G4Cons* collconeontheright = new G4Cons("collconeontheright",0.0, 3.75*mm/2, 0.0, 2.6*mm/2, 1.0*mm/2, 0.0, 2.0*pi);
#elif defined COLL8
  G4Cons* collconeinthemiddle = new G4Cons("collconeinthemiddle",0.0, 3.5*mm/2, 0.0, 7.85*mm/2, collHeight/2, 0.0, 2.0*pi);
  //FIXME: get correct dimensions
  G4Cons* collconeontheright = new G4Cons("collconeontheright",0.0, 4.65*mm/2, 0.0, 3.5*mm/2, 1.0*mm/2, 0.0, 2.0*pi);
#elif defined COLL14
  G4Cons* collconeinthemiddle = new G4Cons("collconeinthemiddle",0.0, 5.0*mm/2, 0.0, 7.85*mm/2, collHeight/2, 0.0, 2.0*pi);
  G4Cons* collconeontheright = new G4Cons("collconeontheright",0.0, 6.15*mm/2, 0.0, 5.0*mm/2, 1.0*mm/2, 0.0, 2.0*pi);
#elif defined COLL18
  G4Cons* collconeinthemiddle = new G4Cons("collconeinthemiddle",0.0, 6.0*mm/2, 0.0, 7.85*mm/2, collHeight/2, 0.0, 2.0*pi);
  //FIXME: get correct dimensions
  G4Cons* collconeontheright = new G4Cons("collconeontheright",0.0, 7.15*mm/2, 0.0, 6.0*mm/2, 1.0*mm/2, 0.0, 2.0*pi);
#else
  G4cerr << "***** WARNING: Secondary collimator diameter not set. Defaulting to 14mm." << G4endl;
  G4Cons* collconeinthemiddle = new G4Cons("collconeinthemiddle",0.0, 5.0*mm/2, 0.0, 7.85*mm/2, collHeight*mm/2, 0.0, 2.0*pi);
  //FIXME: get correct dimensions
  G4Cons* collconeontheright = new G4Cons("collconeontheright",0.0, 6.15*mm/2, 0.0, 5.0*mm/2, 1.0*mm/2, 0.0, 2.0*pi);
#endif

// Subtract shaped hole from center of collimator body
  G4RotationMatrix* rotationa = new G4RotationMatrix();
  G4SubtractionSolid* colla = new G4SubtractionSolid("collbody-collconeinthemiddle", collbody, collconeinthemiddle,rotationa , G4ThreeVector(0.0 ,0.0, 0.0));
  G4RotationMatrix* rotationb = new G4RotationMatrix();
  G4SubtractionSolid* collb = new G4SubtractionSolid("collbody-collconeinthemiddle-collconeontheleft", colla, collconeontheleft, rotationb, G4ThreeVector(0.0 ,0.0, collHeight/2));
  G4RotationMatrix* rotation = new G4RotationMatrix();
  G4SubtractionSolid* coll = new G4SubtractionSolid("collbody-collconeinthemiddle-collconeontheleft-collconeontheright", collb, collconeontheright,rotation , G4ThreeVector(0.0 ,0.0, -collHeight/2));

  G4VisAttributes* collLogic_att = new G4VisAttributes(magenta);
  G4LogicalVolume* collLogic = new G4LogicalVolume(coll, /*material=*/mat_tungsten, /*name=*/"collLogic");

  collLogic->SetVisAttributes(collLogic_att);
  G4PVPlacement* collPhys = new G4PVPlacement(zero_rotation, G4ThreeVector(collPosX,collPosY,collPosZ), collLogic, "collPhys", container, false, 0);

  //####Source shielding

  G4double sourceShieldingInnerDiam=27.6352 * mm;
  G4double sourceShieldingOuterDiam=107.6352 * mm;
  G4double sourceShieldingHeight=50.0126*mm + 103.*mm;
  G4double sourceShieldingPosX=0.0*mm;
  G4double sourceShieldingPosY=0.0*mm;
  G4double sourceShieldingPosZ= sourceShieldingHeight/2 - containerHeight/2;

  G4Tubs* sourceShielding = new G4Tubs("sourceShielding", sourceShieldingInnerDiam/2, sourceShieldingOuterDiam/2, sourceShieldingHeight/2., 0.0, 2.0*pi);
  G4VisAttributes* sourceShieldingLogic_att = new G4VisAttributes(cyan);
  G4LogicalVolume* sourceShieldingLogic = new G4LogicalVolume(sourceShielding, /*material=*/mat_iron, /*name=*/"sourceShieldingLogic");
      //, /*color=*/skin);
  sourceShieldingLogic->SetVisAttributes(sourceShieldingLogic_att);
  G4PVPlacement* sourceShieldingPhys = new G4PVPlacement(zero_rotation, G4ThreeVector(sourceShieldingPosX,sourceShieldingPosY,sourceShieldingPosZ), sourceShieldingLogic, "sourceShieldingPhys", container, false, 0);
  //uncomment later
  //sourceShieldingLogic->SetForceWireFrame(true);
  //#sourceShieldingLogic->SetForceSolid(true);

  //####Collimator shielding

  G4double collimatorShieldingInnerDiam=20 * mm;
  G4double collimatorShieldingOuterDiam=107.6352 * mm;
  G4double collimatorShieldingHeight=89 * mm;
  G4double collimatorShieldingPosX=0.0*mm;
  G4double collimatorShieldingPosY=0.0*mm;
  G4double collimatorShieldingPosZ= ( primaryColl2PosZ + collHeight/2 + primaryColl2Height/2 + 1.5 );

  G4Tubs* collimatorShielding = new G4Tubs("collimatorShielding", collimatorShieldingInnerDiam/2, collimatorShieldingOuterDiam/2, collimatorShieldingHeight/2., 0.0, 2.0*pi);
  G4VisAttributes* collimatorShieldingLogic_att = new G4VisAttributes(brown);
  G4LogicalVolume* collimatorShieldingLogic = new G4LogicalVolume(collimatorShielding, /*material=*/mat_iron, /*name=*/"collimatorLogic");
      //, /*color=*/skin);
  collimatorShieldingLogic->SetVisAttributes(collimatorShieldingLogic_att);
  G4PVPlacement* collimatorShieldingPhys = new G4PVPlacement(zero_rotation, G4ThreeVector(collimatorShieldingPosX,collimatorShieldingPosY,collimatorShieldingPosZ), collimatorShieldingLogic, "collimatorShieldingPhys", container, false, 0);
  //collimatorShieldingLogic.SetForceWireFrame(1)
  //#collimatorShieldingLogic.SetForceSolid(1)



  //####plexi
  G4double plexiInnerDiam= 0.0;
  G4double plexiOuterDiam= 107.6352 * mm;
  G4double plexiHeight = 2.0 * mm;
  G4double plexiPosX=0.0;
  G4double plexiPosY=0.0;
  G4double plexiPosZ=containerHeight/2.-plexiHeight/2.0; // WARNING TO BE CORRECTED

  G4Tubs* plexiSolid = new G4Tubs("plexiSolid", plexiInnerDiam/2, plexiOuterDiam/2, plexiHeight/2, 0.0, 2.0*pi);
  G4VisAttributes* plexiLogic_att = new G4VisAttributes(white);

  G4LogicalVolume* plexiLogic = new G4LogicalVolume(plexiSolid, /*material=*/mat_plexiglas, /*name=*/"plexi");
  plexiLogic->SetVisAttributes(plexiLogic_att);
  G4PVPlacement* plexiPhys = new G4PVPlacement(zero_rotation, G4ThreeVector(plexiPosX,plexiPosY,plexiPosZ), plexiLogic, "plexiPhys", World_log, false, 0);
  //plexiLogic.SetForceSolid(1)

//   G4GDMLParser parser;
//   parser.Write("g4test.gdml", World_phys);

#else

  //################################################################
  // Define the flask geometry
  //################################################################

#endif

    return World_phys;
}
