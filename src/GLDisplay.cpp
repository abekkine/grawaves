#include <Util.h>
#include <GLDisplay.h>

GLDisplay::GLDisplay()
{
    InitVars();
}

GLDisplay::~GLDisplay()
{
    SDL_FreeSurface( m_screen );
}

void GLDisplay::InitVars()
{
    quitSignal = false;
    m_screen_width = -1;
    m_screen_height = -1;
    bgRed = bgGreen = bgBlue = 0.0;
    bgAlpha = 1.0;
    vpNear = -1.0;
    vpFar = 1.0;
    // UPDATE : Pan/Zoom
    _real_width = 100.0;
    _real_height = 100.0;
    _zoom_level = 1.0;
    _x_offset = 0.0;
    _y_offset = 0.0;
    _pan_mode = 0;
    _pan_start_x = 0;
    _pan_start_y = 0;
    _zoom_mode = 0;
    _zoom_start_x = 0;
    _zoom_start_y = 0;
    _mouse_x = 0;
    _mouse_y = 0;
    // END : Pan/Zoom
}

// UPDATE : Pan/Zoom
void GLDisplay::SetWorldSize( double size )
{
    if( m_screen_width > m_screen_height )
    {
        _real_width = size;
        _real_height = size * m_screen_height / m_screen_width;
    }
    else
    {
        _real_width = size * m_screen_width / m_screen_height;
        _real_height = size;
    }
}

void GLDisplay::SetScreenSize( int width, int height )
{
    m_screen_width = width;
    m_screen_height = height;
}

void GLDisplay::ExitFunction()
{
    SDL_Quit();
}

bool GLDisplay::Init()
{
    bool result = false;
    int rc;

    rc = SDL_Init( SDL_INIT_VIDEO );
    if( rc < 0 )
    {
        fprintf( stderr, "Unable to init SDL: %s\n", SDL_GetError() );
    }
    else
    {
        atexit( ExitFunction );

        m_screen = SDL_SetVideoMode( m_screen_width, m_screen_height, 16, SDL_OPENGL );
        if( m_screen == NULL )
        {
            fprintf( stderr, "Unable to set %dx%d video: %s\n", m_screen_width, m_screen_height, SDL_GetError() );
        }
        else
        {
            // try to enable text rendering support.
            GL_Init();
            Reshape(m_screen->w, m_screen->h);
            result = true;
        }
    }

    return result;
}

void GLDisplay::PreRender()
{
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void GLDisplay::PostRender()
{
    // Swap buffers.
    SDL_GL_SwapBuffers();
}

void GLDisplay::Render()
{
}

void GLDisplay::Update()
{
    PreRender();
    Render();
    PostRender();
}

void GLDisplay::GL_Init()
{
    glShadeModel( GL_SMOOTH );
    glClearColor( bgRed, bgGreen, bgBlue, bgAlpha );
    glClearDepth( 1.0f );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void GLDisplay::Reshape(int width, int height)
{
    if( height == 0 )
    {
        height = 1;
    }

    glViewport( 0, 0, width, height );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    // UPDATE : Pan/Zoom
    // viewport calculation.
    {
        double scaled_width = 0.5 * _real_width * _zoom_level;
        double scaled_height = 0.5 * _real_height * _zoom_level;

        vpLeft = _x_offset - scaled_width;
        vpRight = _x_offset + scaled_width;

        vpTop = _y_offset + scaled_height;
        vpBottom = _y_offset - scaled_height;

        // Update Pick Distance
        _pick_distance = _pick_range * (vpRight - vpLeft) / m_screen->w;
    }

    glOrtho( vpLeft, vpRight, vpTop, vpBottom, vpNear, vpFar );
    // END : Pan/Zoom

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void GLDisplay::PollEvents()
{
    while( SDL_PollEvent(&m_event) )
    {
        switch( m_event.type )
        {
            case SDL_VIDEORESIZE:
                m_screen = SDL_SetVideoMode(m_event.resize.w, m_event.resize.h, 16, SDL_OPENGL|SDL_RESIZABLE);
                if( m_screen )
                {
                    Reshape(m_screen->w, m_screen->h);
                }
                else
                {
                    puts( "Unable to set video mode on reshape." );
                }
                break;

            case SDL_KEYDOWN:
                ProcessKeys( m_event );
                break;

            // UPDATE : Pan/Zoom
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                ButtonEvent( &m_event.button );
                break;

            case SDL_MOUSEMOTION:
                MotionEvent( &m_event.motion );
                break;
            // END : Pan/Zoom

            case SDL_QUIT:
                quitSignal = true;
                break;
        }
    }
}

// UPDATE : Pan/Zoom
void GLDisplay::ButtonEvent( SDL_MouseButtonEvent* button )
{
    switch( button->button )
    {
        case SDL_BUTTON_LEFT:
            break;

        case SDL_BUTTON_RIGHT:
            if( button->state == SDL_PRESSED )
            {
                _pan_mode = 1;
                _pan_start_x = _mouse_x;
                _pan_start_y = _mouse_y;
            }
            else
            {
                _pan_mode = 0;
            }
            break;

        case SDL_BUTTON_MIDDLE:
            if( button->state == SDL_PRESSED )
            {
                _zoom_mode = 1;
                _zoom_start_x = _mouse_x;
                _zoom_start_y = _mouse_y;
            }
            else
            {
                _zoom_mode = 0;
            }
            break;

        case SDL_BUTTON_WHEELUP:
            _zoom_level += 0.01;
            Reshape(m_screen->w, m_screen->h);
            break;

        case SDL_BUTTON_WHEELDOWN:
            _zoom_level -= 0.01;
            Reshape(m_screen->w, m_screen->h);
            break;
    }
}

void GLDisplay::MotionEvent( SDL_MouseMotionEvent* motion )
{
    int dx, dy;
    float scale_x, scale_y;

    _mouse_x = motion->x;
    _mouse_y = motion->y;

    if( _zoom_mode != 0 )
    {
        dx = _mouse_x - _zoom_start_x;
        dy = _mouse_y - _zoom_start_y;

        /// @remark Zoom uses only y-axis
        _zoom_level += dy * 0.02;

        _zoom_start_x = _mouse_x;
        _zoom_start_y = _mouse_y;

        Reshape(m_screen->w, m_screen->h);
    }

    if( _pan_mode != 0 )
    {
        scale_x = (vpRight - vpLeft) / m_screen->w;
        scale_y = (vpBottom - vpTop) / m_screen->h;

        dx = _mouse_x - _pan_start_x;
        dy = _mouse_y - _pan_start_y;

        _x_offset -= dx * scale_x;
        _y_offset += dy * scale_y;

        _pan_start_x = _mouse_x;
        _pan_start_y = _mouse_y;

        Reshape( m_screen->w, m_screen->h );
    }
}
// END : Pan/Zoom

void GLDisplay::UserKeys( int keycode, bool shift, bool ctrl )
{
    keycode = keycode;
    shift = shift;
    ctrl = ctrl;
}

void GLDisplay::ProcessKeys( SDL_Event &event )
{
    bool shiftState;
    bool ctrlState;
    SDLMod modifier = SDL_GetModState(); 
    m_keyCode = (int) event.key.keysym.sym;

    shiftState = ( (modifier & (KMOD_LSHIFT|KMOD_RSHIFT)) != 0);
    ctrlState  = ( (modifier & (KMOD_LCTRL|KMOD_RCTRL)) != 0);

    UserKeys( m_keyCode, shiftState, ctrlState );
}

void GLDisplay::SetBGColor( unsigned int color )
{
    Util::ConvertColor( color, bgRed, bgGreen, bgBlue );
}

void GLDisplay::SetBGAlpha( float alpha )
{
    bgAlpha = alpha;
}

void GLDisplay::GetRealCoordinates( float& x, float& y )
{
    x =  (_mouse_x * (vpRight - vpLeft) / m_screen->w) + vpLeft;
    y = (_mouse_y * (vpBottom - vpTop) / m_screen->h ) + vpTop; 
    y = -1.0 * y;
}

void GLDisplay::SetPickRange( int range )
{
    _pick_range = range;
}

float GLDisplay::PickDistance()
{
    return _pick_distance;
}

