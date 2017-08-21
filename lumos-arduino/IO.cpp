#include <hardwareSerial.h>

#include "Colors.h"
#include "IO.h"

char buffer[64];

void IO::getCmd() {
  Serial.println("RDY");
  
  // Wait for someting to arrive on the Serial bus.
  while (!Serial.available()) ;

  // Keep looping while there is more to read.
  while (Serial.available()) {
    Range range(0, 0);
    Color color1;
    Color color2;
    CommandType cmd = readCommand();
    switch(cmd) {
      case BLINK:
      case ROTATE:
      case FLICKER:
      case NOISE:
      case FLAME:
      case FADE_TO:
      case FUSE:
      case GROW:
      case LIGHTNING:
        writeNotYetImplemented();
        break;
      case SET_SOLID_COLOR:
        range = readRange();
        color1 = readColor();
        Log::logInt("cmd", cmd);
        writeRange(range);
        writeColor(color1);
        Serial.println();
        break;
      case SET_GRADIENT:
      case SET_SINE_WAVE:
      case PAUSE:
      case RESUME:
        writeNotYetImplemented();
        break;
      case NONE:
      default:
        writeInvalidCmd();
        break;
    }
  }
}

IO::CommandType IO::readCommand() {
  // Read the first two bytes - commands are always two bytes.
  byte numRead = Serial.readBytes(buffer, 2);
  buffer[numRead] = '\0';
  if (numRead != 2) {
    Serial.println(F("Cmd too short"));
    return NONE;
  }

  if (strcmp(buffer, "BL") == 0) return BLINK;
  if (strcmp(buffer, "RT") == 0) return ROTATE;
  if (strcmp(buffer, "FK") == 0) return FLICKER;
  if (strcmp(buffer, "NS") == 0) return NOISE;
  if (strcmp(buffer, "FM") == 0) return FLAME;

  if (strcmp(buffer, "FT") == 0) return FADE_TO;
  if (strcmp(buffer, "FS") == 0) return FUSE;
  if (strcmp(buffer, "GR") == 0) return GROW;
  if (strcmp(buffer, "LT") == 0) return LIGHTNING;

  if (strcmp(buffer, "SL") == 0) return SET_SOLID_COLOR;
  if (strcmp(buffer, "SN") == 0) return SET_SINE_WAVE;
  if (strcmp(buffer, "SG") == 0) return SET_GRADIENT;

  if (strcmp(buffer, "PS") == 0) return PAUSE;
  if (strcmp(buffer, "RS") == 0) return RESUME;

  // No match.
  return NONE;
}

Range IO::readRange() {
  int first = Serial.parseInt();
  int last = Serial.parseInt();
  return Range(first, last);
}

Color IO::readColor() {
  int red = Serial.parseInt();
  int green = Serial.parseInt();
  int blue = Serial.parseInt();

return strip.Color(red, green, blue);
}

void IO::writeNotYetImplemented() {
  Serial.println("\nCmd NYI");
}

void IO::writeInvalidCmd() {
  Serial.println("\nCmd invalid");
}

void IO::writeRange(Range range) {
  Serial.print('(');
  Serial.print(range.first);
  Serial.print(',');
  Serial.print(range.last);
  Serial.print(')');
  Serial.print(' ');
}

void IO::writeColor(Color color) {
  Serial.print(color, HEX);
  Serial.print(' ');
}

