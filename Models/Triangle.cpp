#include "Triangle.h"
#include "lumos-arduino/Models/ModelUtils.h"

Color Triangle::render(float pos) {
  if (pos < rangeMin || pos > rangeMax) {
    return BLACK;
  }

  float midPoint = (rangeMin + rangeMax) / 2;

  if (pos <= midPoint) {
    // Rising side of the triangle
    float ratio = fmap(pos, rangeMin, midPoint, 0.0, 1.0);
    return Colors::blend(BLACK, color, ratio);
  } else {
    // Falling side of the triangle
    float ratio = fmap(pos, midPoint, rangeMax, 1.0, 0.0);
    return Colors::blend(BLACK, color, ratio);
  }
}

void Triangle::asJson(JsonObject obj) const {
  Model::asJson(obj);
  obj["rangeMin"] = rangeMin;
  obj["rangeMax"] = rangeMax;
  colorAsJson(obj["color"].to<JsonObject>(), color);
}
