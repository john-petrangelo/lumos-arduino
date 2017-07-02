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
typedef uint32_t Pixels[NUM_PIXELS];

Color const BLACK =  0x000000;
Color const BLUE =   0x0000FF;
Color const GREEN =  0x00FF00;
Color const CYAN =   0x00FFFF;
Color const RED =    0xFF0000;
Color const PURPLE = 0xFF00FF;
Color const YELLOW = 0xFFFF00;
Color const WHITE =  0xFFFFFF;

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
  applyPixels(pixels);
  delay(5000);

  // TODO: Test setGradient()
  setGradient(pixels, 3, RED, GREEN, BLUE);
  applyPixels(pixels);
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
void colorWipe(Color c, uint8_t wait) {
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

void printVar(char *name, int value, bool eol) {
  Serial.print(name);
  Serial.print("=");
  Serial.print(value);
  Serial.print(" ");

  if (eol) {
    Serial.println();
  }
}

void printVar(char *name, float value, bool eol) {
  Serial.print(name);
  Serial.print("=");
  Serial.print(value);
  Serial.print(" ");

  if (eol) {
    Serial.println();
  }
}

