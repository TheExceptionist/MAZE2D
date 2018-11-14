#include "geometry.h"
using namespace e_std;

const color_t& get_color_ARGB(e_byte set_a, e_byte set_r, e_byte set_g, e_byte set_b)
{
    for(auto color = colors.begin(); color != colors.end(); ++color)
    {
        const color_t* check_color = *color;
        if(check_color->a == set_a && check_color->r == set_r && check_color->g == set_g && check_color->b == set_b)
        {
            return *check_color;
        }
    }

    color_t* temp_color = new color_t;
    temp_color->a = set_a;
    temp_color->r = set_r;
    temp_color->g = set_g;
    temp_color->b = set_b;

    addColor(*temp_color);
    return *temp_color;
}

const color_t& get_color_INT(e_std::e_word color_int)
{
    e_byte a = (color_int >> 24) & COLOR_MASK;
    e_byte r = (color_int >> 16) & COLOR_MASK;
    e_byte g = (color_int >> 8) & COLOR_MASK;
    e_byte b = (color_int) & COLOR_MASK;

    return get_color_ARGB(a, r, g, b);
}

void initColors()
{
    addColor(RED);
    addColor(BLUE);
    addColor(GREEN);
    addColor(GRAY);
    addColor(DARK_BLUE);
    addColor(BLACK);
}