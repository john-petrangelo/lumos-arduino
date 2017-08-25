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
    CLEAR, PAUSE, RESUME,
    NONE
  };

  template <class T, int NUM_ACTIONS>
  class ActionPool {
    private:
      T actionPool[NUM_ACTIONS];
      int nextIndex = 0;

    public:
      T &getNext();
      T &getCurrent() { return actionPool[nextIndex]; }
  };

  NullEffect nullEffect;
  ActionGroup actions;

  ActionPool<Rotate, 4> rotatePool;
  ActionPool<Blink, 2> blinkPool;

  static bool isRunning;

  public:
    IO() : actions(0) { }
  
    void getCmd();

  private:
    void clear();
  
    CommandType readCommand();
    Range readRange();
    Color readColor();
    Direction readDirection();

    void skipWhitespace();

    void writeNotYetImplemented();
    void writeInvalidCmd();
    void writeCmd(CommandType cmd);
    void writeCmd(CommandType cmd, Range range, Color color);
    void writeCmd(CommandType cmd, Range range, Color color1, Color color2);
    void writeCmd(CommandType cmd, Range range, int val, Direction direction);
    void writeCmd(CommandType cmd, Range range, int periodMS, Color color1, Color color2);
    void writeRange(Range range);
    void writeColor(Color color);
    void writeDirection(Direction direction);
};

#endif /* _IO_H_ */

