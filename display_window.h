#ifndef DISPLAY_H
#define DISPLAY_H 

#define SDL_SUCCESS 0

#include <SDL2/SDL.h>
#include "defs.h"
#include "geometry.h"

//Declaration of a data type ends in a semicolon
class DisplayWindow
{
    public:
        DisplayWindow(e_std::e_str name, const e_std::e_word width, const e_std::e_word height);
        ~DisplayWindow();

        e_std::e_bool init();
        void update();
        void close();

        void fillRect(e_std::e_word x, e_std::e_word y, e_std::e_word width, e_std::e_word height, const e_std::color_t* const color);
        void putPixel(e_std::pixel_t* pixel);

        //Draw a straigth line
        void drawLine(e_std::e_word start_x, e_std::e_word start_y, e_std::e_word end_x, e_std::e_word end_y, const e_std::color_t* const color);
        void putPixel(e_std::e_word x, e_std::e_word y, const e_std::color_t* const color);

        e_std::e_word getWidth() const {return m_width;}
        e_std::e_word getHeight() const {return m_height;}
        e_std::e_str getName() const {return m_name;}

        e_std::e_bool isRunning() const {return m_running;}
        void setRunning(e_std::e_bool value) { m_running = value; }
    private:
        SDL_Window* m_window;
        SDL_Surface* m_surface;

        e_std::e_word m_width;
        e_std::e_word m_height;
        e_std::e_str m_name;

        e_std::e_bool m_running;

        void storePixel(e_std::e_word* pixel_addr, const e_std::e_word xOff, const e_std::color_t* const color);
        bool checkBounds(const e_std::e_word x, const e_std::e_word y, e_std::e_word width, e_std::e_word height);
        bool checkBounds(const e_std::e_word x, const e_std::e_word y);
        void clearColor(const e_std::color_t* const color);

        //Move this into the input handler
        void handleEvents();
};

#endif

