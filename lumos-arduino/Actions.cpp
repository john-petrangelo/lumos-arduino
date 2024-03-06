#include "Actions.h"
#include "Colors.h"

/***** ACTIONGROUP *****/

ActionGroup::ActionGroup(Adafruit_NeoPixel &strip, int count, ...) : Action(strip, 0, strip.numPixels()), numActions(min(count, MAX_ACTIONS)) {
  // Declare a va_list macro and initialize it with va_start.
  va_list argList;
  va_start(argList, count);

  // Copy all of the input Actions.
  int i = 0;
  while (count-- > 0) {
    actions[i++] = va_arg(argList, Action*);
  }
}

void ActionGroup::reset() {
  for (int i = 0; i < numActions; i++) {
    actions[i]->reset();
  }
}

void ActionGroup::loop() {
  // TODO Can be modified to only strip.show() once after all actions loop.
  for (int i = 0; i < numActions; i++) {
    actions[i]->loop();
  }
}

bool ActionGroup::isDone() {
  for (int i = 0; i < numActions; i++) {
    if (!actions[i]->isDone()) {
      return false;
    }
  }

  return true;
}
/***** BLINK *****/

Blink::Blink(Adafruit_NeoPixel &strip, Pixels pixels, int periodMS, int firstPixel, int lastPixel, Color c1, Color c2)
  : Action(strip, firstPixel, lastPixel), pixels(pixels), periodMS(periodMS)
{
  this->colors[0] = c1;
  this->colors[1] = c2;
}

void Blink::reset() {
  setNextUpdateMS(millis() + periodMS / 2);
  colorIndex = 0;
  update();
}

// TODO
//void Blink::update() {
//  colorIndex = (colorIndex + 1) % 2;
//  Patterns::setSolidColor(pixels, firstPixel, lastPixel, colors[colorIndex]);
//  Patterns::applyPixels(strip, pixels, firstPixel, lastPixel);
//  setNextUpdateMS(millis() + periodMS / 2);
//}

/***** DELAYEDSTART *****/

void DelayedStart::reset() {
  isStarted = false;
  action->reset();
  setNextUpdateMS(millis() + delayMS);
}

/***** FADETO *****/

FadeTo::FadeTo(Adafruit_NeoPixel &strip, Pixels pixels, long durationMS, int firstPixel, int lastPixel, Color c)
    : Action(strip, firstPixel, lastPixel), pixels(pixels), durationMS(durationMS), newColor(c) { }

void FadeTo::reset() {
  for (int i = firstPixel; i < lastPixel; i++) {
    pixels[i] = strip.getPixelColor(i);
  }
  currentPercent = 0;
  setNextUpdateMS(millis() + durationMS / 100);
}

void FadeTo::update() {
  currentPercent += 1 + (millis() - getNextUpdateMS()) / (durationMS / 100.0);
  int clippedPercent = min(100, currentPercent);
  
  for (int pixel = firstPixel; pixel < lastPixel; pixel++) {
    Color stepColor = Colors::blend(pixels[pixel], newColor, clippedPercent);
    strip.setPixelColor(pixel, stepColor);
  }

  setNextUpdateMS(millis() + durationMS / 100);
}

/***** FLAME *****/

void Flame::update() {
  int const delayMS = 120;

  // Paint the background all black.
  Patterns::setSolidColor(pixels, firstPixel, lastPixel, BLACK);

  // TODO
  // Patterns::applyPixels(strip, pixels, firstPixel, lastPixel);

  int const range = lastPixel - firstPixel;
  int const myFirstPixel = firstPixel + random(0, range / 5);
  int const myLastPixel = lastPixel - random(0, range / 5);
  Color const FIRE_RED = Colors::blend(RED, YELLOW, 10);
  Color const FIRE_RED2 = Colors::blend(RED, YELLOW, 20);
  Patterns::setGradient(pixels, myFirstPixel, myLastPixel, 7, BLACK, FIRE_RED, FIRE_RED2, ORANGE, FIRE_RED2, FIRE_RED, BLACK);

  // TODO
  // Patterns::applyPixels(strip, pixels, myFirstPixel, myLastPixel);

  setNextUpdateMS(millis() + 110);
}

/***** FLICKER *****/

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

/***** FUSE *****/

Fuse::Fuse(Adafruit_NeoPixel &strip, int pixelsPerSecond, int firstPixel, int lastPixel, Color fuseColor, Color burnColor)
    : Action(strip, firstPixel, lastPixel), pixelsPerSecond(pixelsPerSecond), fuseColor(fuseColor), burnColor(burnColor)
{ }

void Fuse::reset() {
  // Initialize the length to fuseColor.TIME
  for (int i = firstPixel; i < lastPixel - 1; i++) {
    strip.setPixelColor(i, fuseColor);
  }
  strip.show();

  currentPixel = lastPixel - 1;
  setNextUpdateMS(millis() + 1000 / pixelsPerSecond);
}

void Fuse::update() {
  Flicker flicker(strip, currentPixel, burnColor);
  // TODO Need to do make the flicker happen without blocking.
  // Runner::runForDurationMS(1000 / pixelsPerSecond, &flicker);
  strip.setPixelColor(currentPixel, BLACK);
  currentPixel--;
  setNextUpdateMS(millis());
}

/***** GROW *****/

Grow::Grow(Adafruit_NeoPixel &strip, int pixelsPerSecond, int firstPixel, int lastPixel, Color color)
    : Action(strip, firstPixel, lastPixel), pixelsPerSecond(pixelsPerSecond), color(color)
{ }

void Grow::reset() {
  currentPixel = 0;
  setNextUpdateMS(millis() + 1000 / pixelsPerSecond);
}

void Grow::update() {
  strip.setPixelColor(currentPixel, color);
  currentPixel++;
  setNextUpdateMS(millis() + 1000 / pixelsPerSecond);
}

/***** LIGHTNING *****/

Lightning::Lightning(Adafruit_NeoPixel &strip, int firstPixel, int lastPixel, Color color)
    : Action(strip, firstPixel, lastPixel), color(color) { }

void Lightning::reset() {
  index = 0;
  for (int i = firstPixel; i < lastPixel; i++) {
    strip.setPixelColor(i, BLACK);
  }
  strip.show();
  pixelsOn = false;
  setNextUpdateMS(millis());
}

void Lightning::update() {
  Color newColor = pixelsOn ? BLACK : color;
  for (int i = firstPixel; i < lastPixel; i++) {
    strip.setPixelColor(i, newColor);
  }
  pixelsOn = !pixelsOn;

  setNextUpdateMS(millis() + patternMS[index++]);
}

//    long patternMS[5] = {
//      1000, /*on*/
//      1000, /*off*/
//      1000, /*on*/
//      1000, /*off*/
//      1000  /*on*/

//    };

// bool isDone() { return index >= sizeof(patternMS)/sizeof(long); }

/***** NOISE *****/

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

/***** ROTATE *****/

void Rotate::update() {
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
