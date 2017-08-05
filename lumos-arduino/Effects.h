#ifndef _EFFECTS_H_
#define _EFFECTS_H_

#include "Action.h"
#include "Colors.h"

class Effects {
  public:
    static void sparklePixel(int durationMS, int pos, Color color);
    static void fuse(int durationMS, Color fuseColor, Color burnColor);
    static void fuse(int durationMS, Color fuseColor, Color burnColor, int length);

  private:
    static int const TIME_STEP_MS = 30;

    static void tick();
    static void tickMicroseconds(float delayTime);
};

#endif // _EFFECTS_H_

