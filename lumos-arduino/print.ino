void printInt(char *name, int value) {
  Serial.print(name);
  Serial.print("=");
  Serial.print(value);
  Serial.print(" ");
}

void printLong(char *name, long value) {
  Serial.print(name);
  Serial.print("=");
  Serial.print(value);
  Serial.print(" ");
}

void printHex(char *name, long value) {
  Serial.print(name);
  Serial.print("=");
  Serial.print(value, HEX);
  Serial.print(" ");
}

void printFloat(char *name, float value, int precision) {
  Serial.print(name);
  Serial.print("=");
  Serial.print(value, precision);
  Serial.print(" ");
}

