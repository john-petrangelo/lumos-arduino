#include <cstdarg>

#include "Logger.h"

ILogger *Logger::instance = nullptr;

void Logger::logMsg(char const *msg) {
  if (instance != nullptr) {
    instance->logMsg(msg);
  }
}

void Logger::logMsgLn(char const *msg) {
  if (instance != nullptr) {
    instance->logMsgLn(msg);
  }
}

void Logger::logf(char const *format,...) {
  if (instance != nullptr) {
    va_list args;
    va_start(args, format);
    instance->logf(format, args);
    va_end(args);
  }
}

void Logger::set(ILogger *newInstance) {
  if (instance != nullptr) {
    delete instance;
  }
  instance = newInstance;
}
