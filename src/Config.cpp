#include <stdlib.h>
#include "Config.h"

Config::Config()
{
    initVars();
}

Config::~Config()
{
}

void Config::initVars()
{
    config_init( &config );

    Defaults();
}

void Config::Defaults()
{
    // General
    general_frequency = 20;
    general_timestep = 1.0;
    // Display
    display_screen_width = 100;
    display_screen_height = 100;
    display_bgcolor = 0;
    display_pickrange = 5;
    // Body
    body_mass = 100.0;
    body_display = true;
    body_color = 0xffffff;
    body_random_speed = 2.0;
    // Wave
    wave_spawnperiod = 0.5;
    wave_speed = 1.0;
    wave_lifetime = 100.0;
    wave_display = true;
    wave_color = 0x0000ff;
    wave_alphafactor = 1.0;
    // Universe
    universe_radius = 1000.0;
    universe_gravity_con = 1.0;
    universe_num_bodies = 10;
    universe_deadzone = 1.0;
    universe_speed_limit = true;
    // Debugging
    debug_mode = false;
}

void Config::Read( const char *filename )
{
    if( config_read_file( &config, filename ) )
    {
        setting_cfg = config_lookup( &config, "gwaves.general" );
        if( setting_cfg != NULL )
        {
            config_setting_lookup_int( setting_cfg, "frequency", &general_frequency );
            config_setting_lookup_float( setting_cfg, "timestep", &general_timestep );
        }

        setting_cfg = config_lookup( &config, "gwaves.display" );
        if( setting_cfg != NULL )
        {
            config_setting_t *screen_cfg = config_lookup( &config, "gwaves.display.screen" );
            if( screen_cfg != NULL )
            {
                config_setting_lookup_int( screen_cfg, "width", &display_screen_width );
                config_setting_lookup_int( screen_cfg, "height", &display_screen_height );
            }

            config_setting_lookup_int( setting_cfg, "pickrange", &display_pickrange );
            config_setting_lookup_int( setting_cfg, "bgcolor", &display_bgcolor );
        }

        setting_cfg = config_lookup( &config, "gwaves.body" );
        if( setting_cfg != NULL )
        {
            config_setting_lookup_float( setting_cfg, "mass", &body_mass );
            config_setting_lookup_int( setting_cfg, "display", &body_display );
            config_setting_lookup_int( setting_cfg, "color", &body_color );
            config_setting_lookup_float( setting_cfg, "randomspeed", &body_random_speed );
        }

        setting_cfg = config_lookup( &config, "gwaves.wave" );
        if( setting_cfg != NULL )
        {
            config_setting_lookup_float( setting_cfg, "spawnperiod", &wave_spawnperiod );
            config_setting_lookup_float( setting_cfg, "speed", &wave_speed );
            config_setting_lookup_float( setting_cfg, "lifetime", &wave_lifetime );
            config_setting_lookup_int( setting_cfg, "display", &wave_display );
            config_setting_lookup_int( setting_cfg, "color", &wave_color );
            config_setting_lookup_float( setting_cfg, "alphafactor", &wave_alphafactor );
        }

        setting_cfg = config_lookup( &config, "gwaves.universe" );
        if( setting_cfg != NULL )
        {
            config_setting_lookup_float( setting_cfg, "radius", &universe_radius );
            config_setting_lookup_float( setting_cfg, "gravity_con", &universe_gravity_con );
            config_setting_lookup_int( setting_cfg, "num_bodies", &universe_num_bodies );
            config_setting_lookup_float( setting_cfg, "deadzone", &universe_deadzone );
            config_setting_lookup_bool( setting_cfg, "speedlimit", &universe_speed_limit );
        }

        setting_cfg = config_lookup( &config, "gwaves.debug" );
        if( setting_cfg != NULL )
        {
            config_setting_lookup_bool( setting_cfg, "mode", &debug_mode );
        }

        config_destroy( &config );
    }
    else
    {
        fprintf( stderr, "%s:%d - %s\n", 
            config_error_file(&config), 
            config_error_line(&config), 
            config_error_text(&config) );

        config_destroy( &config );

        exit( 1 );
    }
}

