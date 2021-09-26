#include "defs.h"

#include "Action.h"
void Action::loop() {
  if (!isDone() && millis() > getNextUpdateMS()) {
    update();
//    strip.show();
  }
}

String Action::describe() {
  String msg = "ACTION\r\nName: ";
  msg += name;
  msg += "\r\nNext update: ";
  msg += getNextUpdateMS();
  msg += "ms\r\n";

  return msg;
}
