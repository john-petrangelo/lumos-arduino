#include "defs.h"

#include "Action.h"
#include "Colors.h"
#include "Log.h"
#include "Patterns.h"

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

void Blink::loop() {
  if (millis() > getNextUpdateMS()) {
    colorIndex = (colorIndex + 1) % 2;
    paint();
    setNextUpdateMS(millis() + periodMS / 2);
  }
}

void Blink::paint() {
  Patterns::setSolidColor(pixels, firstPixel, lastPixel, colors[colorIndex]);
  Patterns::applyPixels(pixels, firstPixel, lastPixel);
  strip.show();
}

void Flicker::setup() {
  setNextUpdateMS(100);
}

void Flicker::loop() {
  if (millis() > getNextUpdateMS()) {
    Color const nowColor = Colors::fade(color, random(20, 101));
    for (int pixel = firstPixel; pixel < lastPixel; pixel++) {
      strip.setPixelColor(pixel, nowColor);
    }
    strip.show();

    // Randomize the sleep time a bit.
    setNextUpdateMS(millis() + 60 + random(0, 40));
  }
}

void Rotate::setup() {
  setNextUpdateMS(millis() + 1000.0 / pixelsPerSecond);
}

void Rotate::loop() {
  if (millis() > getNextUpdateMS()) {
    rotate();
    setNextUpdateMS(millis() + 1000.0 / pixelsPerSecond);
    strip.show();
  }
}

void Rotate::rotate() {
  Color c0 = strip.getPixelColor(0);
  Color c_last = strip.getPixelColor(strip.numPixels() - 1);
  switch (op) {
    case  LEFT:
      for (int i = 0; i < strip.numPixels() - 1; i++) {
        strip.setPixelColor(i, strip.getPixelColor(i + 1));
      }
      strip.setPixelColor(strip.numPixels()-1, c0);
      break;
    case RIGHT:
      for (int i = strip.numPixels() - 1; i > 0; i--) {
        strip.setPixelColor(i, strip.getPixelColor(i - 1));
      }
      strip.setPixelColor(0, c_last);
      break;
  }
}

void DualAction::loop() {
  action1->loop();
  action2->loop();
}

void TripleAction::loop() {
  action1->loop();
  action2->loop();
  action3->loop();
}

