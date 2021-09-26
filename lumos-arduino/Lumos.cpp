#include "Lumos.h"

Lumos::Lumos(uint16_t num_pixels, int8_t pin) : strip(num_pixels, pin, STRIP_FLAGS), pin(pin) {
  strip.begin();
  strip.setBrightness(255);
  strip.show(); // Initialize all pixels to 'off'
}

void Lumos::loop() {
  if (!action->isDone() && (endTimeMS == FOREVER || millis() < endTimeMS)) {
    action->loop();
  }
  strip.show();
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
