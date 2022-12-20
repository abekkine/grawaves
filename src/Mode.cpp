#include <stdio.h>
#include <stdlib.h>

#include <Mode.h>

Mode* Mode::_instance = NULL;

Mode* Mode::GetInstance()
{
    if( _instance == NULL )
    {
        _instance = new Mode();
    }

    return _instance;
}

Mode::Mode()
{
    Defaults();
}

Mode::~Mode()
{
}

void Mode::Defaults()
{
    fDebugEnable = false;
    _mode = MODE_RUN;
    _request = REQ_NONE;
}

void Mode::SetMode( ModeType mode )
{
    _mode = mode;

    Debug( "SetMode" );
}

Mode::ModeType Mode::GetMode()
{
    return _mode;
}

void Mode::Request( RequestType request )
{
    _request = request;

    Debug( "Request" );
}

Mode::RequestType Mode::GetRequest()
{
    RequestType result = _request;

    if( _request != REQ_NONE )
    {
        Debug( "GetRequest" );
    }

    _request = REQ_NONE;

    return result;
}

void Mode::Toggle()
{
    switch( _mode )
    {
        case MODE_RUN:
            _mode = MODE_PAUSE;
            break;

        case MODE_PAUSE:
            _mode = MODE_RUN;
            break;

        case MODE_STEP:
        case MODE_QUIT:
        default:
            break;
    }

    Debug( "Toggle" );
}

void Mode::DebugEnable( bool value )
{
    fDebugEnable = value;
}

void Mode::Debug( const char *debugMsg )
{
    static char modeStr[5][8] = { "RUN", "PAUSE", "STEP", "RESET", "QUIT" };
    static char requestStr[6][8] = { "TOGGLE", "STEP", "QUIT", "RESET", "COLOR", "NONE" };
    
    if( fDebugEnable )
    {
        printf( "%s : Mode(%s) : Request(%s)\n", 
            debugMsg, 
            modeStr[(int)_mode], 
            requestStr[(int)_request] );
    }
}
