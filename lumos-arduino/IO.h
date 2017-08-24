#ifndef _IO_H_
#define _IO_H_

#include "Action.h"
#include "Effect.h"
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

  class RotatePool {
    private:
      static int const NUM_ROTATES = 4;
      Rotate rotatePool[NUM_ROTATES];
      int nextRotateIndex = 0;

    public:
      Rotate &getNext();
  };

  PixelsArray pixels1;

  NullEffect nullEffect;
  ActionGroup actions;

  RotatePool rotatePool;

  public:
    IO() : actions(0) { }
  
    void getCmd();

  private:
    CommandType readCommand();
    Range readRange();
    Color readColor();
    Direction readDirection();

    void skipWhitespace();

    void writeNotYetImplemented();
    void writeInvalidCmd();
    void writeCmd(CommandType cmd, Range range, Color color);
    void writeCmd(CommandType cmd, Range range, Color color1, Color color2);
    void writeCmd(CommandType cmd, Range range, int val, Direction direction);
    void writeRange(Range range);
    void writeColor(Color color);
    void writeDirection(Direction direction);
};

#endif /* _IO_H_ */

