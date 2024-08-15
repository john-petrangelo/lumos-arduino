#include <cstdarg>
#include <cstdio>
#include <sstream>

#include "Logger.h"

ILogger *Logger::instance = nullptr;
std::ostringstream Logger::buffer;

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
  buff[std::size(buff)-1]='\0';
  log(buff);
}

Logger& Logger::operator<<(std::ostream& (*manip)(std::ostream&)) {
  buffer << manip;
  if (manip == static_cast<std::ostream& (*)(std::ostream&)>(std::endl)) {
    log(buffer.str().c_str());
    buffer.str(""); // Clear the buffer
    buffer.clear(); // Clear any error flags
  }
  return *this;
}

void Logger::set(ILogger *newInstance) {
  if (instance != nullptr) {
    delete instance;
  }
  instance = newInstance;
}
