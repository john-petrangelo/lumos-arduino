#include "defs.h"

#include "Action.h"
#include "Patterns.h"
#include "ShiftRotateUtils.h"

ActionRunner::ActionRunner(Action *action) {
  this->action = action;
}

void ActionRunner::runForever() {
  while (1) {
    action->loop();
  }
}

void ActionRunner::runForDurationMS(long durationMS) {
  long endTime = millis() + durationMS;
  while (millis() < endTime) {
    action->loop();
  }
}

Blink::Blink(Pixels pixels, int periodMS, int firstPixel, int lastPixel, Color c1, Color c2)
  : pixels(pixels), periodMS(periodMS), firstPixel(firstPixel), lastPixel(lastPixel)
{
  this->colors[0] = c1;
  this->colors[1] = c2;
}

void Blink::setup() {
  nextBlinkTimeMS = millis() + periodMS / 2;
  colorIndex = 0;
  paint();
}

void Blink::loop() {
  if (millis() > nextBlinkTimeMS) {
    colorIndex = (colorIndex + 1) % 2;
    paint();
    nextBlinkTimeMS = millis() + periodMS / 2;
  }
}

void Blink::paint() {
  Patterns::setSolidColor(pixels, firstPixel, lastPixel, colors[colorIndex]);
  Patterns::applyPixels(pixels, firstPixel, lastPixel);
  strip.show();
}

RotateLeft::RotateLeft(int pixelsPerSecond) : pixelsPerSecond(pixelsPerSecond) { }

void RotateLeft::setup() {
  nextTimeMS = millis() + 1000.0 / pixelsPerSecond; 
}

void RotateLeft::loop() {
  
  if (millis() > nextTimeMS) {
    ShiftRotateUtils::rotateLeft1();

    nextTimeMS = millis() + 1000.0 / pixelsPerSecond; 
    strip.show();
  }
}

DualAction::DualAction(Action *a1, Action *a2) : action1(a1), action2(a2) { }

void DualAction::setup() {
  action1->setup();
  action2->setup();
}

void DualAction::loop() {
  action1->loop();
  action2->loop();
}

TripleAction::TripleAction(Action *a1, Action *a2, Action *a3) : action1(a1), action2(a2), action3(a3) { }

void TripleAction::setup() {
  action1->setup();
  action2->setup();
  action3->setup();
}

void TripleAction::loop() {
  action1->loop();
  action2->loop();
  action3->loop();
}

