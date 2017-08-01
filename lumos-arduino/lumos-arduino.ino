#include "defs.h"
#include "Action.h"
#include "Colors.h"
#include "Effects.h"
#include "Log.h"
#include "ShiftRotateUtils.h"

int8_t const PIN = 13;
neoPixelType const STRIP_FLAGS = (NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip;

void setup() {
  // Initiate Serial communication.
  Serial.begin(9600);

  // Initialize the LED strip.
  strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, STRIP_FLAGS);
  strip.begin();
  strip.setBrightness(255);
  strip.show(); // Initialize all pixels to 'off'
}

PixelsArray pixels1;
PixelsArray pixels2;
PixelsArray pixels3;

void loop() {
  long startTime = millis();

  testBlink();
  
  Effects::fuse(10000, Colors::fade(WHITE, 3), ORANGE);

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
  long stopTime = millis();
  Log::logFloat((char*)"elapsed=", (stopTime - startTime) / 1000.0, 3);
  Log::logLn();
}

void testBlink() {
  // Operator new doesn't work right with virtual methods, use this workaround instead.
  // NOTE: Don't try to delete this object.
  Blink blink1(pixels1, 2000, PURPLE, ORANGE);
  Action *blink = &blink1;

  blink->setup();

  ActionRunner runner(blink);
  runner.runForDurationMS(10000);
}

