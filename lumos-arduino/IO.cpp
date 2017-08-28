#include <hardwareSerial.h>

#include "Action.h"
#include "Colors.h"
#include "Effect.h"
#include "IO.h"
#include "Patterns.h"

char buffer[64];

bool IO::isRunning = true;

void IO::getCmd() {
  Serial.println("RDY");

  // Wait for someting to arrive on the Serial bus.
  while (!Serial.available()) {
    if (isRunning) {
      actions.loop();
    }
  }

  // Keep looping while there is more to read.
  while (Serial.available()) {
    Range range(0, 0);
    Color color1;
    Color color2;
    int pixelsPerSecond;
    int periodMS;
    Direction direction;
    Blink &blink = blinkPool.getCurrent();
    Rotate &rotate = rotatePool.getCurrent();
    Flicker &flicker = flickerPool.getCurrent();
    Noise &noise = noisePool.getCurrent();
    
    CommandType cmd = readCommand();
    switch(cmd) {
      case BLINK:
        range = readRange();
        periodMS = Serial.parseInt();
        color1 = readColor();
        color2 = readColor();
        writeCmd(cmd, range, periodMS, color1, color2);
        blink = blinkPool.getNext();
        blink.setRange(range);
        blink.setPeriodMS(periodMS);
        blink.setColor(0, color1);
        blink.setColor(1, color2);
        actions.add(&blink);
        break;
      case ROTATE:
        range = readRange();
        pixelsPerSecond = Serial.parseInt();
        direction = readDirection();
        writeCmd(cmd, range, pixelsPerSecond, direction);
        rotate = rotatePool.getNext();
        rotate.setRange(range);
        rotate.setPixelsPerSecond(pixelsPerSecond);
        rotate.setDirection(direction);
        actions.add(&rotate);
        break;
      case FLICKER:
        range = readRange();
        color1 = readColor();
        writeCmd(cmd, range, color1);
        flicker = flickerPool.getNext();
        flicker.setRange(range);
        flicker.setColor(color1);
        actions.add(&flicker);
        break;
        break;
      case NOISE:
        range = readRange();
        color1 = readColor();
        writeCmd(cmd, range, color1);
        noise = noisePool.getNext();
        noise.setRange(range);
        noise.setColor(color1);
        actions.add(&noise);
        break;
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
        writeCmd(cmd, range, color1);
        Patterns::setSolidColor(range.first, range.last, color1);
        break;
      case SET_GRADIENT:
        range = readRange();
        color1 = readColor();
        color2 = readColor();
        writeCmd(cmd, range, color1, color2);
        Patterns::setGradient(range.first, range.last, 2, color1, color2);
        break;
      case SET_SINE_WAVE:
        writeNotYetImplemented();
      case CLEAR:
        writeCmd(cmd);
        clear();
        Patterns::setSolidColor(BLACK);
        break;
      case PAUSE:
        writeCmd(cmd);
        isRunning = false;
        break;
      case RESUME:
        writeCmd(cmd);
        isRunning = true;
        break;
      case NONE:
      default:
        break;
    }
  }

  strip.show();
}

void IO::clear() {
  actions.clear();
}

IO::CommandType IO::readCommand() {
  skipWhitespace();
  if (!Serial.available()) {
    // Only whitespace was available, just bail out.
    return NONE;
  }
  
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

  if (strcmp(buffer, "CL") == 0) return CLEAR;
  if (strcmp(buffer, "PS") == 0) return PAUSE;
  if (strcmp(buffer, "RS") == 0) return RESUME;

  // No match.
  Serial.print(F("Invalid cmd: "));
  Serial.println(buffer);
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

Direction IO::readDirection() {
  skipWhitespace();

  // Read the first two bytes - directions are clockwise (CW) or counter_clockwise (CC).
  byte numRead = Serial.readBytes(buffer, 2);

  // On errors, just assume clockwise.
  if (numRead < 2) {
    return CLOCKWISE;
  }

  if (buffer[0] != 'C') {
    return CLOCKWISE;
  }

  if (buffer[1] == 'C') {
    return COUNTER_CLOCKWISE;
  }
  
  return CLOCKWISE;
}

void IO::skipWhitespace() {
  while (isWhitespace(Serial.peek())) {
    Serial.read();
  }
}

void IO::writeNotYetImplemented() {
  Serial.println("\nCmd NYI");
}

void IO::writeCmd(CommandType cmd) {
  Log::logInt("cmd", cmd);
  Serial.println();
}

void IO::writeCmd(CommandType cmd, Range range, Color color) {
  Log::logInt("cmd", cmd);
  writeRange(range);
  writeColor(color);
  Serial.println();
}

void IO::writeCmd(CommandType cmd, Range range, Color color1, Color color2) {
  Log::logInt("cmd", cmd);
  writeRange(range);
  writeColor(color1);
  writeColor(color2);
  Serial.println();
}

void IO::writeCmd(CommandType cmd, Range range, int val, Direction direction) {
  Log::logInt("cmd", cmd);
  writeRange(range);
  Log::logInt("val", val);
  writeDirection(direction);
  Serial.println();
}

void IO::writeCmd(CommandType cmd, Range range, int periodMS, Color color1, Color color2) {
  Log::logInt("cmd", cmd);
  writeRange(range);
  Log::logInt("periodMS", periodMS);
  writeColor(color1);
  writeColor(color2);
  Serial.println();
  
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
  Serial.print("0x");
  Serial.print(color, HEX);
  Serial.print(' ');
}

void IO::writeDirection(Direction direction) {
    Serial.print("dir=");
  if (direction == CLOCKWISE) {
    Serial.print("CW");
  } else {
    Serial.print("CC");
  }
  Serial.print(' ');
}

template <class T, int NUM_ACTIONS>
T &IO::ActionPool<T, NUM_ACTIONS>::getNext() {
  T &newAction = actionPool[nextIndex++];
  nextIndex %= NUM_ACTIONS;
  return newAction;
}

