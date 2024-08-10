#include <HardwareSerial.h>

#include "defs.h"
#include "ArduinoStreamLogger.h"
#include "ILogger.h"

ILogger *logger;

void ArduinoStreamLogger::logMsg(char const *msg) {
  stream->print(msg);
}

void ArduinoStreamLogger::logMsgLn(char const *msg) {
  stream->println(msg);
}

void ArduinoStreamLogger::logInt(char const *name, int value) {
  logName(name);
  stream->print(value);
  stream->print(" ");
}

void ArduinoStreamLogger::logLong(char const *name, long value) {
  logName(name);
  stream->print(value);
  stream->print(" ");
}

void ArduinoStreamLogger::logColor(char const *name, Color value) {
  logName(name);
  stream->print(value, HEX);
  stream->print(" ");
}

void ArduinoStreamLogger::logFloat(char const *name, float value, int precision) {
  logName(name);
  stream->print(value, precision);
  stream->print(" ");
}

void ArduinoStreamLogger::logName(char const *name) {
  stream->print(name);
  stream->print("=");
}

void ArduinoStreamLogger::logf(char const *format, ...)
{
  char buff[256];
  va_list args;
  va_start (args,format);
  vsnprintf(buff,sizeof(buff),format,args);
  va_end (args);
  buff[sizeof(buff)/sizeof(buff[0])-1]='\0';
  ArduinoStreamLogger::logMsg(buff);
}

void ArduinoStreamLogger::logAvailableMemory()
{
  int size = 8192;
  byte *buf;
  while ((buf = (byte *) malloc(--size)) == NULL);
  free(buf);
  
  logInt("availableMem", size);
}
