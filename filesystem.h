#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bitmap.h"

#define MAX_PATH_LENGTH 100
#define MAX_LINE_SIZE 100

const char* const extension = ".ept";

class FileSystem
{
    public:
        FileSystem(const char* dir1, const char* dir2) : read("r"), write("w"), 
                                                        m_in_dir(dir1), m_out_dir(dir2) {}
        ~FileSystem();

        Bitmap* loadBitmap(const char* name);
        bool saveBitmap(Bitmap& bitmap);

        static FileSystem* get() 
        {
            static FileSystem* file_system = new FileSystem("bitmaps/", "bitmaps/");
            return file_system;
        }

        const char* const read; //= "r";
        const char* const write;// = "w";
    protected:
        const char* m_in_dir;
        const char* m_out_dir;

        FILE* m_input_file;
        FILE* m_output_file;
        const char* m_mode;
};

#endif