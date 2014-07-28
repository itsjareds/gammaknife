#!/usr/bin/env python

# Script to generate collimator hemisphere definition
# usage: ./genhemisphere.py > CollimatorGrid.mac

# nColl is the number of collimators on the main axis
# collSize is the size in mm of the collimator used
# r is the radius of the hemisphere

import math

### Tuneable variables

nColl = 5
collSize = 18
r = 800

### Enter main code

# invert r (beam travels in positive direction)
r = -r

print """/gate/geometry/setMaterialDatabase data/GateMaterials.db

#
#     W O R L D
#
/gate/world/geometry/setXLength                 500. cm
/gate/world/geometry/setYLength                 500. cm
/gate/world/geometry/setZLength                 500. cm
#/gate/world/geometry/setXLength                 400. mm
#/gate/world/geometry/setYLength                 400. mm
#/gate/world/geometry/setZLength                 400. mm

#
# Collimator hemisphere
#

/gate/world/daughters/name                      hemisphere
/gate/world/daughters/insert                    sphere
/gate/hemisphere/geometry/setRmin               0 mm
/gate/hemisphere/geometry/setRmax               1000 mm
/gate/hemisphere/geometry/setPhiStart           0 deg
/gate/hemisphere/geometry/setDeltaPhi           180 deg
/gate/hemisphere/placement/setTranslation       0.0 0.0 0.0 mm
/gate/hemisphere/setMaterial                    Air
/gate/hemisphere/vis/setVisible                 1
/gate/hemisphere/vis/setColor                   yellow

# Volume movement over time

#/gate/hemisphere/moves/insert                   rotation
#/gate/hemisphere/rotation/setSpeed              1.5 deg/s
#/gate/hemisphere/rotation/setAxis               1 0 0

/gate/hemisphere/moves/insert                   orbiting
/gate/hemisphere/orbiting/setSpeed              1.5 deg/s
/gate/hemisphere/orbiting/setPoint1             0 0 0 cm
/gate/hemisphere/orbiting/setPoint2             1 0 0 cm"""

for x in range(0, nColl):
  ratio = float(x) / (nColl-1)
  theta = ratio * math.pi
  xTrans = r * math.sin(theta)
  zTrans = r * math.cos(theta)
  print ("""
#================
# COLLIMATOR {0}
#================

/gate/hemisphere/daughters/name                 Collimator{0}
/gate/hemisphere/daughters/insert               cylinder
/gate/Collimator{0}/geometry/setRmin              0 nm
/gate/Collimator{0}/geometry/setRmax              10 mm
/gate/Collimator{0}/geometry/setHeight            0.5 nm
/gate/Collimator{0}/placement/setTranslation      0.0 {1:.3f} {2:.3f} mm
/gate/Collimator{0}/setMaterial                   Air
/gate/Collimator{0}/vis/setVisible                1
/gate/Collimator{0}/vis/setColor                  red"""
    .format(x,-xTrans,zTrans))

print """
#
# Attach phasespace
#"""

for x in range(0, nColl):
  print ("""
/gate/source/addSource                          seed{0} phaseSpace
/gate/source/seed{0}/addPhaseSpaceFile            data/collimator.root
/gate/source/seed{0}/setParticleType              gamma
#/gate/source/seed{0}/useRegularSymmetry
/gate/source/seed{0}/useRandomSymmetry
/gate/source/seed{0}/setRmax                      {1} mm
/gate/source/seed{0}/attachTo                     Collimator{0}"""
    .format(x,collSize))

print """
#
# Rotate collimated beams
#"""

for x in range(0, nColl):
  ratio = float(x) / (nColl-1)
  theta = ratio * math.pi
  theta_deg = theta * (180/math.pi)
  print ("""
/gate/Collimator{0}/placement/setRotationAxis     1 0 0
/gate/Collimator{0}/placement/setRotationAngle    {1:.4f} deg
#/gate/Collimator{0}/placement/setAxis             1 0 0"""
    .format(x,theta_deg))