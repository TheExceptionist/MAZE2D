#include <stdio.h>
#include "bitmap.h"

Bitmap::Bitmap(const char* name, const int width, const int height)
    : m_width(width),
    m_height(height)
{
    m_name = name;
    //m_marker = MemoryManager::get().getMarker();
    m_pixels = new e_std::pixel_t[m_width * m_height];

    init();
    //clear(0);
}

void Bitmap::init()
{
    for(int y = 0; y < getHeight(); y++)
    {
        for(int x = 0; x < getWidth(); x++)
        {
            m_pixels[x + (y * getWidth())].set(x, y, &BLACK);
            //printf(" [A: %d R: %d G: %d B: %d] ", m_pixels[x + (y * getWidth())].a, m_pixels[x + (y * getWidth())].r, m_pixels[x + (y * getWidth())].g, m_pixels[x + (y * getWidth())].b);
        }
        //printf("\n");
    }
}

Bitmap::~Bitmap()
{
    //clear(0);
    delete m_pixels;
}

void Bitmap::printBitmap()
{
    for(int y = 0; y < getHeight(); y++)
    {
        for(int x = 0; x < getWidth(); x++)
        {
            m_pixels[x + (y * getWidth())].printPixel();
            //printf(" [A: %d R: %d G: %d B: %d] ", m_pixels[x + (y * getWidth())].a, m_pixels[x + (y * getWidth())].r, m_pixels[x + (y * getWidth())].g, m_pixels[x + (y * getWidth())].b);
        }
        printf("\n");
    }
}

void Bitmap::clear(const e_std::color_t* set_color)
{
    for(int y = 0; y < getHeight(); y++)
    {
        for(int x = 0; x < getWidth(); x++)
        {
            m_pixels[x + (y * getWidth())].color = set_color;
            //printf(" [%d] ", pixels[x + (y * getWidth())]);
        }
    }
}