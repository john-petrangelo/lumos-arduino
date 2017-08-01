#include "Colors.h"
#include "Patterns.h"

/*
 * Apply the provided pixels array (pattern) to the light strip.
 */
void Patterns::applyPixels(Pixels pixels, int firstPixel, int lastPixel) {
  for (int i = firstPixel; i < lastPixel; i++) {
    strip.setPixelColor(i, pixels[i]);
  }
}

/*
 * Add two patterns together.
 */
void Patterns::addPatterns(Pixels out, int firstPixel, int lastPixel, Pixels p1, Pixels p2) {
  for (int i = firstPixel; i < lastPixel; i++) {
    out[i] = Colors::add(p1[i], p2[i]);
  }
}

/*
 * Blend two patterns together.
 */
void Patterns::blendPatterns(Pixels out, int firstPixel, int lastPixel, Pixels p1, Pixels p2, int ratio) {
  for (int i = firstPixel; i < lastPixel; i++) {
    out[i] = Colors::blend(p1[i], p2[i], ratio);
  }
}

/*
 * Reverse a pattern.
 */
void Patterns::reversePattern(Pixels out, Pixels in, int firstPixel, int lastPixel) {
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
void Patterns::setSolidColor(Pixels pixels, int firstPixel, int lastPixel, Color color) {
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
void Patterns::setGradient(Pixels pixels, int count, ...) {
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
      pixels[index++] = Colors::blend(prevColor, nextColor, 100 * i / (segmentSize - 1));
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
void Patterns::setSineWave(Pixels pixels, int firstPixel, int lastPixel, Color c1, Color c2, int period, int phase) {
  for (int i = firstPixel; i < lastPixel; i++) {
    float const ratio = 0.5 * (1 + sin(2 * PI * (i + phase) / (float)period));
    Color const newColor = Colors::blend(c1, c2, 100 * ratio);
    pixels[i] = newColor;
  }
}

