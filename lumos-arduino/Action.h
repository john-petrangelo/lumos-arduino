#include "Patterns.h"

// A generic superclass for actions.
// Actions need to be setup once then need loop() to be called periodically to update the strip.
// Actions have no inherent "done" state -- things that finish are called "effects."
class Action {
  public:
    virtual void loop() {}
};

// ActionRunner provides convenience methods for running Actions.
class ActionRunner {
  private:
    Action *action;
  
  public:
    ActionRunner(Action *action);
    void setAction(Action *action) { this->action = action; }
    void runForever();
    void runForDurationMS(long durationMS);
};

// An Action that alternates between two colors with the given period.
class Blink : public Action {
  private:
    Pixels const pixels;
    int const periodMS;
    int const firstPixel;
    int const lastPixel;
    Color colors[2];
    long nextUpdateMS;
    int colorIndex;

  public:
    Blink(Pixels pixels, int periodMS, int firstPixel, int lastPixel, Color c1, Color c2);
    void setup();
    void loop();

  private:
    void paint();
};

// An action that rotates or shifts lights to the left or right.
class Rotate : public Action {
  private:
    int const pixelsPerSecond;
    Direction const op;
    long nextUpdateMS;
    
  public:
    Rotate(int pixelsPerSecond, Direction op);
    void setup();
    void loop();
    void rotate();
};

// DualAction
class DualAction : public Action {
  Action * const action1;
  Action * const action2;
  public:
    DualAction(Action *a1, Action *a2);
    void setup();
    void loop();
};

// TripleAction
class TripleAction : public Action {
  Action * const action1;
  Action * const action2;
  Action * const action3;
  public:
    TripleAction(Action *a1, Action *a2, Action *a3);
    void setup();
    void loop();
};

