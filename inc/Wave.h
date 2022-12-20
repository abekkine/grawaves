#ifndef WAVE_H
#define WAVE_H

#include <vector>
#include <Vector.h>
#include <Body.h>

class Wave
{
public:
    Wave();
    Wave( Body* body );
    void Update( double timeStep );
    ~Wave();
    bool IsAlive();
    Vector& GetCenter();
    bool Covers( Body *body );
    unsigned int Source();
    float *GetColor();
    Scalar Age();
    Scalar Mass();
    Scalar Radius();
    void SetColor( unsigned int color );
    void ResetColor();

public:
    static Scalar WAVE_LIFETIME;
    static Scalar WAVE_SPEED;
    static Scalar WAVE_SPAWN_PERIOD;
    static unsigned int WAVE_DEFAULTCOLOR;
    static Scalar WAVE_ALPHAFACTOR;
private:
    const Scalar conLifetime;
    const Scalar conSpeed;
    const Scalar conAlpha;
    const unsigned int conDefaultColor;
    bool alive;
    unsigned int source;
    Scalar age;
    Scalar radius;
    Scalar mass;
    Vector center;
    // Separate coloring for waves.
    bool fColorEnable;
    float defaultColor[4];
    float waveColor[4];   
    float *activeColorPointer;

    void initVars();
    
};

typedef std::vector< Wave * > WaveVectorType;

#endif

