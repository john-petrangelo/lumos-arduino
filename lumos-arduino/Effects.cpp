#include "Colors.h"
#include "Effects.h"

void Effects::sparklePixel(int durationMS, int pos, Color color) {
  long stopTime = millis() + durationMS;

  while (millis() < stopTime) {
    Color nowColor = Colors::fade(color, random(20, 101));
    strip.setPixelColor(pos, nowColor);
    strip.show();

    // Randomize the sleep time a bit.
    delay(60 + random(0, 40) /*ms*/);
  }
}

void Effects::fuse(int durationMS, Color fuseColor, Color burnColor) { fuse(durationMS, fuseColor, burnColor, strip.numPixels()); }
void Effects::fuse(int durationMS, Color fuseColor, Color burnColor, int length) {
  // Initialize the length to half brightness.
  for (int i = 0; i < length; i++) {
    strip.setPixelColor(i, fuseColor);
  }

  int stepDuration = durationMS / length;
  int currentPixel = length;
  while (currentPixel-- > 0) {
//    printLong("numTicks", currentPixel);
    sparklePixel(stepDuration, currentPixel, burnColor);
    strip.setPixelColor(currentPixel, BLACK);
  }
  strip.show();
}

//    /**
//     * Sweeps lights like K.I.T.T. from Knight Rider from right to left.
//     * 
//     * @param duration number of seconds to make one sweep
//     * @param glowHistory the glow history to use for this action, may already contain some history from previous action
//     * @param color the color of the swept lights
//     */
//    public void sweepLeft(double duration, GlowHistory glowHistory, Color color) {
//        LOGGER.info("sweepLeft duration={} color={}", duration, color);
//
//        final int numTicks = (int)(duration / TIME_STEP);
//        int prevPos = lightStrip.size() - 1;
//        for (int i = 1; i <= numTicks; i++) {
//            glowHistory.tick();
//
//            // Add the current position to the glow list.
//            final int pos = lightStrip.size() * (numTicks - i) / numTicks - 1;
//            for (int j = prevPos; j > pos; j--) {
//                glowHistory.add(j, color);
//            }
//            prevPos = pos;
//
//            tick();
//        }
//    }
//
//    /**
//     * Sweeps lights like K.I.T.T. from Knight Rider from left to right.
//     * 
//     * @param duration number of seconds to make one sweep
//     * @param glowHistory the glow history to use for this action, may already contain some history from previous action
//     * @param color the color of the swept lights
//     */
//    public void sweepRight(double duration, GlowHistory glowHistory, Color color) {
//        LOGGER.info("sweepLeft duration={} color={}", duration, color);
//
//        final int numTicks = (int)(duration / TIME_STEP);
//        int prevPos = -1;
//        for (int i = 1; i <= numTicks; i++) {
//            glowHistory.tick();
//
//            // Add the current position to the glow list.
//            final int pos = lightStrip.size() * i / numTicks - 1;
//            for (int j = prevPos + 1; j <= pos; j++) {
//                glowHistory.add(j, color);
//            }
//            prevPos = pos;
//
//            tick();
//        }
//    }
//    
//    /**
//     * Plays out the remaining glow history.
//     */
//    public void drainGlowHistory(GlowHistory glowHistory) {
//        LOGGER.info("drainGlowHistory");
//
//        while (!glowHistory.isEmpty()) {
//            glowHistory.tick();
//
//            tick();
//        }
//    }
//    
//    /**
//     * Plays out the remaining glow history.
//     */
//    public void flash(GlowHistory glowHistory, Color color) {
//        LOGGER.info("flash color={}", color);
//
//        // Set the color to all lights on the strip and display them for a single time tick.
//        Patterns patterns = new Patterns(lightStrip.size());
//        List<Color> solid = patterns.solidColor(color);
//        lightStrip.setColors(solid);
//        tick();
//
//        // Add all of the lights to the glow history.
//        for (int i = 0; i < lightStrip.size(); i++) {
//            glowHistory.add(i, color);
//        }
//    }

void Effects::tick() {
  strip.show();
  delay(TIME_STEP_MS);
}

void Effects::tickMicroseconds(float delayTime) {
  strip.show();
  while (delayTime > 16000) {
    delayMicroseconds(16000);
    delayTime -= 16000;
  }
  delayMicroseconds(delayTime);
}


