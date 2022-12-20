#include <stdio.h>
#include <math.h>
#include <Body.h>

bool Body::fLimitEnable = false;
Scalar Body::speedLimit = 0.0;

Body::Body( int id )
{
    initVars();
    Body::id = id;
}

Body::~Body()
{
}

void Body::initVars()
{
    // Nothing to initialize.
    fSelected = false;
}

void Body::Update( double timeStep )
{
    if( fLimitEnable )
    {
        Vector vel = velocity;
        vel.x = velocity.x + timeStep * acceleration.x;
        vel.y = velocity.y + timeStep * acceleration.y;
        if( ~vel < 0.95 * speedLimit )
        {
            velocity = vel;
        }
        else
        {
            // INCOMPLETE : something proper should be implemented otherwise.
        }
    }
    else
    {
        velocity.x += timeStep * acceleration.x;
        velocity.y += timeStep * acceleration.y;
        //velocity.z += timeStep * acceleration.z;
    }

    position.x += timeStep * velocity.x;
    position.y += timeStep * velocity.y;
    //position.z += timeStep * velocity.z;
}

double Body::RandomBetween( double min, double max )
{
    double range = max - min;
    double root = ((float) rand()) / (float)(RAND_MAX);

    return (min + range*root);
}

void Body::AtRandom( Scalar radius )
{
    float randomAngle;
    float randomSpeed;

    position.x = RandomBetween( -radius, radius );
    position.y = RandomBetween( -radius, radius );
    position.z = 0.0;

    randomSpeed = RandomBetween( 0.0, Entity::RANDOM_SPEED );
    randomAngle = RandomBetween( 0.0, 2.0 * M_PI + 0.01 );
    
	velocity.x = randomSpeed * cos( randomAngle );
	velocity.y = randomSpeed * sin( randomAngle );
	velocity.z = 0.0;
}

void Body::SetSpeedLimit( bool limit_enable, Scalar limit_value )
{
    fLimitEnable = limit_enable;
    speedLimit = limit_value * 0.25;
}

void Body::Select( bool value )
{
    fSelected = value;
}

bool Body::Selected()
{
    return fSelected;
}

