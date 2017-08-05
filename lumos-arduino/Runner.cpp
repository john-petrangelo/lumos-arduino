#include "Runner.h"

void Runner::runForever(Action *action) {
  while (1) {
    action->loop();
  }
}

void Runner::runForDurationMS(long durationMS, Action *action) {
  long endTime = millis() + durationMS;
  while (millis() < endTime) {
    action->loop();
  }
}

void Runner::runUntilDone(Effect *effect) {
  while (!effect->isDone()) {
    effect->loop();
  }
}

