#ifndef MODE_H
#define MODE_H

class Mode
{
    public:
        typedef enum {
            MODE_RUN = 0,
            MODE_PAUSE,
            MODE_STEP,
            MODE_RESET,
            MODE_QUIT
        } ModeType;

        typedef enum {
            REQ_TOGGLE = 0,
            REQ_STEP,
            REQ_QUIT,
            REQ_RESET,
            REQ_COLOR_WAVES,
            REQ_NONE
        } RequestType;

    private:
        static Mode* _instance;
        ModeType _mode;
        RequestType _request;
        Mode();
        void Defaults();

        bool fDebugEnable;
        void Debug( const char *debugMsg );

    public:
        static Mode* GetInstance();
        ~Mode();

        void Request( RequestType request );
        RequestType GetRequest();
        void SetMode( ModeType mode );
        ModeType GetMode();
        void Toggle();
        void DebugEnable( bool value );
};

#endif

