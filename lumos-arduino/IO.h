#ifndef _IO_H_
#define _IO_H_

#include "Action.h"
#include "Log.h"

class IO {
private:
  enum CommandType {
    BLINK, ROTATE, FLICKER, NOISE, FLAME,
    FADE_TO, FUSE, GROW, LIGHTNING,
    SET_SOLID_COLOR, SET_GRADIENT, SET_SINE_WAVE,
    PAUSE, RESUME,
    NONE
  };

  PixelsArray pixels1;

  NullEffect nullEffect;
  Action *currentAction = &nullEffect;

  public:
    void getCmd();

  private:
    CommandType readCommand();
    Range readRange();
    Color readColor();

    void writeNotYetImplemented();
    void writeInvalidCmd();
    void writeCmd(CommandType cmd, Range range, Color color);
    void writeRange(Range range);
    void writeColor(Color color);
};

#endif /* _IO_H_ */

