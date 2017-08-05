#ifndef _RUNNER_
#define _RUNNER_

#include "Action.h"
#include "Effect.h"

// Runner provides convenience methods for running Actions and EFfects.
class Runner {
  private:
    Runner() { }
    
  public:
    static void runForever(Action *action);
    static void runForDurationMS(long durationMS, Action *action);
    static void runUntilDone(Effect *effect);
};

#endif // _RUNNER_

