#pragma once

#include "Colors.h"

class ILogger {
public:
    virtual ~ILogger() = default;

    virtual void log(char const *msg) = 0;
};
