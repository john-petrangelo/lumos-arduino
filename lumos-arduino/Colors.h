#ifndef _COLORS_H_
#define _COLORS_H_

#include "defs.h"

class Colors {
  public:
    static Color blend(Color a, Color b, int ratio);
    static Color fade(unsigned long c, int ratio);
    static Color add(Color a, Color b);

  private:
    static uint8_t blend(uint8_t a, uint8_t b, int ratio);
    static uint8_t getRed(Color color);
    static uint8_t getGreen(Color color);
    static uint8_t getBlue(Color color);
};

#endif // _COLORS_H_

