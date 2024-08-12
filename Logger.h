#pragma once

#include "ILogger.h"

class Logger {
private:
    static ILogger *instance;

public:
    static void log(char const *msg);
    static void logf(char const *format,...);

    static void set(ILogger *newInstance);
};
