#include "Runner.h"

void Runner::runUntilDone(Action *action) {
  action->reset();
  if (!action->isDone()) {
    action->loop();
  }
}

void Runner::loop() {
  if (endTimeMS == FOREVER || millis() < endTimeMS) {
    action->loop();
  }
}

String Runner::describe() {
  String msg = "RUNNER\r\nEnd time: ";
  msg += endTimeMS;
  msg += "ms\r\nCurrent time: ";
  msg += millis();
  msg += "ms\r\n";
  msg += action->describe();
  
  return msg;
}
