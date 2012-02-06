# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/LdfEvent/SConscript,v 1.10 2009/11/06 01:58:03 jrb Exp $
# Authors: Heather Kelly <heather@milkyway.gsfc.nasa.gov>
# Version: LdfEvent-04-12-01-tr01
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




