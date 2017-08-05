#ifndef _EFFECTS_H_
#define _EFFECTS_H_

#include "Colors.h"

class Effects {
  public:
    static void fuse(int durationMS, Color fuseColor, Color burnColor);
    static void fuse(int durationMS, Color fuseColor, Color burnColor, int length);
};

#endif // _EFFECTS_H_

