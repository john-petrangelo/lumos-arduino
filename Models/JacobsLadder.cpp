#include <algorithm>

#include "ModelUtils.h"
#include "JacobsLadder.h"
#include "Map.h"
#include "Shift.h"
#include "Triangle.h"

Color const JacobsLadder::defaultColor = WHITE;

JacobsLadder::JacobsLadder(float const size, float const frequency, Color const color, float const jitterSize,
                           float const jitterPeriod)
  : Model("JacobsLadder"), size(size), frequency(frequency), color(color),
    jitterSize(jitterSize), jitterPeriod(jitterPeriod) {
  init();
}

void JacobsLadder::init() {
  ModelPtr const glow = Triangle::make(0.0, 1.0, color);

  // If the size is too big or too small, then we have a warp core breach, light the whole length
  if (size < 0.0 || size >= 1.0) {
    size = 1.0;
  }

  // Can't handle exactly zero frequency, so pretend by setting it really, really low
  if (frequency <= 0.0) {
    frequency = 0.000001;
    return;
  }

  // Map the glow into the middle with the specified size
  mapModel = Map::make(0.0f, size, 0.0, 1.0, glow);

  // Calculate how long to display and shift the lights
  duration = 1 / frequency;

  // Set the initial mode and model
  model = Shift::Out::make(duration, mapModel);
}

void JacobsLadder::set(float const newFrequency, float const newSize, Color const newColor, float const newJitterSize,
                       float const newJitterPeriod) {
  frequency = newFrequency;
  size = newSize;
  color = newColor;
  jitterSize = newJitterSize;
  jitterPeriod = newJitterPeriod;

  init();
}

void JacobsLadder::update(float const timeStamp) {
  if (timeStamp - lastResetTime >= std::abs(duration)) {
    lastResetTime = timeStamp;
    model->reset();
  }

  model->update(timeStamp);
  brightness = fmap(timeStamp, lastResetTime, lastResetTime + duration, 0.0, 1.0);

  if (timeStamp - lastJitterTime >= jitterPeriod) {
    jitter = frand(0.0, jitterSize);
    lastJitterTime = timeStamp;
  }
}

Color JacobsLadder::render(float pos) {
  pos = std::clamp(pos + jitter, 0.0f, 1.0f);
  Color const c = model->render(pos);
  uint8_t const red = Colors::fade(Colors::getRed(c), brightness);
  uint8_t const green = Colors::fade(Colors::getGreen(c), brightness);
  uint8_t const blue = Colors::fade(Colors::getBlue(c), brightness);

  return Colors::makeColor(red, green, blue);
}

void JacobsLadder::asJson(JsonObject const obj) const {
  Model::asJson(obj);
  obj["size"] = size;
  obj["frequency"] = frequency;
  obj["duration"] = duration;
  colorAsJson(obj["color"].to<JsonObject>(), color);
  model->asJson(obj["model"].to<JsonObject>());
}
