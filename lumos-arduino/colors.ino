#define R_SHIFT 16
#define G_SHIFT  8
#define B_SHIFT  0

#define R_MASK 0x00FF0000
#define G_MASK 0x0000FF00
#define B_MASK 0x000000FF

/**
 * Blend the two provided colors to make a new color.
 * 
 * @param a First color
 * @param b Second color
 * @param ratio Ratio of the blend between a and b. 0 means all a, 100 means all b, 50 means 50% of each.
 */
Color blend(Color a, Color b, int ratio) {
    Color x = ColorsX::blend(YELLOW, BLUE, 50);

    uint8_t red = blend(getRed(a), getRed(b), ratio);
    uint8_t green = blend(getGreen(a), getGreen(b), ratio);
    uint8_t blue = blend(getBlue(a), getBlue(b), ratio);

    return strip.Color(red, green, blue);
}

inline uint8_t blend(uint8_t a, uint8_t b, int ratio) {
  return a + (b - a) * ratio / 100;
}

inline uint8_t getRed(Color color) {
  return (color & R_MASK) >> R_SHIFT;
}

inline uint8_t getGreen(Color color) {
  return (color & G_MASK) >> G_SHIFT;
}

inline uint8_t getBlue(Color color) {
  return (color & B_MASK) >> B_SHIFT;
}

inline Color fade(Color c, int ratio) {
  return blend(BLACK, c, ratio);
}

