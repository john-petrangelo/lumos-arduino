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
//  colorWipe(RED, 50);
//  colorWipe(GREEN, 50);
//  colorWipe(BLUE, 50);
  // Send a theater pixel chase in...
//  theaterChase(WHITE, 50);
//  theaterChase(RED, 50);
//  theaterChase(BLUE, 50);s

//  rainbow(10);
//  rainbowCycle(5);
//  theaterChaseRainbow(50);
  Pixels pixels;

  // TODO: Test setSolidColor()
  setSineWave(pixels, BLACK, BLUE, 60, 0);
  applyPixels(pixels);
  strip.show();
  rotateRight(2400, 240);

  int delayMS = 300;
  setGradient(pixels, 1, VIOLET);
  applyPixels(pixels);
  strip.show();
  delay(delayMS);
  setGradient(pixels, 2, VIOLET, INDIGO);
  applyPixels(pixels);
  strip.show();
  delay(delayMS);
  setGradient(pixels, 3, VIOLET, INDIGO, BLUE);
  applyPixels(pixels);
  strip.show();
  delay(delayMS);
  setGradient(pixels, 4, VIOLET, INDIGO, BLUE, GREEN);
  applyPixels(pixels);
  strip.show();
  delay(delayMS);
  setGradient(pixels, 5, VIOLET, INDIGO, BLUE, GREEN, YELLOW);
  applyPixels(pixels);
  strip.show();
  delay(delayMS);
  setGradient(pixels, 6, VIOLET, INDIGO, BLUE, GREEN, YELLOW, ORANGE);
  applyPixels(pixels);
  strip.show();
  delay(delayMS);
  setGradient(pixels, 7, VIOLET, INDIGO, BLUE, GREEN, YELLOW, ORANGE, RED);
  applyPixels(pixels);
  strip.show();
  delay(delayMS);
  rotateRight(4000, 220);

  fadeTo(1000, RED);
  fadeTo(1000, WHITE);
  fadeTo(1000, BLUE);

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

