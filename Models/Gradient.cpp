#include <cmath>

#include "Gradient.h"

Color Gradient::render(float const pos) {
  float const colorPos = pos * static_cast<float>(colors.size() - 1);

  // Get the two colors flanking the mapped position
  int const lower = std::floor(colorPos);
  int const upper = std::ceil(colorPos);

  // Linearly interpolate from the lower color to the upper color. If same, quick return.
  if (upper == lower) {
    return colors[lower];
  }

  float const ratio = (colorPos - static_cast<float>(lower)) / static_cast<float>(upper - lower);
  return Colors::blend(colors[lower], colors[upper], ratio);
}

void Gradient::asJson(JsonObject const obj) const {
  Model::asJson(obj);
  JsonArray const colorArray = obj["colors"].to<JsonArray>();
  for (Color const color : colors) {
    colorAsJson(colorArray.add<JsonObject>(), color);
  }
}
