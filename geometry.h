#ifndef GEOMETRY_H
#define GEOMETRY_H

#define COLOR_MASK 0xFF

#include <stdlib.h>
#include <vector>
#include "defs.h"

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

        void printColor() const
        {
            printf(" [A: %d R: %d G: %d B: %d] ", a, r, g, b);
        }

        void set(e_std::e_word color_int)
        {
            a = (color_int >> 24) & COLOR_MASK;
            r = (color_int >> 16) & COLOR_MASK;
            g = (color_int >> 8) & COLOR_MASK;
            b = (color_int) & COLOR_MASK;
        }

        e_std::e_word toInt() const
        {
            return (a << 24) | (r << 16) | (g << 8) | b;
        }
    };

    struct pixel_s
    {
        int x;
        int y;
        const color_t* color;

        void set(int set_x, int set_y, const color_t* const set_color)
        {
            x = set_x;
            y = set_y;
            color = set_color;
        }

        void deletePixel()
        {
            delete color;
        }

        void printPixel() const
        {
            printf("X: %d Y: %d | ", x, y);
            color->printColor();
        }
    };
}

static std::vector<const e_std::color_t*> colors;

static void addColor(const e_std::color_t& color)
{
    colors.push_back(&color);
}

const e_std::color_t RED = {0xFF, 0xFF, 0, 0};
const e_std::color_t BLUE = {0xFF, 0, 0, 0xFF};
const e_std::color_t GREEN = {0xFF, 0, 0xFF, 0};
const e_std::color_t GRAY = {0xFF, 0xd3, 0xd3, 0xd3};
const e_std::color_t DARK_BLUE = {0xFF, 0, 0x33, 0x66};
const e_std::color_t BLACK = {0xFF, 0, 0, 0};

 //Reslove dup 
const e_std::color_t& get_color_ARGB(e_std::e_byte set_a, e_std::e_byte set_r, e_std::e_byte set_g, e_std::e_byte set_b);
const e_std::color_t& get_color_INT(e_std::e_word color_int);
void initColors();

#endif