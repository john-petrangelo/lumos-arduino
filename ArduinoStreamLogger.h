#pragma once

#include <Stream.h>

#include "Colors.h"
#include "ILogger.h"

class ArduinoStreamLogger : public ILogger {
public:
    explicit ArduinoStreamLogger(Stream *newStream) : stream(newStream) {}

    void logInt(char const *name, int value);
    virtual void logMsg(char const *msg);
    virtual void logMsgLn(char const *msg);
    virtual void logLong(char const *name, long value);
    virtual void logColor(char const *name, Color value);
    virtual void logFloat(char const *name, float value, int precision);
    virtual void logf(char const *format,...);
    virtual void logAvailableMemory();

  private:
    void logName(char const *name);
    Stream *stream;
};
