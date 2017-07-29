#include "Log.h"

void Log::printInt(char const *name, int value) {
  Serial.print(name);
  Serial.print("=");
  Serial.print(value);
  Serial.print(" ");
}

void Log::printLong(char const *name, long value) {
  Serial.print(name);
  Serial.print("=");
  Serial.print(value);
  Serial.print(" ");
}

void Log::printColor(char const *name, Color value) {
  Serial.print(name);
  Serial.print("=");
  Serial.print(value, HEX);
  Serial.print(" ");
}

void Log::printFloat(char const *name, float value, int precision) {
  Serial.print(name);
  Serial.print("=");
  Serial.print(value, precision);
  Serial.print(" ");
}

