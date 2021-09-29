#ifndef _ACTION_H_
#define _ACTION_H_

#include "defs.h"

// A generic base class for actions.
class Action {
  protected:
    long nextUpdateMS = 0;
    int firstPixel;
    int lastPixel;
    Adafruit_NeoPixel &strip;
    
  public:
    const char *name = "";
    Action(Adafruit_NeoPixel &strip, int firstPixel, int lastPixel) : strip(strip), firstPixel(firstPixel), lastPixel(lastPixel) { }
    Action(Adafruit_NeoPixel &strip) : Action(strip, 0, strip.numPixels()) { }
  
    // Runners should call reset once before looping.
    virtual void reset() = 0;
    
    // Update will be called by loop() when its time to make a change to the lights.
    // Implementations should set pixel colors but should not call strip.show().
    // Implementations mmust update nextUpdateMS to indicate when update() should be called again.
    virtual void update() = 0;

    virtual String describe();

    // Actions that reach a done condition of some kind should implement this function to return true
    // when the action is done. Actions that do not have any deterministic done condition can rely on
    // the default implementation which is never done.
    virtual bool isDone() { return false; }

    // Runners should call loop periodically.
    void loop();

    long getNextUpdateMS() { return nextUpdateMS; }
    void setNextUpdateMS(long val) { nextUpdateMS = val; }

    void setRange(int firstPixel, int lastPixel) { this->firstPixel = firstPixel; this->lastPixel = lastPixel; }
    int getFirstPixel() { return firstPixel; }
    int getLastPixel() { return lastPixel; }
};

#endif // _ACTION_H_
