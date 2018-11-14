#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define DEBUG

namespace e_std
{
    typedef uint8_t e_byte;
    typedef uint16_t e_halfword;
    typedef uint32_t e_word;
    typedef uint64_t e_doubleword;

    typedef int8_t e_int8;
    typedef int16_t e_int16;
    typedef int32_t e_int32;
    typedef int64_t e_int64;

    typedef const char* e_str;
    typedef e_byte e_bool;
}

#endif
