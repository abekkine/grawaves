#include <stdio.h>
#include <Util.h>
#include <Wave.h>

Scalar Wave::WAVE_LIFETIME = 1.0;
Scalar Wave::WAVE_SPEED = 1.0;
Scalar Wave::WAVE_ALPHAFACTOR = 1.0;
unsigned int Wave::WAVE_DEFAULTCOLOR = 0x204080;

Wave::Wave():
    conLifetime( WAVE_LIFETIME ),
    conSpeed( WAVE_SPEED ), 
    conAlpha( WAVE_ALPHAFACTOR ), 
    conDefaultColor( WAVE_DEFAULTCOLOR )
{
    initVars();
}

Wave::Wave( Body* body ):
    conLifetime( WAVE_LIFETIME ),
    conSpeed( WAVE_SPEED ),
    conAlpha( WAVE_ALPHAFACTOR ),
    conDefaultColor( WAVE_DEFAULTCOLOR )
{
    initVars();
    source = body->Identifier();
    mass = body->GetMass();
    center = body->GetPosition();
    radius = 0.0;
    alive = true;

    fColorEnable = false;
    Util::ConvertColor( conDefaultColor, defaultColor, false );
    defaultColor[3] = conAlpha;
    Util::ConvertColor( 0, waveColor, true );
    activeColorPointer = &defaultColor[0];
}

Wave::~Wave()
{
}

void Wave::initVars()
{
    source = -1;
    mass = 0.0;
    center.Set( 0.0, 0.0, 0.0 );
    radius = 0.0;
    age = 0.0;
    alive = false;
}

void Wave::Update( double timeStep )
{
    if( age > conLifetime )
    {
        alive = false;
    }
    else
    {
        age += timeStep;
        radius += timeStep * conSpeed;

        // Update alpha 
        activeColorPointer[3] = conAlpha * (WAVE_LIFETIME - age) / WAVE_LIFETIME;
    }
}

void Wave::SetColor( unsigned int color )
{
    fColorEnable = true;
    Util::ConvertColor( color, waveColor );
    activeColorPointer = &waveColor[0];
}

void Wave::ResetColor()
{
    fColorEnable = false;
    activeColorPointer = &defaultColor[0];
}

bool Wave::IsAlive()
{
    return alive;
}

Vector& Wave::GetCenter()
{
    return center;
}

bool Wave::Covers( Body *body )
{
    Vector distance;

    distance = body->GetPosition() - center;

    return (~distance < radius);
}

unsigned int Wave::Source()
{
    return source;
}

Scalar Wave::Age()
{
    return age;
}

Scalar Wave::Mass()
{
    return mass;
}

Scalar Wave::Radius()
{
    return radius;
}

float *Wave::GetColor()
{
    return activeColorPointer;
}

