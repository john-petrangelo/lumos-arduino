#pragma once

#include "Colors.h"
#include "ILogger.h"

class Logger {
private:
    static ILogger *instance;

public:
    static void logMsg(char const *msg);
    static void logMsgLn(char const *msg);
    static void logf(char const *format,...);

    static void set(ILogger *newInstance);
};
