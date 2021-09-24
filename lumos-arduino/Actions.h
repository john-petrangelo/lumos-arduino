#ifndef _ACTIONS_H_
#define _ACTIONS_H_

#include "Action.h"
#include "Colors.h"
#include "Log.h"
#include "Patterns.h"

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

// An Action that alternates between two colors with the given period.
class Blink : public Action {
  private:
    Pixels const pixels;
    int const periodMS;
    Color colors[2];
    int colorIndex;

    void update();

  public:
    Blink(Pixels pixels, int periodMS, int firstPixel, int lastPixel, Color c1, Color c2);
    void reset();
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

// Fades from the current colors to the specified color.
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

class Flame : public Action {
  private:
    Pixels const pixels;

  public:
    Flame(Pixels pixels, int firstPixel, int lastPixel) : Action(firstPixel, lastPixel), pixels(pixels) { }
    Flame(Pixels pixels) : Flame(pixels, 0, strip.numPixels()) { }
    void reset() { }
    void update();
};

class Flicker : public Action {
  private:
    Color color;

  public:
    Flicker(int firstPixel, int lastPixel, Color color) : Action(firstPixel, lastPixel), color(color) { }
    Flicker(int pixel, Color color) : Flicker(pixel, pixel + 1, color) { }
    Flicker(Color color) : Flicker(0, strip.numPixels(), color) { }
    void reset();
    void update();
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

class Noise : public Action {
  private:
    Color color;

  public:
    Noise(int firstPixel, int lastPixel, Color color) : Action(firstPixel, lastPixel), color(color) { }
    Noise(Color color) : Noise(0, strip.numPixels(), color) { }
    Noise() : Noise(0, strip.numPixels(), WHITE) { }
    void reset();
    void update();
};

class NullAction : public Action {
  public:
    void reset() { }
    void update() { }
    bool isDone() { return true; }
};

// An action that rotates or shifts lights to the left or right.
class Rotate : public Action {
  private:
    int pixelsPerSecond;
    Direction op;
    
  public:
    Rotate(int pixelsPerSecond, Direction op) : Rotate(0, strip.numPixels(), pixelsPerSecond, op) { }
    Rotate(int firstPixel, int lastPixel, int pixelsPerSecond, Direction op)
        : Action(firstPixel, lastPixel), pixelsPerSecond(pixelsPerSecond), op(op) { }
    void reset() { }
    void update();

    void setPixelsPerSecond(int pixelsPerSecond) { this->pixelsPerSecond = pixelsPerSecond; }
    void setDirection(Direction op) { this->op = op; }
};

#endif // _ACTIONS_H_
