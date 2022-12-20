#include <Entity.h>

Scalar Entity::DEFAULT_MASS = 1.0;
Scalar Entity::RANDOM_SPEED = 0.0;

Entity::Entity()
{
    initVars();
}

Entity::Entity( unsigned int id )
{
    initVars();
    Entity::id = id;
}

Entity::~Entity()
{
}

void Entity::initVars()
{
    id = -1;
    position.Set( 0.0, 0.0, 0.0 );
    acceleration.Set( 0.0, 0.0, 0.0 );
    velocity.Set( 0.0, 0.0, 0.0 );
    mass = DEFAULT_MASS;
}

unsigned int Entity::Identifier()
{
    return id;
}

Scalar Entity::GetMass()
{
    return mass;
}

Vector& Entity::GetPosition()
{
    return position;
}

Vector& Entity::GetVelocity()
{
    return velocity;
}

void Entity::SetAcceleration( const Vector& acceleration )
{
    Entity::acceleration = acceleration;
}


