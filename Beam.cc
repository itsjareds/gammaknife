#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
//#include "G4UItcsh.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
// #include "RecorderBase.hh"
// #include "ExTPROOTuple.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4TrajectoryDrawByParticleID.hh"
#include "SteppingAction.hh"
#include "StackingAction.hh"
// #include "ExTPRunAction.hh"


int main(int argc,char** argv)
{

    int particles = 1;

  time_t seed;
  time(&seed);
  seed += atoi(argv[2]);
  //   seed = 10;//atoi(10);
  cout << "Random seed : " << seed << endl;
  CLHEP::RanecuEngine *theRanGenerator = new CLHEP::RanecuEngine;
  theRanGenerator->setSeed(seed);
  CLHEP::HepRandom::setTheEngine(theRanGenerator);
  // Constrution du "run manager"

  G4RunManager* runManager = new G4RunManager;

  // Appel des classes incontournables
  // Les pointeurs de ces classes sont fournis au "run manager"

  runManager->SetUserInitialization(new PhysicsList());

  runManager->SetUserAction( new PrimaryGeneratorAction(atoi(argv[1])));//(atoi(argv[2]),argv[3]) );
  runManager->SetUserAction( new SteppingAction(0,particles) );
  runManager->SetUserAction( new StackingAction() );
  runManager->SetUserInitialization(new DetectorConstruction());

    runManager->Initialize();
//
//   runManager->BeamOn(particles );


    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    UImanager->ApplyCommand("/control/execute command.mac");
//       cout << "Random seed : " << seed << endl;


    // interactive mode : define UI session
//     G4UIExecutive* ui = new G4UIExecutive(argc, argv);
//     ui->SessionStart();

//     delete ui;


    // Appel de la classe visualisation de Geant4 et initialisation
//   //
//   G4VisManager* visManager = new G4VisExecutive;
// //
//   visManager->Initialize();
// //
// //   // Personnalisation des couleurs des particules
// //
//   G4TrajectoryDrawByParticleID* model = new  G4TrajectoryDrawByParticleID;
//
//   model->SetDefault("blue");
//   model->Set("e-","red");
//   model->Set("gamma","green");
//   model->Set("neutron","magenta");
//   model->Set("e+","cyan");
//
//   visManager->RegisterModel(model);
// //
//   visManager->SelectTrajectoryModel(model->Name());
/*
  G4UImanager *UImanager= G4UImanager::GetUIpointer();
G4String command = "/control/execute ";
G4String filename = "command.mac";
UImanager->ApplyCommand(command+filename);*/


    delete runManager;

}
