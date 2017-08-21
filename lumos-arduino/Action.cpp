#include "defs.h"

#include "Action.h"
#include "Colors.h"
#include "Log.h"
#include "Patterns.h"

void Action::loop() {
  if (millis() > getNextUpdateMS()) {
    update();
    strip.show();
  }
}

Blink::Blink(Pixels pixels, int periodMS, int firstPixel, int lastPixel, Color c1, Color c2)
  : Action(firstPixel, lastPixel), pixels(pixels), periodMS(periodMS)
{
  this->colors[0] = c1;
  this->colors[1] = c2;
}

void Blink::reset() {
  setNextUpdateMS(millis() + periodMS / 2);
  colorIndex = 0;
  update();
}

void Blink::update() {
  colorIndex = (colorIndex + 1) % 2;
  Patterns::setSolidColor(pixels, firstPixel, lastPixel, colors[colorIndex]);
  Patterns::applyPixels(pixels, firstPixel, lastPixel);
  setNextUpdateMS(millis() + periodMS / 2);
}

void Flicker::reset() {
  setNextUpdateMS(0);
}

void Flicker::update() {
  Color const nowColor = Colors::fade(color, random(20, 101));
  for (int i = firstPixel; i < lastPixel; i++) {
    strip.setPixelColor(i, nowColor);
  }

  // Randomize the sleep time a bit.
  setNextUpdateMS(millis() + 60 + random(0, 40));
}

void Noise::reset() {
  setNextUpdateMS(0);
}

void Noise::update() {
  Color const nowColor = Colors::fade(color, random(20, 101));
  for (int i = firstPixel; i < lastPixel; i++) {
    strip.setPixelColor(i, Colors::fade(color, random(25, 150)));
  }

  setNextUpdateMS(millis() + 30);
}

void Rotate::update() {
  Color firstColor = strip.getPixelColor(firstPixel);
  Color lastColor = strip.getPixelColor(lastPixel - 1);
  switch (op) {
    case  COUNTER_CLOCKWISE:
      for (int i = firstPixel; i < lastPixel - 1; i++) {
        strip.setPixelColor(i, strip.getPixelColor(i + 1));
      }
      strip.setPixelColor(lastPixel - 1, firstColor);
      break;
    case CLOCKWISE:
      for (int i = lastPixel - 1; i >= firstPixel; i--) {
        strip.setPixelColor(i, strip.getPixelColor(i - 1));
      }
      strip.setPixelColor(firstPixel, lastColor);
      break;
  }

  setNextUpdateMS(millis() + 1000.0 / pixelsPerSecond);
}

void Flame::update() {
  int const delayMS = 120;

  // Paint the background all black.
  Patterns::setSolidColor(pixels, firstPixel, lastPixel, BLACK);
  Patterns::applyPixels(pixels, firstPixel, lastPixel);

  int const range = lastPixel - firstPixel;
  int const myFirstPixel = firstPixel + random(0, range / 5);
  int const myLastPixel = lastPixel - random(0, range / 5);
  Color const FIRE_RED = Colors::blend(RED, YELLOW, 10);
  Color const FIRE_RED2 = Colors::blend(RED, YELLOW, 20);
  Patterns::setGradient(pixels, myFirstPixel, myLastPixel, 7, BLACK, FIRE_RED, FIRE_RED2, ORANGE, FIRE_RED2, FIRE_RED, BLACK);
  Patterns::applyPixels(pixels, myFirstPixel, myLastPixel);

  setNextUpdateMS(millis() + 110);
}

