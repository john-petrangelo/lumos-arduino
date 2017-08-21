#ifndef _IO_H_
#define _IO_H_

#include "Action.h"
#include "Log.h"

class IO {

  enum CommandType {
    BLINK, ROTATE, FLICKER, NOISE, FLAME,
    FADE_TO, FUSE, GROW, LIGHTNING,
    SET_SOLID_COLOR, SET_GRADIENT, SET_SINE_WAVE,
    PAUSE, RESUME,
    NONE
  };
  
  public:
    void getCmd();

  private:
    CommandType readCommand();
    Range readRange();
    Color readColor();

    void writeNotYetImplemented();
    void writeInvalidCmd();
    void writeRange(Range range);
    void writeColor(Color color);
};

#endif /* _IO_H_ */

