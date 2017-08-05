#include "Colors.h"
#include "Effects.h"
#include "Log.h"
#include "Runner.h"

void Effects::fuse(int durationMS, Color fuseColor, Color burnColor) { fuse(durationMS, fuseColor, burnColor, strip.numPixels()); }
void Effects::fuse(int durationMS, Color fuseColor, Color burnColor, int length) {
  // Initialize the length to fuseColor.
  for (int i = 0; i < length; i++) {
    strip.setPixelColor(i, fuseColor);
  }

  int stepDuration = durationMS / length;
  int currentPixel = length;
  while (currentPixel-- > 0) {
    Flicker flicker(currentPixel, burnColor);
    Runner runner;
    runner.runForDurationMS(stepDuration, &flicker);
    strip.setPixelColor(currentPixel, BLACK);
  }
  strip.show();
}


