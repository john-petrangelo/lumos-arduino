#include "lumos-arduino/Models/ModelUtils.h"

#include "Shift.h"

void Shift::update(float timeStamp) {
  // The first time we call update() we need to set the initial startTime
  if (startTime == 0.0) {
    startTime = timeStamp;

    endTime = startTime + std::abs(shiftDuration);
  }

  updateTime = timeStamp;

  // How far along are we in the shift window?
  if (updateTime > endTime) {
    // Should be done, return completely shifted.
    switch(shiftMode) {
      case SHIFT_IN:
        // For shift-in, that means the shift is completely in, so 1.0.
        shiftOffset = 1.0;
        break;
      case SHIFT_OUT:
        // For shift-out, that means the shift just out of range, so -1.01.
        shiftOffset = 1.01;
        break;
    }
  } else {
    shiftOffset = fmap(updateTime, startTime, endTime, 0.0f, 1.0f);
  }

  if (shiftMode == SHIFT_IN) {
    // If sliding in, then invert the offset to start with nothing and fill-in over time.
    shiftOffset = -(1.0f - shiftOffset);
  }

  // Adjust the offset by the direction (positive speed is low to high).
  shiftOffset = sign(shiftDuration) * shiftOffset;

  // Update the wrapped model as well.
  model->update(timeStamp);
}

Color Shift::render(float pos) {
  // If there's no predecessor, then there's nothing to shift. Bail out.
  if (model == nullptr) {
    return BLACK;
  }

  float const shiftedPos = pos - shiftOffset;

  // If the shifted position is out of range, then just return BLACK.
  if (shiftedPos > 1.0 || shiftedPos < 0.0) {
    return BLACK;
  }

  // Render the predecessor model at the adjusted position
  return model->render(shiftedPos);
}

void Shift::asJson(JsonObject obj) const {
  Model::asJson(obj);
  obj["duration"] = shiftDuration;
  obj["shiftMode"] = shiftMode;
  obj["shiftOffset"] = shiftOffset;
  obj["startTime"] = startTime;
  obj["endTime"] = endTime;
  obj["updateTime"] = updateTime;
  model->asJson(obj["model"].to<JsonObject>());
}
