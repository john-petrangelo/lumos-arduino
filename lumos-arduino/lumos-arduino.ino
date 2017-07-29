#include "defs.h"
#include "Colors.h"
#include "Effects.h"
#include "Log.h"
#include "ShiftRotateUtils.h"

int8_t const PIN = 13;
neoPixelType const STRIP_FLAGS = (NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip;

void setup() {
  //Initiate Serial communication.
  Serial.begin(9600);

  // Initialize the LED strip.
  strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, STRIP_FLAGS);
  strip.begin();
  strip.setBrightness(255);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  long startTime = millis();

  Pixels pixels;
  Pixels pixels2;
  Pixels pixels3;

  Effects::fuse(30000, Colors::fade(WHITE, 3), ORANGE);

//  setGradient(pixels2, 7, VIOLET, INDIGO, BLUE, GREEN, YELLOW, ORANGE, RED);
//  //  setGradient(pixels2, 2, BLACK, BLUE);
//  reversePattern(pixels3, pixels2);
//  for (int ratio = 0; ratio <= 100; ratio += 3) {
//    blendPatterns(pixels, pixels2, pixels3, ratio);
//    applyPixels(pixels);
//    strip.show();
//    delay(20);
//  }
//  delay(1000);
//  for (int ratio = 0; ratio <= 100; ratio += 3) {
//    blendPatterns(pixels, pixels3, pixels2, ratio);
//    applyPixels(pixels);
//    strip.show();
//    delay(20);
//  }
//  delay(100);
//  rotateRight(3000, 20);
//  rotateLeft(250, 240);
//  delay(2000);
//
//    setSineWave(pixels, RED, BLUE, 60, 0);
//    applyPixels(pixels);
//    strip.show();
//    rotateRight(2000, 30);
//    delay(100);
//    rotateLeft(250, 240);
//    delay(1000);
//
//    setGradient(pixels, 7, VIOLET, INDIGO, BLUE, GREEN, YELLOW, ORANGE, RED);
//    applyPixels(pixels);
//    strip.show();
//    rotateRight(2000, 30);
//    delay(100);
//    rotateLeft(250, 240);
//    delay(1000);
//
//    fadeTo(1000, RED);
//    fadeTo(1000, WHITE);
//    fadeTo(1000, BLUE);
//
////    setGradient(3, RED, GREEN, BLUE);
////    delay(2000);
//
//    setSolidColor(pixels, BLACK);
//    setGradient(pixels, 3, RED, GREEN, BLUE);
//    applyPixels(pixels);
//    strip.show();
//    delay(2000);
//  
//    setSolidColor(pixels, BLACK);
//    setGradient(pixels, 3, RED, GREEN, RED);
//    applyPixels(pixels);
//    strip.show();
//    delay(2000);
//  
//  //  setSolidColor(BLACK);
//  //  setGradient(13, YELLOW, BLUE, YELLOW, RED, YELLOW, BLUE, YELLOW, RED, YELLOW, BLUE, YELLOW, RED, YELLOW);
//  //  strip.show();
//  //  delay(2000);
//  //
//  //  setRainbow();
//  //  johnDemo(15);
  long stopTime = millis();
  Log::printFloat((char*)"elapsed=", (stopTime - startTime) / 1000.0, 3);
  Log::println();
}

void johnDemo(int wait) {
  //  for (int i = 0; i < 40; ++i) {
  //    shiftLeft(1, GREEN);
  //    strip.show();
  //    delay(wait);
  //  }
  for (int i = 0; i < 60; ++i) {
    ShiftRotateUtils::rotateRight(1);
    strip.show();
    delay(wait);
  }
}

