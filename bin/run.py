#! /usr/bin/env python
import os , sys , time, commands
startTime = time.time()
#*********************************************
# C O N F I G U R A T I O N
#*********************************************
i0 = 0
nthreads = 4
threads = range(i0,i0+nthreads )
# f e t c h c o n f i g from arguments i f p r e s e n t
A = {}
if len(sys.argv) >1: A.update(eval(sys.argv [1]))

#*********************************************
# T H R E A D S
#*********************************************

from threading import Thread
import subprocess as sp
from random import randint


##*********************************************
## P O U R  L E S  S I M U L A T I O N S  S U R  P L U S I E U R S  T H R E A D S
#*********************************************


#os.chdir(A['DIR'])
class Run(Thread):
    def __init__(self,i):
      Thread.__init__(self)
      self.thread=i
    def run(self):
      A['THREAD'] = self.thread
      A['SEED'] = randint(0,1e9)
      if os.path.isfile('./RunBeam'):
        cmd = './RunBeam %d %d' % (A['THREAD'],A['SEED'])
      elif os.path.isfile('../RunBeam'):
        cmd = '../RunBeam %d %d' % (A['THREAD'],A['SEED'])
      else:
        print ' Fatal: No RunBeam binary found.'
        sys.exit(1)
      print cmd
      self.P = sp.Popen(cmd, shell=True,stdout=sp.PIPE, stderr=sp.PIPE)
      self.out = self.P.communicate()[0]

th = []
for t in threads: th.append(Run(t))
for t in th: t.start(); time.sleep(1)
for t in th:
  while t.isAlive(): continue

#print 'ls'
#os.chdir('data')
#print os.getcwd()
#print 'hadd phasespace.root phasespace.*.root'
#os.system('hadd phasespace.root phasespace.*.root')




##*********************************************
## C H R O N O M E T R E
#*********************************************

totalTime = time.time() - startTime

print ' La simulation a dure ' + str(totalTime) + ' secondes '

