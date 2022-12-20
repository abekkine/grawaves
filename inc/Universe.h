#ifndef UNIVERSE_H
#define UNIVERSE_H

/// @class Universe
/// @brief This is where physics law governing the 'Universe'
///        computed and applied.
/// @author A.Bekkine
/// @version 0.1
/// @date 2011

#include <map>
#include <vector>
#include <Wave.h>

using namespace std;

typedef struct
{
    unsigned int numBodies;
    unsigned int numWaves;
    Scalar age;

} StatsType;

class Universe
{
public:
	/// @brief Universe constructor.
	///
    Universe();

	/// @brief Universe constructor, with a given radius.
	/// @param in radius
	///
    Universe( Scalar radius );

	/// @brief Universe destructor.
	/// 
	/// Body and Wave objects freed.
	/// 
    ~Universe();

	/// @brief Advances universe in time with given value.
	/// @param in timeStep
    void Update( double timeStep );

	/// @brief Initialization of universe contents.
    void Initialize();

	/// @brief Set universe radius.
	/// @param in radius
    void Radius( Scalar radius );

	/// @brief Set number of bodies in universe.
	/// @param in numBodies
    void NumBodies( int numBodies );

	/// @brief Sets maximum effective gravity range in universe.
	/// @param in distance
	/// @bug It is obsolete since each individual wave should have
	///      its spesific effective range.
    void DeadZone( Scalar distance );

	/// @brief Returns bodies in universe.
	/// @param out bodies
    BodyVectorType& GetBodies();

	/// @brief Returns waves in universe.
	/// @param out waves
    WaveVectorType& GetWaves();

	/// @brief Dump simulation statistics.
	/// @warning This is a debug purposed method. It should be 
	///			 removed on later releases.
    void DumpStats();

	/// @brief Dump statistics control method.
	/// @param in enable
    void DumpEnable( bool enable );

    /// @brief Color single spawn of waves.
    /// @param in color
    /// @param out fWaveColorCommand
    void ColorWaves( unsigned int color );

public:
	/// @brief Gravity coefficient as a class static value.
    static Scalar GRAVITY_COEF;
    static bool SPEED_LIMIT;

private:
	/// @brief Gravity coefficient as a class constant, used in simulation.
    const Scalar conGravity;
	/// @brief Radius of the universe; needed for body insertion within universe limits. @see Radius.
    Scalar radius;
	/// @brief Number of bodies in the simulation. @see NumBodies.
    int numBodies;
	/// @brief Time of universe simulation. @see Update.
    double time;
	/// @brief Debug purposed dump control flag. @see DumpEnable.
    bool fDumpEnabled;
	/// @brief Wave effective range. Rendered useless. @see DeadZone.
    Scalar deadzone;

	/// @brief Container variable to keep bodies in universe.
    BodyVectorType bodies;
	/// @brief Container variable to keep waves induced by bodies in universe.
    WaveVectorType waves;

    /// @brief Container to collect statistics.
    StatsType stats;

    /// @brief Command flag to initiate wave color marking.
    bool fWaveColorCommand;

    /// @brief Marking color for waves.
    unsigned int waveColor;

	/// @brief Initialization of member variables.
    void initVars();

	/// @brief Extract a list of all waves containing given body inside.
	/// @param in body
	/// @param out waves
    void GetWavesCoveringBody( Body* body, WaveVectorType& waves );

	/// @brief Deletes all waves from same source, excluding newest one.
	/// @param in waves
	/// @param out waves
    void EliminateOlderWaves( WaveVectorType& waves );

	/// @brief Compute acceleration vector of given body, due to given waves.
	/// @param in body
	/// @param in waves
	/// @param out acceleration
    Vector ComputeAccelerationVector( Body* body, WaveVectorType& waves );

	/// @brief Compute Newtonian gravity force on a body due to given single wave.
	/// @param in body
	/// @param in wave
	/// @param out acceleration
    Vector GetNewtonianGravity( Body* body, Wave* wave );
};

#endif

