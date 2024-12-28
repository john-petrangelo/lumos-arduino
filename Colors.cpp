#include <algorithm>

#include "Colors.h"

#define R_SHIFT 16
#define G_SHIFT  8
#define B_SHIFT  0

#define R_MASK 0x00FF0000
#define G_MASK 0x0000FF00
#define B_MASK 0x000000FF

Color Colors::makeColor(uint8_t const red, uint8_t const green, uint8_t const blue) {
  return (static_cast<uint32_t>(red) << R_SHIFT) | (static_cast<uint32_t>(green) << G_SHIFT) | (static_cast<uint32_t>(blue) << B_SHIFT);
}

/**
 * Blend the two provided colors to make a new color.
 * 
 * @param a First color
 * @param b Second color
 * @param ratio The ratio of the blend between a and b. 0.0 means all a, 1.0 means all b, 0.5 means 50% of each.
 */
Color Colors::blend(Color const a, Color const b, float const ratio) {
    uint8_t const red = blend_channel(getRed(a), getRed(b), ratio);
    uint8_t const green = blend_channel(getGreen(a), getGreen(b), ratio);
    uint8_t const blue = blend_channel(getBlue(a), getBlue(b), ratio);

    return makeColor(red, green, blue);
}

uint8_t Colors::blend_channel(uint8_t const a, uint8_t const b, float const ratio) {
  return a + static_cast<float>(b - a) * ratio;
}

Color Colors::fade(Color const c, float const ratio) {
  return blend(BLACK, c, ratio);
}

/**
 * Adds two colors component-wise
 *
 * @param a The first color to add.
 * @param b The second color to add.
 * @return A new Color representing the sum of the two colors, with each component
 *         (red, green, blue) clamped to a maximum of 255 to prevent overflow.
 */
Color Colors::add(Color const a, Color const b) {
 return makeColor(
     std::min(255, getRed(a) + getRed(b)),
     std::min(255, getGreen(a) + getGreen(b)),
     std::min(255, getBlue(a) + getBlue(b)));
}

uint8_t Colors::getRed(Color const color) {
  return (color & R_MASK) >> R_SHIFT;
}

uint8_t Colors::getGreen(Color const color) {
  return (color & G_MASK) >> G_SHIFT;
}

uint8_t Colors::getBlue(Color const color) {
  return (color & B_MASK) >> B_SHIFT;
}
