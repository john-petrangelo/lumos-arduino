static int TIME_STEP_MS = 30;

/**
 * Rotate lights to the right
 * 
 * @param duration duration of the action in seconds
 * @param distance the number of light positions to rotate
 */
void rotateRight(double duration, int distance) {
  rotateOrShift(ROTATE_RIGHT, duration, distance, BLACK);
}

/**
 * Rotate lights to the left
 * 
 * @param duration duration of the action in seconds
 * @param distance the number of light positions to rotate
 */
void rotateLeft(double duration, int distance) {
  rotateOrShift(ROTATE_LEFT, duration, distance, BLACK);
}

/**
 * Shift lights to the right
 * 
 * @param duration duration of the action in seconds
 * @param distance the number of light positions to shift
 * @param fillColor color to fill lights shift in from the left
 */
void shiftRight(double duration, int distance, uint32_t fillColor) {
  rotateOrShift(SHIFT_RIGHT, duration, distance, fillColor);
}

/**
 * Shift lights to the left
 * 
 * @param duration duration of the action in seconds
 * @param distance the number of light positions to shift
 * @param fillColor color to fill lights shift in from the right
 */
void shiftLeft(double duration, int distance, uint32_t fillColor) {
  rotateOrShift(SHIFT_LEFT, duration, distance, fillColor);
}

int getNumTicks(int durationMS) {
  return durationMS / TIME_STEP_MS;
}

int getNewStepSizeInMicroseconds(int durationMS, int numTicks) {
  return 1000L * durationMS / numTicks;
}

/**
 * Fades from the current colors to the specified color.
 * 
 * @param duration
 * @param newColor
 */
void fadeTo(int durationMS, uint32_t newColor) {
  // Each fade costs computation time, so subtract from duration budget.
  durationMS = constrain(durationMS - 131, TIME_STEP_MS, 32767);
  
  int numTicks = getNumTicks(durationMS);
  int newStepSizeMicroSec = getNewStepSizeInMicroseconds(durationMS, numTicks);

  uint32_t* oldColors = new uint32_t[strip.numPixels()];
  for (int i = 0; i < strip.numPixels(); i++) {
    oldColors[i] = strip.getPixelColor(i);
  }

  for (int i = 1; i <= numTicks; i++) {
    int ratio = 100 * i / numTicks;
    for (int light = 0; light < strip.numPixels(); light++) {
      uint32_t stepColor = blend(oldColors[light], newColor, ratio);
      strip.setPixelColor(light, stepColor);
    }

    tick(newStepSizeMicroSec);
  }

  delete [] oldColors;
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

void rotateOrShift(RotateShiftOp op, float duration, int distance, uint32_t fillColor) {
  int numTicks = (int)(duration / TIME_STEP_MS);

  double rate = distance / duration;
  int distanceSoFar = 0;
  for (int i = 0; i <= numTicks; i++) {
    int currentDistance = (int)round(i * rate * TIME_STEP_MS);
    int delta = currentDistance - distanceSoFar;
    distanceSoFar = currentDistance;

    switch (op) {
    case ROTATE_LEFT:
      rotateLeft(delta);
      break;
    case ROTATE_RIGHT:
      rotateRight(delta);
      break;
    case SHIFT_LEFT:
      shiftLeft(delta, fillColor);
      break;
    case SHIFT_RIGHT:
      shiftRight(delta, fillColor);
      break;
    }

    tick();
  }
}

void tick() {
  strip.show();
  delay(TIME_STEP_MS);
}

void tick(int delayTime) {
  strip.show();
  while (delayTime > 16000) {
    delayMicroseconds(16000);
    delayTime -= 16000;
  }
  delayMicroseconds(delayTime);
}

