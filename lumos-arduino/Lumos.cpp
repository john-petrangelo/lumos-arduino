#include "defs.h"
#include "Logger.h"
#include "Lumos.h"

Lumos::Lumos(uint16_t num_pixels, int8_t pin) : strip(num_pixels, pin, STRIP_FLAGS), pin(pin) {
  strip.begin();
  strip.setBrightness(255);
  strip.show(); // Initialize all pixels to 'off'
}

void Lumos::loop() {
  char buffer[256];
  snprintf(buffer, 256, "LUMOS action=%s isDone=%d endTimeMS=%d\n", action->name, action->isDone(), endTimeMS);
  buffer[255] = '\0';
  Logger::logMsg(buffer);
  
  if (!action->isDone() && (endTimeMS == FOREVER || millis() < endTimeMS)) {
    Logger::logf("LUMOS Did loop\n");
    action->loop();
    strip.show();
  } else {
    Logger::logf("LUMOS Did not loop\n");
  }
}

void Lumos::runForever(Action *newAction) {
  action = newAction;
  endTimeMS = FOREVER;
  action->reset(); 
}
  
void Lumos::runForDurationMS(long durationMS, Action *newAction) {
  action = newAction;
  endTimeMS = millis() + durationMS;
  action->reset(); 
}

String Lumos::describe() {
  String msg = "LUMOS\r\nEnd time: ";
  msg += endTimeMS;
  msg += "ms\r\nCurrent time: ";
  msg += millis();
  msg += "ms\r\n";
  msg += action->describe();
  
  return msg;
}
