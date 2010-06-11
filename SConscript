# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/LdfEvent/SConscript,v 1.12 2010/04/27 20:14:18 lsrea Exp $
# Authors: Heather Kelly <heather@milkyway.gsfc.nasa.gov>
# Version: LdfEvent-04-12-00
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('addLinkDeps', package='LdfEvent', toBuild='shared')
LdfEvent = libEnv.SharedLibrary('LdfEvent', listFiles(['src/*.cxx']))

progEnv.Tool('LdfEventLib')
test_LdfEvent = progEnv.Program('test_LdfEvent', ['src/test/testMain.cxx'])

progEnv.Tool('registerTargets', package = 'LdfEvent',
             libraryCxts = [[LdfEvent, libEnv]],
             testAppCxts = [[test_LdfEvent, progEnv]],
             includes = listFiles(['LdfEvent/*.h']))




