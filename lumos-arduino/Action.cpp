#include "defs.h"
#include "Logger.h"

#include "Action.h"
void Action::loop() {
  int now = millis();
  Logger::logf("ACTION::LOOP isDone=%d now=%dms nextUpdate=%dms\n", isDone(), now, getNextUpdateMS());
  if (!isDone() && now > getNextUpdateMS()) {
    update();
    strip.show();
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
