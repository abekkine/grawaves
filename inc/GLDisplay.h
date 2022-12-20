#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <SDL/SDL.h>
#include <GL/gl.h>

class GLDisplay {

    public:
        GLDisplay();
        ~GLDisplay();
        
        void SetScreenSize( int width, int height );
        // UPDATE : Pan/Zoom
        void SetWorldSize( double size );
        // END : Pan/Zoom
        bool Init();
        void PreRender();
        void PostRender();
        virtual void Render()=0;
        virtual void UserKeys( int keycode, bool shift, bool ctrl );
        void Update();
        void Reshape(int w, int h);
        void PollEvents();
        void SetBGColor( unsigned int color );
        void SetBGAlpha( float alpha );
        void SetPickRange( int range );
        float PickDistance();

    public:
        static void ExitFunction();

    public:
        bool quitSignal;

    protected:
        void GetRealCoordinates( float& x, float& y );

    private:
        // UPDATE : Pan/Zoom
        double _real_width;
        double _real_height;
        double _zoom_level;
        double _x_offset;
        double _y_offset;
        int _pan_mode;
        int _zoom_mode;
        int _mouse_x;
        int _mouse_y;
        int _pan_start_x;
        int _pan_start_y;
        int _zoom_start_x;
        int _zoom_start_y;
        // END : Pan/Zoom
        int _pick_range;
        float _pick_distance;
        int m_keyCode;
        SDL_Event m_event;
        SDL_Surface *m_screen;
        int m_screen_width;
        int m_screen_height;
        float bgRed;
        float bgGreen;
        float bgBlue;
        float bgAlpha;
        double vpLeft;
        double vpRight;
        double vpBottom;
        double vpTop;
        double vpNear;
        double vpFar;

        // Methods.
        void InitVars();
        void GL_Init();
        void ProcessKeys( SDL_Event &event );
        // UPDATE : Pan/Zoom
        void ButtonEvent( SDL_MouseButtonEvent* button );
        void MotionEvent( SDL_MouseMotionEvent* motion );
        // END : Pan/Zoom
};


#endif

