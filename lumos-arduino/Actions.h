#ifndef _ACTIONS_H_
#define _ACTIONS_H_

#include "Action.h"
#include "Colors.h"
#include "Patterns.h"

class ActionGroup : public Action {
  private:
    static int const MAX_ACTIONS = 5;
    Action *actions[MAX_ACTIONS];
    int const numActions;

  public:
    ActionGroup(Adafruit_NeoPixel &strip, int count, ...);
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
    Blink(Adafruit_NeoPixel &strip, Pixels pixels, int periodMS, int firstPixel, int lastPixel, Color c1, Color c2);
    void reset();
};

class DelayedStart : public Action {
  private:
    long delayMS;
    Action *action;
    bool isStarted;

  public:
    DelayedStart(Adafruit_NeoPixel &strip, long delayMS, Action *action) : Action(strip), delayMS(delayMS), action(action) { }
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
    FadeTo(Adafruit_NeoPixel &strip, Pixels pixels, long durationMS, int firstPixel, int lastPixel, Color c);
    FadeTo(Adafruit_NeoPixel &strip, Pixels pixels, long durationMS, Color c) : FadeTo(strip, pixels, durationMS, 0, strip.numPixels(), c) { }
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
    Flame(Adafruit_NeoPixel &strip, Pixels pixels, int firstPixel, int lastPixel) : Action(strip, firstPixel, lastPixel), pixels(pixels) { }
    Flame(Adafruit_NeoPixel &strip, Pixels pixels) : Flame(strip, pixels, 0, strip.numPixels()) { }
    void reset() { name = "Flame"; }
    void update();
};

class Flicker : public Action {
  private:
    Color color;

  public:
    Flicker(Adafruit_NeoPixel &strip, int firstPixel, int lastPixel, Color color) : Action(strip, firstPixel, lastPixel), color(color) { }
    Flicker(Adafruit_NeoPixel &strip, int pixel, Color color) : Flicker(strip, pixel, pixel + 1, color) { }
    Flicker(Adafruit_NeoPixel &strip, Color color) : Flicker(strip, 0, strip.numPixels(), color) { }
    void reset();
    void update();
};

class Fuse : public Action {
  private:
    int const pixelsPerSecond;
    Color const fuseColor;
    Color const burnColor;
    int currentPixel;

  public:
    Fuse(Adafruit_NeoPixel &strip, int pixelsPerSecond) : Fuse(strip, pixelsPerSecond, 0, strip.numPixels(), Colors::fade(WHITE, 3), ORANGE) { }
    Fuse(Adafruit_NeoPixel &strip, int pixelsPerSecond, Color fuseColor, Color burnColor) : Fuse(strip, pixelsPerSecond, 0, strip.numPixels(), fuseColor, burnColor) { }
    Fuse(Adafruit_NeoPixel &strip, int pixelsPerSecond, int firstPixel, int lastPixel, Color fuseColor, Color burnColor);
    void reset();
    void update();
    bool isDone() { return currentPixel < firstPixel; }
};

class Grow : public Action {
  private:
    int pixelsPerSecond;
    Color color;
    int currentPixel;

  public:
    Grow(Adafruit_NeoPixel &strip, int pixelsPerSecond, Color color) : Grow(strip, pixelsPerSecond, 0, strip.numPixels(), color) { }
    Grow(Adafruit_NeoPixel &strip, int pixelsPerSecond, int firstPixel, int lastPixel, Color color);
    void reset();
    void update();
    bool isDone() { return currentPixel >= lastPixel; }
};

class Lightning : public Action {
  private:
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
    Lightning(Adafruit_NeoPixel &strip, Color color) : Lightning(strip, 0, strip.numPixels(), color) { }
    Lightning(Adafruit_NeoPixel &strip, int firstPixel, int lastPixel, Color color);
    void reset();
    void update();
    bool isDone() { return index >= sizeof(patternMS)/sizeof(long); }
};

class Noise : public Action {
  private:
    Color color;

  public:
    Noise(Adafruit_NeoPixel &strip, int firstPixel, int lastPixel, Color color) : Action(strip, firstPixel, lastPixel), color(color) { }
    Noise(Adafruit_NeoPixel &strip, Color color) : Noise(strip, 0, strip.numPixels(), color) { }
    Noise(Adafruit_NeoPixel &strip) : Noise(strip, 0, strip.numPixels(), WHITE) { }
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
    Rotate(Adafruit_NeoPixel &strip, int pixelsPerSecond, Direction op) : Rotate(strip, 0, strip.numPixels(), pixelsPerSecond, op) { }
    Rotate(Adafruit_NeoPixel &strip, int firstPixel, int lastPixel, int pixelsPerSecond, Direction op)
        : Action(strip, firstPixel, lastPixel), pixelsPerSecond(pixelsPerSecond), op(op) { }
    void reset() { }
    void update();

    void setPixelsPerSecond(int pixelsPerSecond) { this->pixelsPerSecond = pixelsPerSecond; }
    void setDirection(Direction op) { this->op = op; }
};

#endif // _ACTIONS_H_
