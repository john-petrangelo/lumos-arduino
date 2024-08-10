#include <cstdarg>

#include "Logger.h"

ILogger *Logger::instance = nullptr;

void Logger::logInt(char const *name, int value) {
  if (instance != nullptr) {
    instance->logInt(name, value);
  }
}

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

void Logger::logLong(char const *name, long value) {
  if (instance != nullptr) {
    instance->logLong(name, value);
  }
}

void Logger::logColor(char const *name, Color value) {
  if (instance != nullptr) {
    instance->logColor(name, value);
  }
}

void Logger::logFloat(char const *name, float value, int precision) {
  if (instance != nullptr) {
    instance->logFloat(name, value, precision);
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

void Logger::logAvailableMemory() {
  if (instance != nullptr) {
    instance->logAvailableMemory();
  }
}

void Logger::set(ILogger *newInstance) {
  if (instance != nullptr) {
    delete instance;
  }
  instance = newInstance;
}
