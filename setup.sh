#*******ROOT*****
source ~/software/root/bin/thisroot.sh
export LD_LIBRARY_PATH=$ROOTSYS/lib:$PYTHONDIR/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$ROOTSYS/lib:$PYTHONPATH
alias root='root -l'


#********GEANT4****
source ~/software/geant4/geant4.10.00-install/bin/geant4.sh
export G4HOME=~/software/geant4/geant4.10.00-install

export PATH=$PATH:/home/yannick/software/view3dscene

