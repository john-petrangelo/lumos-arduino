#include <cmath>

#include "Rotate.h"

void Rotate::update(float timeStamp) {
  // New timestamp, calculate the new offset.
  float deltaTime = timeStamp - prevTimeStamp;
  prevTimeStamp = timeStamp;

  // How far should we rotate given the time delta. Handle wrapping to keep
  // offset between 0.0 and 1.0.
  float deltaPos = -deltaTime * speed;
  rotationOffset = fmod(rotationOffset + deltaPos, 1.0f);
  if (rotationOffset < 0.0) {
    rotationOffset += 1.0;
  }

  // Update the wrapped model as well.
  model->update(timeStamp);
}

Color Rotate::render(float pos) {
  // If there's no predecessor, then there's nothing to rotate. Bail out.
  if (model == nullptr) {
    return BLACK;
  }

  // Add the offset to the position, then correct for wrap-around
  float rotatedPos = std::fmod(pos + rotationOffset, 1.0f);
  if (rotatedPos < 0.0) {
    rotatedPos += 1.0;
  }

  return model->render(rotatedPos);
}

void Rotate::asJson(JsonObject obj) const {
  Model::asJson(obj);
  obj["speed"] = speed;
  model->asJson(obj["model"].to<JsonObject>());
}
