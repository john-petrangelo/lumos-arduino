#include <cstdarg>
#include <cstdio>

#include "Logger.h"

ILogger *Logger::instance = nullptr;

Logger Logger::loggerInstance;
Logger& logger = Logger::getInstance();

void Logger::log(char const *msg) {
  if (instance != nullptr) {
    instance->log(msg);
  }
}

void Logger::logf(char const *format, ...)
{
  char buff[256];
  va_list args;
  va_start (args,format);
  vsnprintf(buff,sizeof(buff)-1,format,args);
  va_end (args);
  buff[sizeof(buff)-1]='\0';
  log(buff);
}

void Logger::set(ILogger *newInstance) {
  if (instance != nullptr) {
    delete instance;
  }
  instance = newInstance;
}

// The ESP8266 with 1MB of flash storage doesn't have enough room to
// also include the C++ stream library.
#ifndef ARDUINO_ARCH_ESP8266

std::ostringstream Logger::buffer;

Logger& Logger::operator<<(std::ostream& (*manip)(std::ostream&)) {
  buffer << manip;
  if (manip == static_cast<std::ostream& (*)(std::ostream&)>(std::endl)) {
    log(buffer.str().c_str());
    buffer.str(""); // Clear the buffer
    buffer.clear(); // Clear any error flags
  }
  return *this;
}
#endif
