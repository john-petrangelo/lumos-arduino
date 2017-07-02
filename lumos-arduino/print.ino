void printInt(char const *name, int value) {
  Serial.print(name);
  Serial.print("=");
  Serial.print(value);
  Serial.print(" ");
}

void printLong(char const *name, long value) {
  Serial.print(name);
  Serial.print("=");
  Serial.print(value);
  Serial.print(" ");
}

void printHex(char const *name, long value) {
  Serial.print(name);
  Serial.print("=");
  Serial.print(value, HEX);
  Serial.print(" ");
}

void printFloat(char const *name, float value, int precision) {
  Serial.print(name);
  Serial.print("=");
  Serial.print(value, precision);
  Serial.print(" ");
}

