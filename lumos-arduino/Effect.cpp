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

FadeTo::FadeTo(Pixels pixels, int durationMS, int firstPixel, int lastPixel, Color c)
    : pixels(pixels), durationMS(durationMS), firstPixel(firstPixel), lastPixel(lastPixel), newColor(c) {
  long adjustedDurationMS = constrain(durationMS - 131, TIME_STEP_MS, 32767);
  updateIntervalMS = adjustedDurationMS / 100;
}

void FadeTo::reset() {
  for (int i = 0; i < strip.numPixels(); i++) {
    pixels[i] = strip.getPixelColor(i);
  }
  setNextUpdateMS(millis() + updateIntervalMS);
}

void FadeTo::update() {
  Log::logLn();
  for (int pixel = firstPixel; pixel < lastPixel; pixel++) {
    Color stepColor = Colors::blend(pixels[pixel], newColor, currentPercent);
    strip.setPixelColor(pixel, stepColor);
  }

  currentPercent++;
  setNextUpdateMS(millis() + updateIntervalMS);
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
  Runner::runForDurationMS(updateIntervalMS, &flicker);
  strip.setPixelColor(currentPixel, BLACK);
  currentPixel--;
  setNextUpdateMS(millis() + 1000 / pixelsPerSecond);
}

GrowLeft::GrowLeft(int pixelsPerSecond, int firstPixel, int lastPixel, Color color)
    : pixelsPerSecond(pixelsPerSecond), firstPixel(firstPixel), lastPixel(lastPixel), color(color)
{ }

void GrowLeft::reset() {
  currentPixel = 0;
  setNextUpdateMS(millis() + 1000 / pixelsPerSecond);
}

void GrowLeft::update() {
  strip.setPixelColor(currentPixel, color);
  currentPixel++;
  setNextUpdateMS(millis() + 1000 / pixelsPerSecond);
}

void DelayedStart::reset() {
  isStarted = false;
  effect->reset();
  setNextUpdateMS(millis() + delayMS);
}

void DualAction::reset() {
  effect1->reset();
  effect2->reset();
}

void DualAction::loop() {
  // TODO Can be modified to only strip.show() once after all actions loop.
  effect1->loop();
  effect2->loop();
}

bool DualAction::isDone() {
  return effect1->isDone() && effect2->isDone();
}

void TripleAction::reset() {
  effect1->reset();
  effect2->reset();
  effect3->reset();
}

void TripleAction::loop() {
  // TODO Can be modified to only strip.show() once after all actions loop.
  effect1->loop();
  effect2->loop();
  effect3->loop();
}

bool TripleAction::isDone() {
  return effect1->isDone() && effect2->isDone() && effect3->isDone();
}

