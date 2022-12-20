#include <Util.h>

void Util::ConvertColor( unsigned int color, float *array, bool alpha )
{
    if( alpha )
    {
        array[0] = ( (color >> 24) & 0xff ) / 255.0;
        array[1] = ( (color >> 16) & 0xff ) / 255.0;
        array[2] = ( (color >> 8) & 0xff ) / 255.0;
        array[3] = ( color & 0xff ) / 255.0;
    }
    else
    {
        array[0] = ( (color >> 16) & 0xff ) / 255.0;
        array[1] = ( (color >> 8) & 0xff ) / 255.0;
        array[2] = ( color & 0xff ) / 255.0;
    }
}

void Util::ConvertColor( unsigned int rgb, float& r, float& g, float& b )
{
    r = ( (rgb>>16) & 0xff ) / 255.0;
    g = ( (rgb>>8) & 0xff ) / 255.0;
    b = ( rgb & 0xff ) / 255.0;
}
