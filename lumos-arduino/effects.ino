static int TIME_STEP_MS = 30;

/**
 * Rotate lights to the right
 * 
 * @param duration durationMS of the action in milliseconds
 * @param distance the number of light positions to rotate
 */
inline void rotateRight(float durationMS, int pixelsPerSecond) {
  rotateOrShift(ROTATE_RIGHT, durationMS, pixelsPerSecond, BLACK);
}

/**
 * Rotate lights to the left
 * 
 * @param duration durationMS of the action in milliseconds
 * @param distance the number of light positions to rotate
 */
inline void rotateLeft(float durationMS, int pixelsPerSecond) {
  rotateOrShift(ROTATE_LEFT, durationMS, pixelsPerSecond, BLACK);
}

/**
 * Shift lights to the right
 * 
 * @param durationMS duration of the action in milliseconds
 * @param distance the number of light positions to shift
 * @param fillColor color to fill lights shift in from the left
 */
inline void shiftRight(float durationMS, int pixelsPerSecond, Color fillColor) {
  rotateOrShift(SHIFT_RIGHT, durationMS, pixelsPerSecond, fillColor);
}

/**
 * Shift lights to the left
 * 
 * @param durationMS duration of the action in milliseconds
 * @param distance the number of light positions to shift
 * @param fillColor color to fill lights shift in from the right
 */
inline void shiftLeft(float durationMS, int pixelsPerSecond, Color fillColor) {
  rotateOrShift(SHIFT_LEFT, durationMS, pixelsPerSecond, fillColor);
}

/**
 * Fades from the current colors to the specified color.
 * 
 * @param durationMS
 * @param newColor
 */
void fadeTo(int durationMS, Color newColor) {
  // Each fade costs computation time, so subtract from duration budget.
  durationMS = constrain(durationMS - 131, TIME_STEP_MS, 32767);
  
  int numTicks = durationMS / TIME_STEP_MS;
  int newStepSizeMicrosec = 1000L * durationMS / numTicks;

  Color* oldColors = new Color[strip.numPixels()];
  for (int i = 0; i < strip.numPixels(); i++) {
    oldColors[i] = strip.getPixelColor(i);
  }

  for (int i = 1; i <= numTicks; i++) {
    int ratio = 100 * i / numTicks;
    for (int light = 0; light < strip.numPixels(); light++) {
      Color stepColor = blend(oldColors[light], newColor, ratio);
      strip.setPixelColor(light, stepColor);
    }

    tickMicroseconds(newStepSizeMicrosec);
  }

  delete [] oldColors;
}

void sparklePixel(int durationMS, int pos, Color color) {
  int numTicks = durationMS / TIME_STEP_MS;
  long stopTime = millis() + durationMS;

  while (millis() < stopTime) {
    Color nowColor = fade(color, random(20, 101));
      strip.setPixelColor(pos, nowColor);
    strip.show();
    delay(50 /*ms*/);
  }
}

inline void fuse(int durationMS, Color fuseColor, Color burnColor) { fuse(durationMS, fuseColor, burnColor, strip.numPixels()); }
void fuse(int durationMS, Color fuseColor, Color burnColor, int length) {
  // Initialize the length to half brightness.
  for (int i = 0; i < length; i++) {
    strip.setPixelColor(i, fuseColor);
  }

  int stepDuration = durationMS / length;
  int currentPixel = length;
  while (currentPixel-- > 0) {
    printLong("numTicks", currentPixel);
    sparklePixel(stepDuration, currentPixel, burnColor);
    Serial.println();
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

void rotateOrShift(RotateShiftOp op, int durationMS, int pixelsPerSecond, Color fillColor) {
  float const secondsPerPixel = 1.0 / pixelsPerSecond;
  int const numTicks = (int)(durationMS / 1000.0 / secondsPerPixel);

  unsigned long const startTimeMS = millis();
  unsigned long const endTimeMS = startTimeMS + durationMS;
  
  for (int i = 0; i <= numTicks; i++) {
    switch (op) {
    case ROTATE_LEFT:
      rotateLeft(1);
      break;
    case ROTATE_RIGHT:
      rotateRight(1);
      break;
    case SHIFT_LEFT:
      shiftLeft(1, fillColor);
      break;
    case SHIFT_RIGHT:
      shiftRight(1, fillColor);
      break;
    }

    tickMicroseconds(secondsPerPixel*1000*1000);
  }
}

void tick() {
  strip.show();
  delay(TIME_STEP_MS);
}

void tickMicroseconds(float delayTime) {
  strip.show();
  while (delayTime > 16000) {
    delayMicroseconds(16000);
    delayTime -= 16000;
  }
  delayMicroseconds(delayTime);
}

