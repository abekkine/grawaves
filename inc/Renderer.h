#ifndef RENDERER_H
#define RENDERER_H

#include <Mode.h>
#include <GLDisplay.h>
#include <Body.h>
#include <Wave.h>

class Renderer : public GLDisplay {

    public:
        Renderer();
        void Render();
        void UserKeys( int keycode, bool shift, bool ctrl );
        void RegisterBodies( BodyVectorType& bodies );
        void RegisterWaves( WaveVectorType& waves );
        void BodyDisplay( bool enable );
        void WaveDisplay( bool enable );
        void SetBodyColor( unsigned int color );
        void SetWaveColor( unsigned int color );
        void SetWaveAlpha( double alphafactor );

    private:
        Mode* _mode;

        float bodyRed;
        float bodyGreen;
        float bodyBlue;
        float waveRed;
        float waveGreen;
        float waveBlue;
        double alphafactor;
        bool fBodiesAvailable;
        bool fBodyDisplayEnable;
        BodyVectorType bodies;
        bool fWavesAvailable;
        bool fWaveDisplayEnable;
        WaveVectorType waves;

        void RenderBodies();
        void RenderWaves();
        void RenderSingleWave( Vector center, double radius, float *color );
        void PickRequest();
};

#endif

