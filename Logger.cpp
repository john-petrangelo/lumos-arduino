#include <cstdarg>
#include <cstdio>

#include "Logger.h"

ILogger *Logger::instance = nullptr;

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
  vsnprintf(buff,sizeof(buff),format,args);
  va_end (args);
  buff[sizeof(buff)/sizeof(buff[0])-1]='\0';
  log(buff);
}

void Logger::set(ILogger *newInstance) {
  if (instance != nullptr) {
    delete instance;
  }
  instance = newInstance;
}
