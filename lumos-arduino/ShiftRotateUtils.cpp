#include "ShiftRotateUtils.h"

/**
 * Shift all of the lights to the left
 * 
 * @param distance the number of lights to shift by
 * @param fillColor the color to set to the newly vacated lights
 */
void ShiftRotateUtils::shiftLeft(int distance, Color fillColor) {
    int effectiveDistance = strip.numPixels() - (distance % strip.numPixels());
    rotateLeft(distance);
    for (int i = effectiveDistance; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, fillColor);
    }
}

/**
 * Shift all of the lights to the right
 * 
 * @param distance the number of lights to shift by
 * @param fillColor the color to set to the newly vacated lights
 */
void ShiftRotateUtils::shiftRight(int distance, Color fillColor) {
    int effectiveDistance = distance % strip.numPixels();
    rotateRight(distance);
    for (int i = 0; i < effectiveDistance; i++) {
        strip.setPixelColor(i, fillColor);
    }
}

/**
 * Rotate all of the the lights to the left by the specified distance
 */
void ShiftRotateUtils::rotateLeft(int distance) {
    int effectiveDistance = distance % strip.numPixels();
    swapPartitions(effectiveDistance);
}

/**
 * Rotate all of the the lights to the right by the specified distance
 */
void ShiftRotateUtils::rotateRight(int distance) {
    int effectiveDistance = strip.numPixels() - (distance % strip.numPixels());
    swapPartitions(effectiveDistance);
}

/**
 * Swap left-half partition with right-half partition at the specified pivot point.
 */
void ShiftRotateUtils::swapPartitions(int partition) {
  // Save the left side of the partition.
  Color* leftSide = new Color[partition];
  for (int i = 0; i < partition; ++i) {
    leftSide[i] = strip.getPixelColor(i);
  }

  // Copy the right side to the left side.
  int destIndex = 0;
  for (int i = partition; i < strip.numPixels(); ++i, ++destIndex) {
    strip.setPixelColor(destIndex, strip.getPixelColor(i));
  }

  // Copy the left side to the right side.
  int oldIndex = 0;
  for (;destIndex < strip.numPixels(); ++destIndex, ++oldIndex) {
    strip.setPixelColor(destIndex, leftSide[oldIndex]);
  }

  delete [] leftSide;
}

void ShiftRotateUtils::rotateLeft1() {
  Color c0 = strip.getPixelColor(0);
  for (int i = 0; i < strip.numPixels() - 1; i++) {
    strip.setPixelColor(i, strip.getPixelColor(i + 1));
  }
  strip.setPixelColor(strip.numPixels()-1, c0);
}

void ShiftRotateUtils::rotateRight1() {
  Color c_last = strip.getPixelColor(strip.numPixels() - 1);
  for (int i = strip.numPixels() - 1; i > 0; i--) {
    strip.setPixelColor(i, strip.getPixelColor(i - 1));
  }
  strip.setPixelColor(0, c_last);
}

