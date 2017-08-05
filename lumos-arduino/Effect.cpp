#include "Colors.h"
#include "Effect.h"
#include "Log.h"

long const TIME_STEP_MS = 30;

FadeTo::FadeTo(Pixels pixels, int durationMS, int firstPixel, int lastPixel, Color c)
    : pixels(pixels), durationMS(durationMS), firstPixel(firstPixel), lastPixel(lastPixel), newColor(c) {
  long adjustedDurationMS = constrain(durationMS - 131, TIME_STEP_MS, 32767);
  updateIntervalMS= adjustedDurationMS / 100;
}

void FadeTo::setup() {
  for (int i = 0; i < strip.numPixels(); i++) {
    pixels[i] = strip.getPixelColor(i);
  }
  setNextUpdateMS(millis() + updateIntervalMS);
}

void FadeTo::loop() {
  if (!isDone() && millis() > nextUpdateMS) {
    for (int pixel = firstPixel; pixel < lastPixel; pixel++) {
      Color stepColor = Colors::blend(pixels[pixel], newColor, currentPercent);
      strip.setPixelColor(pixel, stepColor);
    }

    currentPercent++;
    setNextUpdateMS(millis() + updateIntervalMS);
    strip.show();
  }
}

