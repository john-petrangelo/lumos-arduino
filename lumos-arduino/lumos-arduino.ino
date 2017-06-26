#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

enum RotateShiftOp {
    ROTATE_LEFT, ROTATE_RIGHT, SHIFT_LEFT, SHIFT_RIGHT
};

int8_t PIN = 6;
uint16_t NUM_PIXELS = 60;
neoPixelType STRIP_FLAGS = (NEO_GRB + NEO_KHZ800);

uint32_t const BLACK =  0x000000;
uint32_t const BLUE =   0x0000FF;
uint32_t const GREEN =  0x00FF00;
uint32_t const CYAN =   0x00FFFF;
uint32_t const RED =    0xFF0000;
uint32_t const PURPLE = 0xFF00FF;
uint32_t const YELLOW = 0xFFFF00;
uint32_t const WHITE =  0xFFFFFF;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, STRIP_FLAGS);

void setup() {
  //Initiate Serial communication.
  Serial.begin(9600);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
//  colorWipe(RED, 50);
//  colorWipe(GREEN, 50);
//  colorWipe(BLUE, 50);
  // Send a theater pixel chase in...
//  theaterChase(WHITE, 50);
//  theaterChase(RED, 50);
//  theaterChase(BLUE, 50);

//  rainbow(10);
//  rainbowCycle(5);
//  theaterChaseRainbow(50);

//  setSolidColor(BLACK);
//  setGradient(4, RED, GREEN, BLUE, RED);
//  strip.show();
//  delay(2000);
//
//  fadeTo(3.0, WHITE);
//
//  setSolidColor(BLACK);
//  setGradient(2, RED, GREEN);
//  strip.show();
//  delay(2000);
//
//  setSolidColor(BLACK);
  fadeTo(1.0, GREEN);
  fadeTo(1.0, YELLOW);
  fadeTo(1.0, BLUE);
  fadeTo(1.0, RED);
  fadeTo(1.0, WHITE);
  fadeTo(1.0, RED);
  fadeTo(1.0, WHITE);
  fadeTo(1.0, PURPLE);

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

void setRainbow() {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel(255 * i / strip.numPixels()));
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j*10) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow_orig(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

