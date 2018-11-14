
#include "filesystem.h"

//#define DEBUG

Bitmap* FileSystem::loadBitmap(const char* name)
{
    Bitmap* bitmap = NULL;
    char path[MAX_PATH_LENGTH];
    char line[MAX_LINE_SIZE];
    int width = 0;
    int height = 0;

    sprintf(path, "%s%s%s", m_in_dir, name, extension);

    m_mode = read;
    m_input_file = fopen(path, m_mode);

    if(m_input_file == NULL)
    {
        fprintf(stderr, "Could not open file: %s\nFrom path: %s\n", name, path);
        return NULL;
    }
    else
    {
        fprintf(stdout, "Reading from %s...\n", path);

        //Get width and height first
        if(fscanf(m_input_file, "%d %d", &width, &height) == 2)
        {
            if(width != 0)
            {
                printf("Loaded bitmap width: %d\n", width);
            }
            else if(height != 0)
            {
                printf("Loaded bitmap height: %d\n", height);
            }
        }
        else
        {
            fprintf(stdout, "Could not read width and height from %s...\nError: END_OF_FILE\n", path);
            return NULL;
        }

        //Remember to delete this bitmap
        bitmap = new Bitmap(name, width, height);

        #ifdef DEBUG
            bitmap->printBitmap();
        #endif

        fprintf(stdout, "Reading pixels from: %s\n", path);

        //Get pixel colors now
        int index = 0;
        e_std::e_word color_int = 0;//(*bitmap)[index++].color->toInt();
        while(fscanf( m_input_file, "%d", &color_int ) == 1)
        {
            if(index > width * height) break;
            (*bitmap)[index++].color = &get_color_INT(color_int);//&((*bitmap)[index++].color->set(color_int));
        }

        fprintf(stdout, "Successfully loaded bitmap: %s from: %s\n", name, path);
        fclose(m_input_file);
        return bitmap;
    }
}

bool FileSystem::saveBitmap(Bitmap& bitmap)
{
    char path[MAX_PATH_LENGTH];
    sprintf(path, "%s%s%s", m_out_dir, bitmap.getName(), extension);
    bool success = true;
    int width = bitmap.getWidth();
    int height = bitmap.getHeight();

    m_mode = write;
    m_output_file = fopen(path, m_mode);

    if(m_output_file == NULL)
    {
        fprintf(stderr, "Could not write to file: %s\nAt path: %s\n", bitmap.getName(), path);
        success = false;
        return success;
    }
    else
    {
        fprintf(stdout, "Writing to %s...\n", path);
        fprintf(m_output_file, "%d %d\n", width, height);

        for(int y = 0; y < bitmap.getHeight(); y++)
        {
            for(int x = 0; x < bitmap.getWidth(); x++)
            {
                fprintf(m_output_file, " %d ", bitmap[x + (y * bitmap.getWidth())].color->toInt());
            }
            fprintf(m_output_file, "\n");
        }

        fclose(m_output_file);
        return success;
    }
}