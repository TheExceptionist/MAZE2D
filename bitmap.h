#ifndef BITMAP_H
#define BITMAP_H

#include "defs.h"
#include "geometry.h"

class Bitmap
{
    public:
        Bitmap(const char* name, const int width, const int height);
        ~Bitmap();

        e_std::pixel_t& operator [](int index) { return m_pixels[index]; }
        e_std::pixel_t& get(const int x, const int y) const { return m_pixels[x + (y * m_width)]; }

        void save(const char* path);

        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }
        const char* getName() const { return m_name; }

        void printBitmap();
        void clear(const e_std::color_t* color);
    private:
        void init();

        const int m_width;
        const int m_height;
        const char* m_name;
        e_std::pixel_t* m_pixels;

       // e_std::e_byte* m_marker;
};

#endif