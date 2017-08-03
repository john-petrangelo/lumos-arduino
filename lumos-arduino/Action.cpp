#include "defs.h"

#include "Action.h"
#include "Patterns.h"

ActionRunner::ActionRunner(Action *action) {
  this->action = action;
}

void ActionRunner::runForever() {
  while (1) {
    action->loop();
  }
}

void ActionRunner::runForDurationMS(long durationMS) {
  long endTime = millis() + durationMS;
  while (millis() < endTime) {
    action->loop();
  }
}

Blink::Blink(Pixels pixels, int periodMS, int firstPixel, int lastPixel, Color c1, Color c2)
  : pixels(pixels), periodMS(periodMS), firstPixel(firstPixel), lastPixel(lastPixel)
{
  this->colors[0] = c1;
  this->colors[1] = c2;
}

void Blink::setup() {
  nextBlinkTimeMS = millis() + periodMS / 2;
  colorIndex = 0;
  paint();
}

void Blink::loop() {
  if (millis() > nextBlinkTimeMS) {
    colorIndex = (colorIndex + 1) % 2;
    paint();
    nextBlinkTimeMS = millis() + periodMS / 2;
  }
}

void Blink::paint() {
  Patterns::setSolidColor(pixels, firstPixel, lastPixel, colors[colorIndex]);
  Patterns::applyPixels(pixels, firstPixel, lastPixel);
  strip.show();
}


