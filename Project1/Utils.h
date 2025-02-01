#pragma once
#include <cstdint>

#define MAKE_WORD(low, high) ((high << 8) | low)

#define GET_HIGH_BYTE(val) ((val >> 8) & 0xFF)
#define GET_LOW_BYTE(val) (val & 0xFF)
#define IS_NEGATIVE(val) (val & 0x80)

#define MEM_SIZE 64*1024

using byte = uint8_t;
using word = uint16_t;

