#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "Action.h"
#include "Colors.h"
#include "Log.h"

/* Fades from the current colors to the specified color. */
class FadeTo : public Action {
  private:
    Pixels const pixels;
    long durationMS;
    int firstPixel;
    int lastPixel;
    Color newColor;
    int currentPercent = 0;
    
  public:
    FadeTo(Pixels pixels, long durationMS, int firstPixel, int lastPixel, Color c);
    FadeTo(Pixels pixels, long durationMS, Color c) : FadeTo(pixels, durationMS, 0, strip.numPixels(), c) { }
    void reset();
    void update();
    bool isDone() { return currentPercent > 100; }

    void setDurationMS(long durationMS) { this->durationMS = durationMS; }
    void setColor(Color newColor) { this->newColor = newColor; }
};

class Fuse : public Action {
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

class Grow : public Action {
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

class Lightning : public Action {
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

class NullAction : public Action {
  public:
    void reset() { }
    void update() { }
    bool isDone() { return true; }
};

class DelayedStart : public Action {
  private:
    long delayMS;
    Action *action;
    bool isStarted;

  public:
    DelayedStart(long delayMS, Action *action) : delayMS(delayMS), action(action) { }
    void reset();
    void update() { isStarted = true; action->update(); }
    long getNextUpdateMS() { return isStarted ? action->getNextUpdateMS() : nextUpdateMS; }
    bool isDone() { return isStarted && action->isDone(); }
};

class ActionGroup : public Action {
  private:
    static int const MAX_ACTIONS = 5;
    Action *actions[MAX_ACTIONS];
    int const numActions;

  public:
    ActionGroup(int count, ...);
    void reset();
    void loop();
    void update() { }
    bool isDone();
};

#endif // _EFFECT_H_
