#include <cmath>

#include "ModelUtils.h"
#include "Pulsate.h"

void Pulsate::update(float const timeStamp) {
  float const modTimeStamp = std::fmod(timeStamp, periodSecs);
  if (modTimeStamp < brightenSecs) {
    // We're getting brighter
    dimness = fmap(modTimeStamp, 0.0, brightenSecs, brightest, dimmest);
  } else {
    // We're getting dimmer
    dimness = fmap(modTimeStamp, brightenSecs, periodSecs, dimmest, brightest);
  }

  // Update the wrapped model as well.
  model->update(modTimeStamp);
}

Color Pulsate::render(float const pos) {
  Color const oldColor = model->render(pos);
  Color const newColor = Colors::fade(oldColor, dimness);
  return newColor;
}

void Pulsate::asJson(JsonObject const obj) const {
  Model::asJson(obj);
  obj["dimmest"] = dimmest;
  obj["brightest"] = brightest;
  obj["dimSecs"] = dimSecs;
  obj["brightenSecs"] = brightenSecs;
  obj["periodSecs"] = periodSecs;
  model->asJson(obj["model"].to<JsonObject>());
}
