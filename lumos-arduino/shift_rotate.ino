/**
 * Shift all of the lights to the left
 * 
 * @param distance the number of lights to shift by
 * @param fillColor the color to set to the newly vacated lights
 */
void shiftLeft(int distance, uint32_t fillColor) {
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
void shiftRight(int distance, uint32_t fillColor) {
    int effectiveDistance = distance % strip.numPixels();
    rotateRight(distance);
    for (int i = 0; i < effectiveDistance; i++) {
        strip.setPixelColor(i, fillColor);
    }
}

/**
 * Rotate all of the the lights to the left by the specified distance
 */
void rotateLeft(int distance) {
    int effectiveDistance = distance % strip.numPixels();
    swapPartitions(effectiveDistance);
}

/**
 * Rotate all of the the lights to the right by the specified distance
 */
void rotateRight(int distance) {
    int effectiveDistance = strip.numPixels() - (distance % strip.numPixels());
    swapPartitions(effectiveDistance);
}

/**
 * Swap left-half partition with right-half partition at the specified pivot point.
 */
void swapPartitions(int partition) {
    // Save the left side of the partition.
    uint32_t* leftSide = new uint32_t[partition];
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

