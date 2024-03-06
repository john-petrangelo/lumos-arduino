#include "defs.h"
#include "Action.h"
#include "Actions.h"
#include "Colors.h"
#include "Logger.h"
#include "Runner.h"
#include "Lumos.h"

int8_t const PIN = 2;
neoPixelType const STRIP_FLAGS = (NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip;

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

  // Start with a little white noise.
  demo_noise();

  delay(2000);

  // Four growing snakes.
  demo_quadGrow();

  // Fade to white.
  FadeTo fadeWhite(strip, pixels1, 3000, WHITE);
  Runner::runUntilDone(&fadeWhite);

  delay(500);

  // Fade in to RGB bands.
  FadeTo fade1(strip, pixels1, 2000, 0, 20, RED);
  FadeTo fade2(strip, pixels2, 2000, 20, 40, GREEN);
  FadeTo fade3(strip, pixels3, 2000, 40, 60, BLUE);
  ActionGroup fades(strip, 3, &fade1, &fade2, &fade3);
  Runner::runUntilDone(&fades);

  delay(500);

  // Rotate RGB.
  Rotate rotate(strip, 20, LEFT);
  Runner::runForDurationMS(2000, &rotate);
  rotate.setDirection(RIGHT);
  Runner::runForDurationMS(2000, &rotate);
  rotate.setDirection(LEFT);
  Runner::runForDurationMS(750, &rotate);
  rotate.setDirection(RIGHT);
  Runner::runForDurationMS(3750, &rotate);

  delay(500);

  // Fuse.
  Fuse fuse(strip, 12);
  Runner::runUntilDone(&fuse);

  // Lightning
  Lightning lightning(strip, WHITE);
  Runner::runUntilDone(&lightning);

  delay(1000);
  
  // Show rainbow.
  Patterns::setGradient(pixels1, 0, strip.numPixels(), 7, VIOLET, INDIGO, BLUE, GREEN, YELLOW, ORANGE, RED);
  Patterns::applyPixels(strip, pixels1);
  strip.show();

  delay(2000);

  // Rotate rainbow.
  rotate.setPixelsPerSecond(15);
  Runner::runForDurationMS(6000, &rotate);
  rotate.setPixelsPerSecond(30);
  Runner::runForDurationMS(3000, &rotate);
  rotate.setPixelsPerSecond(60);
  Runner::runForDurationMS(3000, &rotate);

  // Double rotate rainbow.
  Rotate rotateLeft(strip, 0, 30, 60, RIGHT);
  Rotate rotateRight(strip, 30, 60, 60, LEFT);
  ActionGroup rotateGroup(strip, 2, &rotateLeft, &rotateRight);
  Runner::runForDurationMS(3000, &rotateGroup);
  rotateLeft.setDirection(LEFT);
  rotateRight.setDirection(RIGHT);
  Runner::runForDurationMS(3000, &rotateGroup);
  rotateLeft.setPixelsPerSecond(120);
  rotateRight.setPixelsPerSecond(120);
  Runner::runForDurationMS(3000, &rotateGroup);

  // Fade through rainbow of colors.
  demo_fade(&fade1);

  delay(5000);

  long stopTime = millis();
  Logger::logFloat((char*)"elapsed=", (stopTime - startTime) / 1000.0, 3);
  Logger::logMsgLn("");
}

void demo_noise() {
  Noise noise(strip, Colors::fade(WHITE, 10));
  Patterns::setSolidColor(strip, pixels1, BLACK);

  Runner::runForDurationMS(3000, &noise);

  Patterns::applyPixels(strip, pixels1);
  strip.show();
  delay(500);

  Runner::runForDurationMS(800, &noise);

  Patterns::applyPixels(strip, pixels1);
  strip.show();
  delay(800);

  Runner::runForDurationMS(300, &noise);

  Patterns::applyPixels(strip, pixels1);
  strip.show();
  delay(700);

  Runner::runForDurationMS(300, &noise);

  Patterns::applyPixels(strip, pixels1);
  strip.show();
}

void demo_quadGrow() {
  Grow grow1(strip, 12, 0, 60, Colors::fade(RED, 10));
  Grow grow2(strip, 16, 0, 60, Colors::fade(GREEN, 10));
  Grow grow3(strip, 26, 0, 60, Colors::fade(BLUE, 10));
  Grow grow4(strip, 44, 0, 60, Colors::fade(WHITE, 10));
  DelayedStart delayed2(strip, 1500, &grow2);
  DelayedStart delayed3(strip, 3000, &grow3);
  DelayedStart delayed4(strip, 4000, &grow4);

  Patterns::setSolidColor(strip, pixels1, BLACK);
  Patterns::applyPixels(strip, pixels1);
  strip.show();

  ActionGroup actionGroup(strip, 4, &grow1, &delayed2, &delayed3, &delayed4);
  Runner::runUntilDone(&actionGroup);
}

void demo_fade(FadeTo *fade) {
  fade->setDurationMS(500);
  
  fade->setRange(0, 20);
  fade->setColor(VIOLET);
  Runner::runUntilDone(fade);

  fade->setRange(20, 40);
  fade->setColor(BLUE);
  Runner::runUntilDone(fade);

  fade->setRange(40, 60);
  fade->setColor(GREEN);
  Runner::runUntilDone(fade);

  fade->setRange(0, 20);
  fade->setColor(YELLOW);
  Runner::runUntilDone(fade);

  fade->setRange(20, 40);
  fade->setColor(ORANGE);
  Runner::runUntilDone(fade);

  fade->setRange(40, 60);
  fade->setColor(RED);
  Runner::runUntilDone(fade);

  fade->setDurationMS(2000);
  fade->setRange(0, 60);
  fade->setColor(BLACK);
  Runner::runUntilDone(fade);
}
