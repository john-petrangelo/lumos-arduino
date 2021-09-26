#include <hardwareSerial.h>

#include "defs.h"
#include "Log.h"

void Log::logMsg(char const *msg) {
  Serial.print(msg);
  Serial.print(" ");
}

void Log::logMsgLn(char const *msg) {
  Serial.println(msg);
}

void Log::logInt(char const *name, int value) {
  logName(name);
  Serial.print(value);
  Serial.print(" ");
}

void Log::logLong(char const *name, long value) {
  logName(name);
  Serial.print(value);
  Serial.print(" ");
}

void Log::logColor(char const *name, Color value) {
  logName(name);
  Serial.print(value, HEX);
  Serial.print(" ");
}

void Log::logFloat(char const *name, float value, int precision) {
  logName(name);
  Serial.print(value, precision);
  Serial.print(" ");
}

void Log::logName(char const *name) {
  Serial.print(name);
  Serial.print("=");  
}

void Log::logAvailableMemory()
{
  int size = 8192;
  byte *buf;
  while ((buf = (byte *) malloc(--size)) == NULL);
  free(buf);
  logInt("availableMem", size);
} 
