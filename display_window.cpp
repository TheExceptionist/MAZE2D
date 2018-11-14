#include "display_window.h"

DisplayWindow::DisplayWindow(e_std::e_str name, const e_std::e_word width, const e_std::e_word height)
{
    m_name = name;
    m_width = width;
    m_height = height;
    m_running = TRUE;
}

DisplayWindow::~DisplayWindow()
{
    close();
}

e_std::e_bool DisplayWindow::init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != SDL_SUCCESS)
    {
        printf("Could not initialize video! Error: %s\n", SDL_GetError());
        return FALSE;
    }
    else
    {
        m_window = SDL_CreateWindow(m_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);

        if(m_window != NULL)
        {
            m_surface = SDL_GetWindowSurface(m_window);

            if(m_surface == NULL)
            {
                printf("Surface could not be created! Error: %s\n", SDL_GetError());
                return FALSE;
            }
        }
        else
        {
            printf("Window could not be created! Error: %s\n", SDL_GetError());
            return FALSE;
        }
    }

    return TRUE;
}

void DisplayWindow::close()
{
    SDL_FreeSurface(m_surface);
    m_surface = NULL;

    SDL_DestroyWindow(m_window);
    m_window = NULL;

    SDL_Quit();
    m_running = FALSE;
}

void DisplayWindow::update()
{
    SDL_LockSurface(m_surface);
    
    clearColor(&BLUE);
    //handleInput();
    SDL_UpdateWindowSurface(m_window);
    
    SDL_UnlockSurface(m_surface);
}

void DisplayWindow::clearColor(const e_std::color_t* const color)
{
    fillRect(0, 0, m_width, m_height, color);
}

void putPixel(e_std::pixel_t pixel)//, e_std::e_word y, const e_std::color_t* const color)
{

}

void DisplayWindow::fillRect(e_std::e_word x, e_std::e_word y, e_std::e_word width, e_std::e_word height, const e_std::color_t* const color)
{
    e_std::e_word* pixel_addr = (e_std::e_word*)m_surface->pixels;

    //Check bounds
    if(!checkBounds(x, y, width, height))
    {
        return;
    }

    //Offset the buffer pointer to the specific pixel int memory 
    pixel_addr += x + (y * m_width);

    for(int pixel_y = 0; pixel_y < height; pixel_y++)
    {
        for(int pixel_x = 0; pixel_x < width; pixel_x++)
        {
            storePixel(pixel_addr, pixel_x, color);
        }

        pixel_addr += m_width;
    }
}

void DisplayWindow::storePixel(e_std::e_word* addr, const int x, const e_std::color_t* const color)
{
    //Low endian
    e_std::e_byte* pixel_byte = (e_std::e_byte*) (addr + x);
    *pixel_byte = color->b;
    *(pixel_byte + 1) = color->g;
    *(pixel_byte + 2) = color->r;
    *(pixel_byte + 3) = color->a;
}

bool DisplayWindow::checkBounds(const int x, const int y, int width, int height)
{
    if(x > m_width) return FALSE;
    if(y > m_height) return FALSE;
    if(x + width > m_width) width = m_width - x; 
    if(y + height > m_height) height = m_height - y;

    return TRUE; 
}


//Make Modular
void DisplayWindow::drawLine(e_std::e_word start_x, e_std::e_word start_y, e_std::e_word end_x, e_std::e_word end_y, const e_std::color_t* const color)
{
    e_std::e_word begin_x = start_x;
    e_std::e_word begin_y = start_y;
    e_std::e_word last_x = end_x;
    e_std::e_word last_y = end_y;

    if(start_x > end_x)
    {
        begin_x = end_x;
        last_x = start_x;
    }
    if(start_y > end_y)
    {
        begin_y = end_y;
        last_y = start_y;
    }

    e_std::e_word dist_x = last_x - begin_x;
    e_std::e_word dist_y = last_y - begin_y;
    e_std::e_word delta_x = 0;
    e_std::e_word delta_y = 0;

    if(dist_x > dist_y)
    {
        delta_x = dist_x / dist_y;
    }
    else
    {
        delta_y = dist_y / dist_x;
    }

    if(delta_x > 0)
    {
        for(int y = begin_y; y < begin_y + dist_y; y++)
        {
            for(int x = begin_x; x < begin_x + delta_x; x++)
            {
                putPixel(x + (y * delta_x), y, color);
            }
        }
    }
    else
    {
        for(int x = begin_x; x < begin_x + dist_x; x++)
        {
            for(int y = begin_y; y < begin_y + delta_y; y++)
            {
                putPixel(x, y + (x * delta_y), color);
            }
        }
    }
}

//Make modular
void DisplayWindow::putPixel(e_std::e_word x, e_std::e_word y, const e_std::color_t* const color)
{
    if(x > m_width) return;
    if(y > m_height) return;

    SDL_LockSurface(m_surface);
    e_std::e_word* buffer = (e_std::e_word*)m_surface->pixels;
    e_std::e_byte a = color->a;
    e_std::e_byte r = color->r;
    e_std::e_byte g = color->g;
    e_std::e_byte b = color->b;

    buffer += x + (y * m_width);

    e_std::e_byte* pixel_color = (e_std::e_byte*) (buffer);

    *pixel_color = b;
    *(pixel_color + 1) = g;
    *(pixel_color + 2) = r;
    *(pixel_color + 3) = a;
    SDL_UnlockSurface(m_surface);
}

void DisplayWindow::handleInput()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
            {
                close();
            } break;
            case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_LEFT:
                    {
                        printf("Left\n");
                //        InputManager::get().getKey(KEY_LEFT).execute();
                    } break;
                    case SDLK_RIGHT:
                    {
                        printf("Right\n");
                //        InputManager::get().getKey(KEY_RIGHT).execute();
                    } break;
                    case SDLK_UP:
                    {
                        printf("Up\n");
                //        InputManager::get().getKey(KEY_UP).execute();
                    } break;
                    case SDLK_DOWN:
                    {
                        printf("Down\n");
                //        InputManager::get().getKey(KEY_DOWN).execute();
                    } break;
                    default:
                    {
                        printf("Pressed\n");
                    } break;
                }
            } break;
            case SDL_KEYUP:
            {

            } break;
        }
    }
}