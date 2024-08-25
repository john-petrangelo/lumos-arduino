#pragma once

// The ESP8266 with 1MB of flash storage doesn't have enough room to
// also include the C++ stream library.
#ifndef ARDUINO_ARCH_ESP8266
#include <sstream>
#endif

#include "ILogger.h"

class Logger {
public:
    Logger() = default;

    static Logger& getInstance() {
        return loggerInstance;
    }

    static void log(char const *msg);
    static void logf(char const *format,...);

    static void set(ILogger *newInstance);

private:
    static Logger loggerInstance;
    static ILogger *instance;

// The ESP8266 with 1MB of flash storage doesn't have enough room to
// also include the C++ stream library.
#ifndef ARDUINO_ARCH_ESP8266
public:
    // Definition for generic types (move from cpp file to here)
    template<typename T>
    Logger& operator<<(const T& value) {
        buffer << value;
        return *this;
    }

    // Declaration for manipulators
    Logger& operator<<(std::ostream& (*manip)(std::ostream&));

private:
    static std::ostringstream buffer;

#endif
};

extern Logger &logger;
