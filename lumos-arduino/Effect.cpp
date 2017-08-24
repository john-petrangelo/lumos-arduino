#include "Colors.h"
#include "Effect.h"
#include "Log.h"
#include "Runner.h"

long const TIME_STEP_MS = 30;

void Effect::loop() {
  if (!isDone() && millis() > getNextUpdateMS()) {
    update();
    strip.show();
  }
}

FadeTo::FadeTo(Pixels pixels, long durationMS, int firstPixel, int lastPixel, Color c)
    : pixels(pixels), durationMS(durationMS), firstPixel(firstPixel), lastPixel(lastPixel), newColor(c) { }

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

Fuse::Fuse(int pixelsPerSecond, int firstPixel, int lastPixel, Color fuseColor, Color burnColor)
    : pixelsPerSecond(pixelsPerSecond), firstPixel(firstPixel), lastPixel(lastPixel), fuseColor(fuseColor), burnColor(burnColor)
{ }

void Fuse::reset() {
  // Initialize the length to fuseColor.
  for (int i = firstPixel; i < lastPixel - 1; i++) {
    strip.setPixelColor(i, fuseColor);
  }
  strip.show();

  currentPixel = lastPixel - 1;
  setNextUpdateMS(millis() + 1000 / pixelsPerSecond);
}

void Fuse::update() {
  Flicker flicker(currentPixel, burnColor);
  Runner::runForDurationMS(1000 / pixelsPerSecond, &flicker);
  strip.setPixelColor(currentPixel, BLACK);
  currentPixel--;
  setNextUpdateMS(millis());
}

Lightning::Lightning(int firstPixel, int lastPixel, Color color)
    : firstPixel(firstPixel), lastPixel(lastPixel), color(color) { }

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

Grow::Grow(int pixelsPerSecond, int firstPixel, int lastPixel, Color color)
    : pixelsPerSecond(pixelsPerSecond), firstPixel(firstPixel), lastPixel(lastPixel), color(color)
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

void DelayedStart::reset() {
  isStarted = false;
  effect->reset();
  setNextUpdateMS(millis() + delayMS);
}

EffectGroup::EffectGroup(int count, ...) : Effect(0, strip.numPixels()), numEffects(min(count, MAX_EFFECTS)) {
  // Declare a va_list macro and initialize it with va_start.
  va_list argList;
  va_start(argList, count);

  // Copy all of the input Effects.
  int i = 0;
  while (count-- > 0) {
    effects[i++] = va_arg(argList, Effect*);
  }
}

void EffectGroup::reset() {
  for (int i = 0; i < numEffects; i++) {
    effects[i]->reset();
  }
}

void EffectGroup::loop() {
  // TODO Can be modified to only strip.show() once after all actions loop.
  for (int i = 0; i < numEffects; i++) {
    effects[i]->loop();
  }
}

bool EffectGroup::isDone() {
  for (int i = 0; i < numEffects; i++) {
    if (!effects[i]->isDone()) {
      return false;
    }
  }

  return true;
}

void EffectGroup::clear() {
  numEffects = 0;
}

void EffectGroup::add(Effect *effect) {
  if (numEffects >= MAX_EFFECTS) {
    return;
  }

  effects[numEffects++] = effect;
}

