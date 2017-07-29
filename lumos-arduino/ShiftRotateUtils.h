#ifndef _SHIFT_ROTATE_UTILS_H_
#define _SHIFT_ROTATE_UTILS_H_

#include "defs.h"

class ShiftRotateUtils {
  public:
    static void shiftLeft(int distance, Color fillColor);
    static void shiftRight(int distance, Color fillColor);
    static void rotateLeft(int distance);
    static void rotateRight(int distance);

  private:
    static void swapPartitions(int partition);
};

#endif // _SHIFT_ROTATE_UTILS_H_

