#ifndef CONFIG_H
#define CONFIG_H

#include <libconfig.h>

class Config 
{
public:
    Config();
    ~Config();
    void Read( const char *filename );

private:
    config_t config;
    config_setting_t *setting_cfg;

    void initVars();
    void Defaults();

public:
    // Config data members
    // General
    int general_frequency;
    double general_timestep;
    // Display
    int display_screen_width;
    int display_screen_height;
    int display_bgcolor;
    int display_pickrange;
    // Body
    double body_mass;
    int body_display;
    int body_color;
    double body_random_speed;
    // Wave
    double wave_spawnperiod;
    double wave_speed;
    double wave_lifetime;
    int wave_display;
    int wave_color;
    double wave_alphafactor;
    // Universe
    double universe_radius;
    double universe_gravity_con;
    int universe_num_bodies;
    double universe_deadzone;
    int universe_speed_limit;
    // Debug
    int debug_mode;
};

#endif

