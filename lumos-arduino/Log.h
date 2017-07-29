#ifndef _LOG_H_
#define _LOG_H_

#include <hardwareSerial.h>
#include "defs.h"

class Log {
  public:
    static void printInt(char const *name, int value);
    static void printLong(char const *name, long value);
    static void printColor(char const *name, Color value);
    static void printFloat(char const *name, float value, int precision);

    static inline void println() { Serial.println(); }
};

#endif // _LOG_H_

