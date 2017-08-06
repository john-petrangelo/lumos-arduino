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
{
  updateIntervalMS = 1000 / pixelsPerSecond;
}

void Fuse::reset() {
  // Initialize the length to fuseColor.
  for (int i = firstPixel; i < lastPixel - 1; i++) {
    strip.setPixelColor(i, fuseColor);
  }
  strip.show();

  currentPixel = lastPixel - 1;
  setNextUpdateMS(millis() + updateIntervalMS);
}

void Fuse::update() {
  Flicker flicker(currentPixel, burnColor);
  Runner::runForDurationMS(updateIntervalMS, &flicker);
  strip.setPixelColor(currentPixel, BLACK);
  currentPixel--;
  setNextUpdateMS(millis() + updateIntervalMS);
}

