#include <stdio.h>
#include <version.h>
#include <GraWaves.h>

#define NUM_BODIES 10

int main( int argc, char *argv[] )
{
    int numBodies = NUM_BODIES;

    // Display version information.
    printf( "Hg.%s\n", VERSION_STRING );

    if( argc == 2 )
    {
        numBodies = atoi( argv[1] );
    }

    GraWaves* gWaves = new GraWaves( numBodies );

    gWaves->Initialize();

    gWaves->Run();

    delete gWaves;

    return 0;
}


