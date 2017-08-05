#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "Action.h"
#include "Colors.h"

class Effect : public Action {
  public:
    void loop();
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
    
    void paint();

  public:
    FadeTo(Pixels pixels, int durationMS, int firstPixel, int lastPixel, Color c);
    FadeTo(Pixels pixels, int durationMS, Color c) : FadeTo(pixels, durationMS, 0, strip.numPixels(), c) { }
    void setup();
    bool isDone() { return currentPercent >100; }
};

class Fuse : public Effect {
  private:
    int const pixelsPerSecond;
    int const firstPixel;
    Color const fuseColor;
    Color const burnColor;
    long updateIntervalMS;
    int currentPixel;

    void paint();

  public:
    Fuse(int pixelsPerSecond) : Fuse(pixelsPerSecond, 0, strip.numPixels(), Colors::fade(WHITE, 3), ORANGE) { }
    Fuse(int pixelsPerSecond, Color fuseColor, Color burnColor) : Fuse(pixelsPerSecond, 0, strip.numPixels(), fuseColor, burnColor) { }
    Fuse(int pixelsPerSecond, int firstPixel, int lastPixel, Color fuseColor, Color burnColor);
    void setup();
    bool isDone() { return currentPixel < firstPixel; }
};

#endif // _EFFECT_H_

