# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/LdfEvent/SConscript,v 1.9 2009/08/07 21:54:50 jrb Exp $
# Authors: Heather Kelly <heather@milkyway.gsfc.nasa.gov>
# Version: LdfEvent-04-10-01
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('LdfEventLib', depsOnly = 1)
LdfEvent = libEnv.SharedLibrary('LdfEvent', listFiles(['src/*.cxx']))

progEnv.Tool('LdfEventLib')
test_LdfEvent = progEnv.Program('test_LdfEvent', ['src/test/testMain.cxx'])

progEnv.Tool('registerTargets', package = 'LdfEvent',
             libraryCxts = [[LdfEvent, libEnv]],
             testAppCxts = [[test_LdfEvent, progEnv]],
             includes = listFiles(['LdfEvent/*.h']))




