#ifndef _RUNNER_
#define _RUNNER_

#include "Action.h"
#include "Effect.h"

// Runner provides convenience methods for running Actions and EFfects.
class Runner {
  public:
    Runner() { }
    void runForever(Action *action);
    void runForDurationMS(long durationMS, Action *action);
    void runUntilDone(Effect *effect);
};

#endif // _RUNNER_

