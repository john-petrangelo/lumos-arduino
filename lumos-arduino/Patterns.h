#ifndef _PATTERNS_H_
#define _PATTERNS_H_

#include "defs.h"
#include "Patterns.h"

class Patterns {
  public:
           void applyPixels(Pixels pixels, int firstPixel, int lastPixel);
    inline void applyPixels(Pixels pixels) { applyPixels(pixels, 0, strip.numPixels()); }
           void addPatterns(Pixels out, int firstPixel, int lastPixel, Pixels p1, Pixels p2);
    inline void addPatterns(Pixels out, Pixels p1, Pixels p2) { addPatterns(out, 0, strip.numPixels(), p1, p2); }
           void blendPatterns(Pixels out, int firstPixel, int lastPixel, Pixels p1, Pixels p2, int ratio);
    inline void blendPatterns(Pixels out, Pixels p1, Pixels p2, int ratio) { blendPatterns(out, 0, strip.numPixels(), p1, p2, ratio); }
           void reversePattern(Pixels out, Pixels in, int firstPixel, int lastPixel);
    inline void reversePattern(Pixels out, Pixels in) { reversePattern(out, in, 0, strip.numPixels()); }
           void setSolidColor(Pixels pixels, int firstPixel, int lastPixel, Color color);
    inline void setSolidColor(Pixels pixels, Color color) { setSolidColor(pixels, 0, strip.numPixels(), color); }
           void setGradient(Pixels pixels, int count, ...);
           void setSineWave(Pixels pixels, int firstPixel, int lastPixel, Color c1, Color c2, int period, int phase);
    inline void setSineWave(Pixels pixels, Color c1, Color c2, int period, int phase) { setSineWave(pixels, 0, strip.numPixels(), c1, c2, period, phase); }
};

#endif // _PATTERNS_H_

