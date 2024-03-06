#ifndef _PATTERNS_H_
#define _PATTERNS_H_

#include "defs.h"

class Patterns {
  public:
    static void applyPixels(Adafruit_NeoPixel &strip, Pixels pixels, int firstPixel, int lastPixel);
// TODO
// static void applyPixels(Adafruit_NeoPixel &strip, Pixels pixels) { applyPixels(strip, pixels, 0, strip.numPixels()); }
    
    static void addPatterns(Pixels out, int firstPixel, int lastPixel, Pixels p1, Pixels p2);
    static void addPatterns(Adafruit_NeoPixel &strip, Pixels out, Pixels p1, Pixels p2) { addPatterns(out, 0, strip.numPixels(), p1, p2); }

    static void blendPatterns(Pixels out, int firstPixel, int lastPixel, Pixels p1, Pixels p2, int ratio);
    static void blendPatterns(Adafruit_NeoPixel &strip, Pixels out, Pixels p1, Pixels p2, int ratio) { blendPatterns(out, 0, strip.numPixels(), p1, p2, ratio); }

    static void reversePattern(Pixels out, Pixels in, int firstPixel, int lastPixel);
    static void reversePattern(Adafruit_NeoPixel &strip, Pixels out, Pixels in) { reversePattern(out, in, 0, strip.numPixels()); }

    static void setSolidColor(Pixels pixels, int firstPixel, int lastPixel, Color color);
    static void setSolidColor(Adafruit_NeoPixel &strip, Pixels pixels, Color color) { setSolidColor(pixels, 0, strip.numPixels(), color); }

    static void setGradient(Pixels pixels, int firstPixel, int lastPixel, int count, ...);

    static void setSineWave(Pixels pixels, int firstPixel, int lastPixel, Color c1, Color c2, int period, int phase);
    static void setSineWave(Adafruit_NeoPixel &strip, Pixels pixels, Color c1, Color c2, int period, int phase) { setSineWave(pixels, 0, strip.numPixels(), c1, c2, period, phase); }
};

#endif // _PATTERNS_H_
