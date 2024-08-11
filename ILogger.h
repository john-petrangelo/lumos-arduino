#pragma once

#include "Colors.h"

class ILogger {
public:
    virtual ~ILogger() = default;

    virtual void logInt(char const *name, int value) = 0;
    virtual void logMsg(char const *msg) = 0;
    virtual void logMsgLn(char const *msg) = 0;
    virtual void logLong(char const *name, long value) = 0;
    virtual void logColor(char const *name, Color value) = 0;
    virtual void logFloat(char const *name, float value, int precision) = 0;
    virtual void logf(char const *format,...) = 0;
    virtual void logAvailableMemory() = 0;
};
