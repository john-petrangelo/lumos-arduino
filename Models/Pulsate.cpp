#include <cmath>

#include "Pulsate.h"
#include "lumos-arduino/Models/ModelUtils.h"

void Pulsate::update(float timeStamp) {
  timeStamp = std::fmod(timeStamp, periodSecs);
  if (timeStamp < brightenSecs) {
    // We're getting brighter
    dimness = fmap(timeStamp, 0.0, brightenSecs, brightest, dimmest);
  } else {
    // We're getting dimmer
    dimness = fmap(timeStamp, brightenSecs, periodSecs, dimmest, brightest);
  }

  // Update the wrapped model as well.
  model->update(timeStamp);
}

Color Pulsate::render(float pos) {
  Color oldColor = model->render(pos);
  Color newColor = Colors::fade(oldColor, dimness);
  return newColor;
}

void Pulsate::asJson(JsonObject obj) const {
  Model::asJson(obj);
  obj["dimmest"] = dimmest;
  obj["brightest"] = brightest;
  obj["dimSecs"] = dimSecs;
  obj["brightenSecs"] = brightenSecs;
  obj["periodSecs"] = periodSecs;
  model->asJson(obj["model"].to<JsonObject>());
}
