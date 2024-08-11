#pragma once

#include "Colors.h"

class ILogger {
public:
    virtual ~ILogger() = default;

    virtual void logMsg(char const *msg) = 0;
    virtual void logMsgLn(char const *msg) = 0;

    virtual void logf(char const *format,...) = 0;
};
