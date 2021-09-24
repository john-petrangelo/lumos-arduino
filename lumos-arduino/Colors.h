#ifndef _COLORS_H_
#define _COLORS_H_

#include "defs.h"

typedef uint32_t Color;

class Colors {
  public:
    static Color blend(Color a, Color b, int ratio);
    static Color fade(Color c, int ratio);
    static Color add(Color a, Color b);

  private:
    static uint8_t blend(uint8_t a, uint8_t b, int ratio);
    static uint8_t getRed(Color color);
    static uint8_t getGreen(Color color);
    static uint8_t getBlue(Color color);
};

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

#endif // _COLORS_H_
