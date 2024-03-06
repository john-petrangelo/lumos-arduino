#ifndef _RUNNER_
#define _RUNNER_

#include "Arduino.h"
#include "Action.h"

static const long FOREVER = 0;

// Runner provides convenience methods for running Actions and EFfects.
class Runner {
  private:
    Action *action;
    long endTimeMS;

    Runner(Action *action, long durationMS) : action(action), endTimeMS(millis() + durationMS) { action->reset(); }
    Runner(Action *action) : action(action), endTimeMS(FOREVER) { action->reset(); }
    
  public:
    static Runner runForever(Action *action) { return Runner(action); }
    static Runner runForDurationMS(long durationMS, Action *action) { return Runner(action, durationMS); }

    // DEPRECATED
    // Only for use of legacy demo program. Caution: blocks until done.
    // Causes software watchdog timer exceptions on ESP8266.
    static void runUntilDone(Action *action);

    void loop();
    String describe();
};

#endif // _RUNNER_
