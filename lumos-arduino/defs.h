#ifndef _DEFS_H_
#define _DEFS_H_

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include <stdint.h>

enum Direction {
  LEFT, RIGHT
};

uint16_t const NUM_PIXELS = 60;
typedef uint32_t Color;
typedef Color* Pixels;
typedef Color PixelsArray[60];

Color const BLACK =  0x000000;
Color const BLUE =   0x0000FF;
Color const GREEN =  0x00FF00;
Color const CYAN =   0x00FFFF;
Color const RED =    0xFF0000;
Color const PURPLE = 0xFF00FF;
Color const YELLOW = 0xFFFF00;
Color const WHITE =  0xFFFFFF;
Color const ORANGE = 0xFF7F00;
Color const INDIGO = 0x4B0082;
Color const VIOLET = 0x8F00FF;

extern Adafruit_NeoPixel strip;

#endif // _DEFS_H_

