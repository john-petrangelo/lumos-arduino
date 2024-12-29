#include "ModelUtils.h"
#include "Triangle.h"

Color Triangle::render(float const pos) {
  if (pos < rangeMin || pos > rangeMax) {
    return BLACK;
  }

  if (float const midPoint = (rangeMin + rangeMax) / 2; pos <= midPoint) {
    // Rising side of the triangle
    float const ratio = fmap(pos, rangeMin, midPoint, 0.0, 1.0);
    return Colors::blend(BLACK, color, ratio);
  } else {
    // Falling side of the triangle
    float const ratio = fmap(pos, midPoint, rangeMax, 1.0, 0.0);
    return Colors::blend(BLACK, color, ratio);
  }
}

void Triangle::asJson(JsonObject const obj) const {
  Model::asJson(obj);
  obj["rangeMin"] = rangeMin;
  obj["rangeMax"] = rangeMax;
  colorAsJson(obj["color"].to<JsonObject>(), color);
}
