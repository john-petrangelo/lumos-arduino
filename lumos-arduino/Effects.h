#ifndef _EFFECTS_H_
#define _EFFECTS_H_

#include "Colors.h"

class Effects {
  public:
    static void rotateRight(float durationMS, int pixelsPerSecond);
    static void rotateLeft(float durationMS, int pixelsPerSecond);
    static void shiftRight(float durationMS, int pixelsPerSecond, Color fillColor);
    static void shiftLeft(float durationMS, int pixelsPerSecond, Color fillColor);
    static void fadeTo(int durationMS, Color newColor);
    static void sparklePixel(int durationMS, int pos, Color color);
    static void fuse(int durationMS, Color fuseColor, Color burnColor);
    static void fuse(int durationMS, Color fuseColor, Color burnColor, int length);

  private:
    static int const TIME_STEP_MS = 30;

    static void rotateOrShift(RotateShiftOp op, int durationMS, int pixelsPerSecond, Color fillColor);
    static void tick();
    static void tickMicroseconds(float delayTime);
};

#endif // _EFFECTS_H_

