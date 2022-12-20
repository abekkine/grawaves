# Helper library for Simba SCons builds.
import os
import sys

sys.path.append( './lib' )
import revlib

VERSION_INC = 'inc/version.h'
TARGET_NAME = 'grawvs'

env = Environment()

if not env.GetOption( 'clean' ):
    revlib.getRevisionString( os.path.abspath( '.' ), VERSION_INC )

clean_files = []
clean_files.append( '.sconsign.dblite' )
clean_files.append( 'results.xml' )
clean_files.append( 'bin/core' )
clean_files.append( 'bin/valgrind.log' )
clean_files.append( 'bin/new.supp' )
clean_files.append( VERSION_INC )
env.Clean( 'default', clean_files )

env.ParseConfig( 'sdl-config --cflags --libs' )
env.ParseConfig( 'pkg-config --libs opencv' )
#env.Append( CPPFLAGS = [ '-p' ] )
#env.Append( LINKFLAGS = [ '-p' ] )
env.Append( CPPFLAGS = [ '-g' ] )
env.Append( CPPFLAGS = [ '-Wall' ] )
env.Append( CPPFLAGS = [ '-Wextra' ] )
env.Append( LINKFLAGS = [ '-g' ] )
env.Append( LINKFLAGS = [ '-L/usr/local/share/OpenCV/3rdparty/lib'] )
env.Append( CPPPATH = [ 'inc' ] )
env.Append( LIBS = [ 'GL' ] )
env.Append( LIBS = [ 'config' ] )

files = Glob( 'src/*.cpp' )

target_path = 'bin/%s' % TARGET_NAME
env.Program( target = target_path, source = files )
