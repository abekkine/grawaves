#ifndef UTIL_H
#define UTIL_H

class Util
{
    public:
        static void ConvertColor(unsigned int color, float *array, bool alpha=true);
        static void ConvertColor( unsigned int rgb, float& r, float& g, float& b );
};

#endif

