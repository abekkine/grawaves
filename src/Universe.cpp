#include <stdio.h>
#include <Universe.h>

Scalar Universe::GRAVITY_COEF = 1.0;
bool Universe::SPEED_LIMIT = false;

Universe::Universe() : conGravity( GRAVITY_COEF )
{
	/// Initialize with a separate function.
	/// Required to maintain reusability when there
	/// are multiple constructors.
    initVars();
}

Universe::Universe( Scalar radius ) : conGravity( GRAVITY_COEF )
{
    initVars();
    Universe::radius = radius;
}

Universe::~Universe()
{
    while( not bodies.empty() )
    {
        Body *aBody = bodies.back();
        bodies.pop_back();
        delete aBody;
    }

    while( not waves.empty() )
    {
        Wave *aWave = waves.back();
        waves.pop_back();
        delete aWave;
    }
}

void Universe::initVars()
{
	/// All class members are given their default values here.
	/// @remark Due to a recommendation, it is advised to give all defaults impossible values. It is worth to consider.
    radius = 0;
    numBodies = 0;
    time = 0.0;
    bodies.clear();
    waves.clear();

    /// Also resets statistics data.
    fDumpEnabled = false;
    stats.numBodies = 0;
    stats.numWaves = 0;
    stats.age = 0.0;

    /// init wave coloring.
    fWaveColorCommand = false;
    waveColor = 0xffffff;
}

void Universe::ColorWaves( unsigned int color )
{
    fWaveColorCommand = true;
    waveColor = color;
}

void Universe::Update( double timeStep )
{
    Universe::time += timeStep;

    WaveVectorType::iterator iWave;
    for( iWave=waves.begin(); iWave!=waves.end(); ++iWave )
    {
        if( (*iWave)->IsAlive() )
        {
            (*iWave)->Update( timeStep );
        }
        else
        {
            Wave *deadWave = *iWave;
            bool exitLoop = (deadWave == waves.back());

            waves.erase( iWave );
            delete deadWave;

            if(exitLoop)
            {
                break;
            }
        }
    }

    BodyVectorType::iterator iBody;
    for( iBody=bodies.begin(); iBody!=bodies.end(); ++iBody )
    {
        (*iBody)->Update( timeStep );

        Wave *new_wave = new Wave( *iBody );
        if( fWaveColorCommand )
        {
            new_wave->SetColor( waveColor );
        }
        waves.push_back( new_wave );
    }

    if( fWaveColorCommand )
    {
        fWaveColorCommand = false;
    }


    WaveVectorType waveList;    
    Body *theBody;
    Vector bodyAcceleration;
    for( iBody=bodies.begin(); iBody!=bodies.end(); ++iBody )
    {
        theBody = *iBody;
        
        GetWavesCoveringBody( theBody, waveList );

        EliminateOlderWaves( waveList );

        bodyAcceleration = ComputeAccelerationVector( theBody, waveList );

        theBody->SetAcceleration( bodyAcceleration );
    }
}

void Universe::Initialize()
{
    Body* a_body;

    for( int i=0; i<Universe::numBodies; i++ )
    {
        a_body = new Body( i );
        a_body->AtRandom( radius );
        a_body->SetSpeedLimit( Universe::SPEED_LIMIT, Wave::WAVE_SPEED );
        bodies.push_back( a_body );
    }
}

void Universe::GetWavesCoveringBody( Body* body, WaveVectorType& waveList )
{
    Wave *theWave;

    // Clean up wave list.
    waveList.clear();

    // Iterate over master wave list.
    WaveVectorType::iterator iWave;
    for( iWave=waves.begin(); iWave!=waves.end(); ++iWave )
    {
        theWave = *iWave;
        if( body->Identifier() != theWave->Source() )
        {
            if( theWave->Covers( body ) )
            {
                waveList.push_back( theWave );
            }
        }
    }
}

void Universe::EliminateOlderWaves( WaveVectorType& waveList )
{
    map< unsigned int, Wave * > waveMap;
    WaveVectorType::iterator iWave;
    Wave *theWave;

    for( iWave=waveList.begin(); iWave!=waveList.end(); ++iWave )
    {
        theWave = *iWave;
        if( waveMap.find( theWave->Source() ) == waveMap.end() )
        {
            // wave of source does not exist in the map, so insert it.
            waveMap[ theWave->Source() ] = theWave;
        }
        else
        {
            // wave of source exists in the map, so replace it if new one has smaller age.
            if( theWave->Age() < waveMap[ theWave->Source() ]->Age() )
            {
                waveMap[ theWave->Source() ] = theWave;
            }
        }
    }

    // Cleanup waveList and transfer contents of waveMap into waveList.
    waveList.clear();
    map< unsigned int, Wave * >::iterator iter;
    for( iter=waveMap.begin(); iter!=waveMap.end(); ++iter )
    {
        waveList.push_back( iter->second );
    }
}

Vector Universe::ComputeAccelerationVector( Body* body, WaveVectorType& waveList )
{
    Vector acceleration;
    WaveVectorType::iterator iWave;
    Wave *theWave;

    acceleration.Set( 0.0, 0.0, 0.0 );
    for( iWave=waveList.begin(); iWave!=waveList.end(); ++iWave )
    {
        theWave = *iWave;

        acceleration = acceleration + GetNewtonianGravity( body, theWave );
    }

    return acceleration;
}

Vector Universe::GetNewtonianGravity( Body* body, Wave* wave )
{
    Vector gravityVector;
    Vector distanceVector;
    Scalar distance;
    Scalar squareDistance;
    Scalar gravityForce;

    distanceVector = wave->GetCenter() - body->GetPosition();
    distance = ~distanceVector;

    if( distance > deadzone )
    {
        squareDistance = distance * distance;
        gravityForce = Universe::conGravity * wave->Mass() / squareDistance;
        gravityVector = (!distanceVector) * gravityForce;
    }
    else
    {
        gravityVector.Set( 0.0, 0.0, 0.0 );
    }

    return gravityVector;
}

void Universe::DumpEnable( bool enable )
{
    fDumpEnabled = enable;
}

void Universe::DumpStats()
{
    if( fDumpEnabled )
    {
        static int iteration = 0;
    
        if( iteration == 0 )
        {
            stats.numBodies = bodies.size();
            stats.numWaves = waves.size();
            stats.age = Universe::time;
            printf( "bodies(%d), waves(%d), age(%.2f)\n", stats.numBodies, stats.numWaves, stats.age );
        }

        iteration++;
        iteration %= 100;
    }
}

BodyVectorType& Universe::GetBodies()
{
    return bodies;
}

WaveVectorType& Universe::GetWaves()
{
    return waves;
}

void Universe::Radius( Scalar radius )
{
    Universe::radius = radius;
}

void Universe::NumBodies( int numBodies )
{
    Universe::numBodies = numBodies;
}

void Universe::DeadZone( Scalar distance )
{
    Universe::deadzone = distance;
}

