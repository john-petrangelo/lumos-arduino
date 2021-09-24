#include "defs.h"

#include "Action.h"
void Action::loop() {
  if (!isDone() && millis() > getNextUpdateMS()) {
    update();
    strip.show();
  }
}

String Action::describe() {
  String msg = "ACTION\r\nNext update: ";
  msg += getNextUpdateMS();
  msg += "ms\r\nCurrent time: ";
  msg += millis();
  msg += "ms\r\n";
  msg += "Action: <>";

  return msg;
}
