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
Color const VIOLET = 0x9400D3;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, STRIP_FLAGS);

void setup() {
  //Initiate Serial communication.
  Serial.begin(9600);
  
  strip.begin();
  strip.setBrightness(64);
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
  setSolidColor(pixels, GREEN);
  printHex((char*)"p[0]", pixels[0]);
  applyPixels(pixels);
  strip.show();
  delay(5000);

  // TODO: Test setGradient()
  setGradient(pixels, 7, RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET);
  applyPixels(pixels);
  strip.show();
  delay(5000);

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

