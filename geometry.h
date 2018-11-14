#ifndef GEOMETRY_H
#define GEOMETRY_H

namespace e_std
{  
    typedef struct color_s color_t;
    typedef struct pixel_s pixel_t;

    struct color_s 
    {
        e_byte a;
        e_byte r;
        e_byte g;
        e_byte b;

        color_t& operator/=(int value)
        {
            r /= value;
            g /= value;
            b /= value;

            return *this;
        }
    };

    struct pixel_s
    {
        int x;
        int y;
        color_t* color;
    };
}

const e_std::color_t RED = {0xFF, 0xFF, 0, 0};
const e_std::color_t BLUE = {0xFF, 0, 0, 0xFF};
const e_std::color_t GREEN = {0xFF, 0, 0xFF, 0};
const e_std::color_t GRAY = {0xFF, 0xd3, 0xd3, 0xd3};
const e_std::color_t DARK_BLUE = {0xFF, 0, 0x33, 0x66};
const e_std::color_t BLACK = {0xFF, 0, 0, 0};

#endif