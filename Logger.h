#pragma once

#include <iostream>
#include <sstream>

#include "ILogger.h"

class Logger {
private:
    static Logger loggerInstance;
    static ILogger *instance;
    static std::ostringstream buffer;

public:
    Logger() = default;

    static Logger& getInstance() {
      return loggerInstance;
    }

    static void log(char const *msg);
    static void logf(char const *format,...);

    // Definition for generic types (move from cpp file to here)
    template<typename T>
    Logger& operator<<(const T& value) {
        buffer << value;
        return *this;
    }

    // Declaration for manipulators
    Logger& operator<<(std::ostream& (*manip)(std::ostream&));

    static void set(ILogger *newInstance);
};

extern Logger &logger;
