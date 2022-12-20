#ifndef ENTITY_H
#define ENTITY_H

#include <Vector.h>

class Entity 
{
public:
    Entity();
    Entity( unsigned int id );
    ~Entity();
    unsigned int Identifier();
    Scalar GetMass();
    Vector& GetPosition();
    Vector& GetVelocity();
    void SetAcceleration( const Vector& acceleration );

public:
    static Scalar DEFAULT_MASS;
    static Scalar RANDOM_SPEED;

protected:
    unsigned int id;
    Vector position;
    Vector acceleration;
    Vector velocity; 
    Scalar mass;

private:
    void initVars();
};

#endif

