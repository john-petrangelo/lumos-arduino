#include "defs.h"
#include "Colors.h"

#define R_SHIFT 16
#define G_SHIFT  8
#define B_SHIFT  0

#define R_MASK 0x00FF0000
#define G_MASK 0x0000FF00
#define B_MASK 0x000000FF

Color Colors::makeColor(uint8_t red, uint8_t green, uint8_t blue) {
  return ((uint32_t)red << R_SHIFT) | ((uint32_t)green << G_SHIFT) | ((uint32_t)blue << B_SHIFT);
}

/**
 * Blend the two provided colors to make a new color.
 * 
 * @param a First color
 * @param b Second color
 * @param ratio Ratio of the blend between a and b. 0 means all a, 100 means all b, 50 means 50% of each.
 */
Color Colors::blend(Color a, Color b, int ratio) {
    uint8_t red = blend(getRed(a), getRed(b), ratio);
    uint8_t green = blend(getGreen(a), getGreen(b), ratio);
    uint8_t blue = blend(getBlue(a), getBlue(b), ratio);
//    printf("red=0x%X green=0x%X blue=0x%X\n", red, green, blue);

    return makeColor(red, green, blue);
}

uint8_t Colors::blend(uint8_t a, uint8_t b, int ratio) {
  return a + (b - a) * ratio / 100;
}

Color Colors::fade(Color c, int ratio) {
  return blend(BLACK, c, ratio);
}

Color Colors::add(Color a, Color b) {
 return makeColor(
     constrain(getRed(a)   + getRed(b),  0, 255), 
     constrain(getGreen(a) + getGreen(b), 0, 255), 
     constrain(getBlue(a)  + getBlue(b),  0, 255));
}

uint8_t Colors::getRed(Color color) {
  return (color & R_MASK) >> R_SHIFT;
}

uint8_t Colors::getGreen(Color color) {
  return (color & G_MASK) >> G_SHIFT;
}

uint8_t Colors::getBlue(Color color) {
  return (color & B_MASK) >> B_SHIFT;
}
