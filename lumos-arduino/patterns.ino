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

