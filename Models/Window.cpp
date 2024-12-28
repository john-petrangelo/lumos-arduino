#include "Window.h"

Color Window::render(float pos) {
  if ((rangeMin <= pos) && (pos <= rangeMax)) {
    return insideModel->render(pos);
  }

  // The position is outside the range
  return outsideModel->render(pos);
}

void Window::asJson(JsonObject obj) const {
  Model::asJson(obj);
  obj["rangeMin"] = rangeMin;
  obj["rangeMax"] = rangeMax;
  insideModel->asJson(obj["insideModel"].to<JsonObject>());
  outsideModel->asJson(obj["outsideModel"].to<JsonObject>());
}
