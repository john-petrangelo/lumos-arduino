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
  
  uint32_t prevColor = va_arg(argList, Color);
  count--;
  for (; count > 0; count--) {
    uint32_t nextColor = va_arg(argList, Color);
    for (int i = 0; i < segmentSize; i++) {
      pixels[index++] = blend(prevColor, nextColor, 100 * i / (segmentSize - 1));
    }

    prevColor = nextColor;
  }

  va_end(argList);
}

