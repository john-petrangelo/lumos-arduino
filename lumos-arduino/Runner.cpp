#include "Runner.h"
#include "Log.h"

void Runner::runForever(Action *action) {
  action->reset();
  while (1) {
    action->loop();
  }
}

void Runner::runForDurationMS(long durationMS, Action *action) {
  action->reset();
  long endTime = millis() + durationMS;
  while (millis() < endTime) {
    action->loop();
  }
}

void Runner::runUntilDone(Effect *effect) {
  effect->reset();
  while (!effect->isDone()) {
    effect->loop();
  }
}

