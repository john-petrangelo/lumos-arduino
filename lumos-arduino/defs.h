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
typedef Color PixelsArray[NUM_PIXELS];

extern Adafruit_NeoPixel strip;

#endif // _DEFS_H_
