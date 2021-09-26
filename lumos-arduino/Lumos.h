#pragma once

#include "Arduino.h"
#include "Action.h"

// Lumos manages a singel Neopixel series.
class Lumos {
  private:
    neoPixelType const STRIP_FLAGS = (NEO_GRB + NEO_KHZ800);
    int8_t const pin;
    Adafruit_NeoPixel strip;
    
    static const long FOREVER = 0;
    
    Action *action = NULL;
    long endTimeMS = 0;

  public:
    Lumos(uint16_t num_pixels, int8_t pin);
    
    void runForever(Action *action);
    void runForDurationMS(long durationMS, Action *action);

    void loop();
    String describe();
};
