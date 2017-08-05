#include "defs.h"

#include "Action.h"
#include "Colors.h"
#include "Log.h"
#include "Patterns.h"

void Action::loop() {
  if (millis() > getNextUpdateMS()) {
    paint();
    strip.show();
  }
}

Blink::Blink(Pixels pixels, int periodMS, int firstPixel, int lastPixel, Color c1, Color c2)
  : pixels(pixels), periodMS(periodMS), firstPixel(firstPixel), lastPixel(lastPixel)
{
  this->colors[0] = c1;
  this->colors[1] = c2;
}

void Blink::setup() {
  setNextUpdateMS(millis() + periodMS / 2);
  colorIndex = 0;
  paint();
}

void Blink::paint() {
  colorIndex = (colorIndex + 1) % 2;
  Patterns::setSolidColor(pixels, firstPixel, lastPixel, colors[colorIndex]);
  Patterns::applyPixels(pixels, firstPixel, lastPixel);
  setNextUpdateMS(millis() + periodMS / 2);
}

void Flicker::setup() {
  setNextUpdateMS(100);
}

void Flicker::paint() {
  Color const nowColor = Colors::fade(color, random(20, 101));
  for (int i = firstPixel; i < lastPixel; i++) {
    strip.setPixelColor(i, nowColor);
  }

  // Randomize the sleep time a bit.
  setNextUpdateMS(millis() + 60 + random(0, 40));
}

void Rotate::paint() {
  Color firstColor = strip.getPixelColor(firstPixel);
  Color lastColor = strip.getPixelColor(lastPixel - 1);
  switch (op) {
    case  LEFT:
      for (int i = firstPixel; i < lastPixel - 1; i++) {
        strip.setPixelColor(i, strip.getPixelColor(i + 1));
      }
      strip.setPixelColor(lastPixel - 1, firstColor);
      break;
    case RIGHT:
      for (int i = lastPixel - 1; i >= firstPixel; i--) {
        strip.setPixelColor(i, strip.getPixelColor(i - 1));
      }
      strip.setPixelColor(firstPixel, lastColor);
      break;
  }

  setNextUpdateMS(millis() + 1000.0 / pixelsPerSecond);
}

void DualAction::loop() {
  // TODO Can be modified to only strip.show() once after all actions loop.
  action1->loop();
  action2->loop();
}

void TripleAction::loop() {
  // TODO Can be modified to only strip.show() once after all actions loop.
  action1->loop();
  action2->loop();
  action3->loop();
}

