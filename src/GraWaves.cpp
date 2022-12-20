#include <stdlib.h>
#include "GraWaves.h"

GraWaves::GraWaves( int numBodies )
{
    initVars();
    GraWaves::numBodies = numBodies;
}

GraWaves::GraWaves()
{
    initVars();
    GraWaves::numBodies = DEFAULT_NUM_BODIES;
}

GraWaves::~GraWaves()
{
    CleanupSimulation();

    delete display;
    delete timer;
    delete config;
    delete _mode;
}

void GraWaves::initVars()
{
    timer = NULL;
    display = NULL;
    numTicks = 0;
    universe = NULL;
    config = NULL;
    _mode = Mode::GetInstance();
}

void GraWaves::Update( double timeStep )
{
    universe->Update( timeStep );
    universe->DumpStats();
}

void GraWaves::Initialize()
{
    srand( time(0) );

    config = new Config();
    timer = new Timer();
    display = new Renderer();

    config->Read( "../conf/gw.conf" );

    // Setup class constants
    Entity::DEFAULT_MASS = config->body_mass;
    Entity::RANDOM_SPEED = config->body_random_speed;
    Wave::WAVE_LIFETIME = config->wave_lifetime;
    Wave::WAVE_SPEED = config->wave_speed;
    Wave::WAVE_DEFAULTCOLOR = config->wave_color;
    Wave::WAVE_ALPHAFACTOR = config->wave_alphafactor;

    Universe::GRAVITY_COEF = config->universe_gravity_con;
    Universe::SPEED_LIMIT = config->universe_speed_limit;

    display->SetBGColor( config->display_bgcolor );
    display->SetScreenSize( config->display_screen_width, config->display_screen_height );
    display->SetPickRange( config->display_pickrange );
    display->SetWorldSize( 5.0 * config->universe_radius );
    display->Init();
    display->BodyDisplay( (config->body_display)!=0 );
    display->SetBodyColor( config->body_color );
    display->WaveDisplay( (config->wave_display)!=0 );

    // Setup simulation
    SetupSimulation();

    _mode->DebugEnable( config->debug_mode );
}

void GraWaves::SetupSimulation()
{
    // calculate ticks number corresponding correct period of time.
    if( config->general_frequency > 0 )
    {
        ticksPeriod = 1000000 / config->general_frequency;
    }
    else
    {
        ticksPeriod = 0;
    }
    timer->Reset();

    universe = new Universe();
    universe->Radius( config->universe_radius );
    universe->NumBodies( config->universe_num_bodies );
    universe->DeadZone( config->universe_deadzone );
    universe->Initialize();

    display->RegisterBodies( universe->GetBodies() );
    display->RegisterWaves( universe->GetWaves() );
}

void GraWaves::CleanupSimulation()
{
    delete universe;
}

void GraWaves::Run()
{
    while( Mode::MODE_QUIT != _mode->GetMode() )
    {
        ModeProcessing();

        if( Mode::MODE_RESET == _mode->GetMode() )
        {
            CleanupSimulation();
            SetupSimulation();

            _mode->SetMode( Mode::MODE_PAUSE );
        }
        else if( Mode::MODE_RUN == _mode->GetMode() )
        {
            Step();
        }
        else if( Mode::MODE_STEP == _mode->GetMode() )
        {
            Step();
            _mode->SetMode( Mode::MODE_PAUSE );
        }

        display->Update();
        display->PollEvents();
    }
}

void GraWaves::Step()
{
    numTicks = timer->GetElapsed();
    if( numTicks > ticksPeriod )
    {
        Update( config->general_timestep );
        timer->Reset();
        display->RegisterWaves( universe->GetWaves() );
    }
}

void GraWaves::ModeProcessing()
{
    Mode::RequestType req = _mode->GetRequest();

    switch( req )
    {
        case Mode::REQ_RESET:
            _mode->SetMode( Mode::MODE_RESET );
            break;

        case Mode::REQ_TOGGLE:
            _mode->Toggle();
            break;

        case Mode::REQ_STEP:
            _mode->SetMode( Mode::MODE_STEP );
            break;

        case Mode::REQ_COLOR_WAVES:
            universe->ColorWaves( 0xffffff );
            break;

        case Mode::REQ_QUIT:
            _mode->SetMode( Mode::MODE_QUIT );
            break;

        case Mode::REQ_NONE:
        default:
            break;
    }
}

