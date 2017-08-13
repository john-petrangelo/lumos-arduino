#ifndef _ACTION_H_
#define _ACTION_H_

#include "Patterns.h"

// A generic superclass for actions.
class Action {
  protected:
    long nextUpdateMS = 0;
    int firstPixel;
    int lastPixel;

  public:
    Action(int firstPixel, int lastPixel) : firstPixel(firstPixel), lastPixel(lastPixel) { }
    Action() : Action(0, strip.numPixels()) { }
  
    // Runners should call reset once before looping.
    virtual void reset() = 0;
    
    // Update will be called by loop() when its time to make a change to the lights.
    // Implementations should set pixel colors but should not call strip.show().
    // Implementations mmust update nextUpdateMS to indicate when update() should be called again.
    virtual void update() = 0;

    // Runners should call loop periodically.
    virtual void loop();

    virtual long getNextUpdateMS() { return nextUpdateMS; }
    void setNextUpdateMS(long val) { nextUpdateMS = val; }

    void setRange(int firstPixel, int lastPixel) { this->firstPixel = firstPixel; this->lastPixel = lastPixel; }
    int getFirstPixel() { return firstPixel; }
    int getLastPixel() { return lastPixel; }
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

class Flame : public Action {
  private:
    Pixels const pixels;

  public:
    Flame(Pixels pixels, int firstPixel, int lastPixel) : Action(firstPixel, lastPixel), pixels(pixels) { }
    Flame(Pixels pixels) : Flame(pixels, 0, strip.numPixels()) { }
    void reset() { }
    void update();
};

#endif // _ACTION_H_
