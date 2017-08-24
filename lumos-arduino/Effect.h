#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "Action.h"
#include "Colors.h"
#include "Log.h"

class Effect : public Action {
  public:
    Effect(int firstPixel, int lastPixel) : Action(firstPixel, lastPixel) { }
    Effect() : Action() { }
  
    void loop();
    virtual bool isDone() = 0;
};

/* Fades from the current colors to the specified color. */
class FadeTo : public Effect {
  private:
    Pixels const pixels;
    long durationMS;
    int firstPixel;
    int lastPixel;
    Color newColor;
    long currentPercent = 0;
    
  public:
    FadeTo(Pixels pixels, long durationMS, int firstPixel, int lastPixel, Color c);
    FadeTo(Pixels pixels, long durationMS, Color c) : FadeTo(pixels, durationMS, 0, strip.numPixels(), c) { }
    void reset();
    void update();
    bool isDone() { return currentPercent > 100; }

    void setDurationMS(long durationMS) { this->durationMS = durationMS; }
    void setColor(Color newColor) { this->newColor = newColor; }
};

class Fuse : public Effect {
  private:
    int const pixelsPerSecond;
    int const firstPixel;
    int const lastPixel;
    Color const fuseColor;
    Color const burnColor;
    int currentPixel;

  public:
    Fuse(int pixelsPerSecond) : Fuse(pixelsPerSecond, 0, strip.numPixels(), Colors::fade(WHITE, 3), ORANGE) { }
    Fuse(int pixelsPerSecond, Color fuseColor, Color burnColor) : Fuse(pixelsPerSecond, 0, strip.numPixels(), fuseColor, burnColor) { }
    Fuse(int pixelsPerSecond, int firstPixel, int lastPixel, Color fuseColor, Color burnColor);
    void reset();
    void update();
    bool isDone() { return currentPixel < firstPixel; }
};

class Grow : public Effect {
  private:
    int pixelsPerSecond;
    int const firstPixel;
    int const lastPixel;
    Color color;
    int currentPixel;

  public:
    Grow(int pixelsPerSecond, Color color) : Grow(pixelsPerSecond, 0, strip.numPixels(), color) { }
    Grow(int pixelsPerSecond, int firstPixel, int lastPixel, Color color);
    void reset();
    void update();
    bool isDone() { return currentPixel >= lastPixel; }
};

class Lightning : public Effect {
  private:
    int const firstPixel;
    int const lastPixel;
    Color const color;
    long patternMS[6] = {
      400, /*on*/
      300, /*off*/
      200, /*on*/
      175, /*off*/
      150,  /*on*/
      0 /* final off */
    };
    int index;
    bool pixelsOn;

  public:
    Lightning(Color color) : Lightning(0, strip.numPixels(), color) { }
    Lightning(int firstPixel, int lastPixel, Color color);
    void reset();
    void update();
    bool isDone() { return index >= sizeof(patternMS)/sizeof(long); }
};

class NullEffect : public Effect {
  public:
    void reset() { }
    void update() { }
    bool isDone() { return true; }
};

class DelayedStart : public Effect {
  private:
    long delayMS;
    Effect *effect;
    bool isStarted;

  public:
    DelayedStart(long delayMS, Effect *effect) : delayMS(delayMS), effect(effect) { }
    void reset();
    void update() { isStarted = true; effect->update(); }
    long getNextUpdateMS() { return isStarted ? effect->getNextUpdateMS() : nextUpdateMS; }
    bool isDone() { return isStarted && effect->isDone(); }
};

class EffectGroup : public Effect {
  private:
    static int const MAX_EFFECTS = 5;
    Effect *effects[MAX_EFFECTS];
    int numEffects;

  public:
    EffectGroup(int count, ...);
    void reset();
    void loop();
    void update() { }
    bool isDone();

    void clear();
    void add(Effect *effect);
};

#endif // _EFFECT_H_

