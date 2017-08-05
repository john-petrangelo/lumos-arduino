#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "Action.h"
#include "Colors.h"

class Effect : public Action {
  public:
    virtual bool isDone() = 0;
};

/* Fades from the current colors to the specified color. */
class FadeTo : public Effect {
  private:
    Pixels const pixels;
    long const durationMS;
    int const firstPixel;
    int const lastPixel;
    Color const newColor;
    long updateIntervalMS;
    long currentPercent = 0;
    
  public:
    FadeTo(Pixels pixels, int durationMS, int firstPixel, int lastPixel, Color c);
    FadeTo(Pixels pixels, int durationMS, Color c) : FadeTo(pixels, durationMS, 0, strip.numPixels(), c) { }
    void setup();
    void loop();
    bool isDone() { return currentPercent >100; }
};

#endif // _EFFECT_H_

