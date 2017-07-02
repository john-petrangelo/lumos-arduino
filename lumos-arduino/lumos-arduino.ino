#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

enum RotateShiftOp {
    ROTATE_LEFT, ROTATE_RIGHT, SHIFT_LEFT, SHIFT_RIGHT
};

int8_t const PIN = 6;
uint16_t const NUM_PIXELS = 60;
neoPixelType const STRIP_FLAGS = (NEO_GRB + NEO_KHZ800);

typedef uint32_t Color;
typedef Color Pixels[NUM_PIXELS];

Color const BLACK =  0x000000;
Color const BLUE =   0x0000FF;
Color const GREEN =  0x00FF00;
Color const CYAN =   0x00FFFF;
Color const RED =    0xFF0000;
Color const PURPLE = 0xFF00FF;
Color const YELLOW = 0xFFFF00;
Color const WHITE =  0xFFFFFF;
Color const ORANGE = 0xFF7F00;
Color const INDIGO = 0x4B0082;
Color const VIOLET = 0x8F00FF;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, STRIP_FLAGS);

void setup() {
  //Initiate Serial communication.
  Serial.begin(9600);
  
  strip.begin();
  strip.setBrightness(255);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  long startTime = millis();

  // Some example procedures showing how to display to the pixels:
  // Send a theater pixel chase in...
//  theaterChase(WHITE, 50);

  Pixels pixels;
  Pixels pixels2;
  Pixels pixels3;

  setGradient(pixels2, 7, VIOLET, INDIGO, BLUE, GREEN, YELLOW, ORANGE, RED);
//  setGradient(pixels2, 2, BLACK, BLUE);
  reversePattern(pixels3, pixels2);
  for (int ratio = 0; ratio <= 100; ratio += 3) {
    blendPatterns(pixels, pixels2, pixels3, ratio);
    applyPixels(pixels);
    strip.show();
    delay(20);
  }
  delay(100);
  for (int ratio = 0; ratio <= 100; ratio += 3) {
    blendPatterns(pixels, pixels3, pixels2, ratio);
    applyPixels(pixels);
    strip.show();
    delay(20);
  }
  delay(100);
  rotateRight(2000, 60);
  rotateLeft(500, 240);

//  setSineWave(pixels, RED, BLUE, 60, 0);
//  applyPixels(pixels);
//  strip.show();
//  rotateRight(2000, 30);
//  delay(100);
//  rotateLeft(250, 240);
//  delay(1000);

//  setGradient(pixels, 7, VIOLET, INDIGO, BLUE, GREEN, YELLOW, ORANGE, RED);
//  applyPixels(pixels);
//  strip.show();
//  rotateRight(2000, 30);
//  delay(100);
//  rotateLeft(250, 240);
//  delay(1000);

//  fadeTo(1000, RED);
//  fadeTo(1000, WHITE);
//  fadeTo(1000, BLUE);

//  setGradient(3, RED, GREEN, BLUE);
//  delay(2000);

//  setSolidColor(BLACK);
//  setGradient(3, RED, GREEN, BLUE);
//  strip.show();
//  delay(2000);
//
//  setSolidColor(BLACK);
//  setGradient(3, RED, GREEN, RED);
//  strip.show();
//  delay(2000);
//
//  setSolidColor(BLACK);
//  setGradient(13, YELLOW, BLUE, YELLOW, RED, YELLOW, BLUE, YELLOW, RED, YELLOW, BLUE, YELLOW, RED, YELLOW);
//  strip.show();
//  delay(2000);
//
//  setRainbow();
//  johnDemo(15);
    long stopTime = millis();
    printFloat((char*)"elapsed=", (stopTime - startTime)/1000.0, 3);
    Serial.println();
}

void johnDemo(int wait) {
//  for (int i = 0; i < 40; ++i) {
//    shiftLeft(1, GREEN);
//    strip.show();
//    delay(wait);
//  }
  for (int i = 0; i < 60; ++i) {
    rotateRight(1);
    strip.show();
    delay(wait);
  }
}

