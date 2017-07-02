/*
 * Apply the provided pixels array (pattern) to the light strip.
 */
inline void applyPixels(Pixels pixels) { applyPixels(pixels, 0, strip.numPixels()); }
void applyPixels(Pixels pixels, int firstPixel, int lastPixel) {
  for (int i = firstPixel; i < lastPixel; i++) {
    strip.setPixelColor(i, pixels[i]);
  }
}

/*
 * Add two patterns together.
 */
inline void addPatterns(Pixels out, Pixels p1, Pixels p2) { addPatterns(out, 0, strip.numPixels(), p1, p2); }
void addPatterns(Pixels out, int firstPixel, int lastPixel, Pixels p1, Pixels p2) {
  for (int i = firstPixel; i < lastPixel; i++) {
    uint16_t red1 = getRed(p1[i]);
    uint16_t red2 = getRed(p2[i]);
    uint16_t green1 = getGreen(p1[i]);
    uint16_t green2 = getGreen(p2[i]);
    uint16_t blue1 = getBlue(p1[i]);
    uint16_t blue2 = getBlue(p2[i]);

    out[i] = strip.Color(
      constrain(red1 + red2, 0, 255), 
      constrain(green1 + green2, 0, 255),
      constrain(blue1 + blue2, 0, 255));
  }
}

/*
 * Blend two patterns together.
 */
inline void blendPatterns(Pixels out, Pixels p1, Pixels p2, int ratio) { blendPatterns(out, 0, strip.numPixels(), p1, p2, ratio); }
void blendPatterns(Pixels out, int firstPixel, int lastPixel, Pixels p1, Pixels p2, int ratio) {
  for (int i = firstPixel; i < lastPixel; i++) {
    out[i] = blend(p1[i], p2[i], ratio);
  }
}

/*
 * Reverse a pattern.
 */
inline void reversePattern(Pixels out, Pixels in) { reversePattern(out, in, 0, strip.numPixels()); }
void reversePattern(Pixels out, Pixels in, int firstPixel, int lastPixel) {
  for (int i = firstPixel; i < lastPixel; i++) {
    out[i] = in[lastPixel - i - 1];
  }
}

/*
 * Set a solid color pattern.
 * 
 * color        Color to set
 * firstPixel   First pixel in range, inclusive
 * lastPixel    Last pixel in range, exclusive
 */
inline void setSolidColor(Pixels pixels, Color color) { setSolidColor(pixels, 0, strip.numPixels(), color); }
void setSolidColor(Pixels pixels, int firstPixel, int lastPixel, Color color) {
  for (int i = firstPixel; i < lastPixel; ++i) {
    pixels[i] = color;
  }
}

/*
 * Set a gradient color pattern. The number of defined color points is variable.
 * 
 * Example: to run a gradient from red to yellow to blue:
 *     setGradient(pixels, 3, RED, YELLOW, BLUE);
 */
void setGradient(Pixels pixels, int count, ...) {
  if (count < 2 || count > 20) {
    return;
  }
  
  int segmentSize = strip.numPixels() / (count - 1);

  // Declare a va_list macro and initialize it with va_start.
  va_list argList;
  va_start(argList, count);

  int index = 0;
  
  Color prevColor = va_arg(argList, Color);
  count--;
  for (; count > 0; count--) {
    Color nextColor = va_arg(argList, Color);
    for (int i = 0; i < segmentSize; i++) {
      pixels[index++] = blend(prevColor, nextColor, 100 * i / (segmentSize - 1));
    }

    prevColor = nextColor;
  }

  va_end(argList);
}

/*
 * Set a sinusoidal wave color pattern, oscillating between the two provided colors.
 * period  Period of the sine wave in pixels. May be shorter, same, or longer than the strip length.
 * phase   Phase of the sine wave in pixels.
 */

void setSineWave(Pixels pixels, Color c1, Color c2, int period, int phase) { setSineWave(pixels, 0, strip.numPixels(), c1, c2, period, phase); }
void setSineWave(Pixels pixels, int firstPixel, int lastPixel, Color c1, Color c2, int period, int phase) {
  for (int i = firstPixel; i < lastPixel; i++) {
    float const ratio = 0.5 * (1 + sin(2 * PI * (i + phase) / (float)period));
    Color const newColor = blend(c1, c2, 100 * ratio);
    pixels[i] = newColor;
  }
}

