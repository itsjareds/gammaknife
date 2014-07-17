#!/usr/bin/python

# Quick script to generate timing intervals for source movement
# usage: ./gentimes.py > MoveVisu.mac

# Don't forget to make appropriate changes to time slices in mainMacro.mac!

# t is the total time of rotation
# n is the number of time splits

t = 60.
n = 20

dt = t/n
x = 0.0
while x <= t:
    print "/gate/timing/setTime    %.1f s" % x
    x += dt
