# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/LdfEvent/LdfEventLib.py,v 1.1 2008/07/09 21:13:42 glastrm Exp $
def generate(env, **kw):
    if not kw.get('depsOnly', 0):
        env.Tool('addLibrary', library = ['LdfEvent'])
        if env['PLATFORM']=='win32' and env.get('CONTAINERNAME','')=='GlastRelease':
	    env.Tool('findPkgPath', package = 'LdfEvent') 

    if env['PLATFORM']=='win32' and env.get('CONTAINERNAME','')=='GlastRelease':
        env.Tool('findPkgPath', package = 'lsfData') 
        env.Tool('findPkgPath', package='enums')
        env.Tool('findPkgPath', package='Event')


def exists(env):
    return 1;
