#ifndef GRAWAVES_H
#define GRAWAVES_H

#include <vector>

#include <Mode.h>
#include <Timer.h>
#include <Config.h>
#include <Renderer.h>
#include <Universe.h>

#define DEFAULT_NUM_BODIES 10

using namespace std;

class GraWaves
{
    private:
        Mode* _mode;

    public:
        GraWaves();
        GraWaves( int numBodies );
        ~GraWaves();
        void Update( double timeStep );
        void Initialize();
        void Run();
        void Step();

    private:
        int numBodies;
        Config *config;
        Universe *universe;
        Renderer *display;
        unsigned int numTicks;
        unsigned int ticksPeriod;
        Timer *timer;
        void initVars();
        void ModeProcessing();
        void SetupSimulation();
        void CleanupSimulation();
};

#endif

