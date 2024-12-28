#include "Gauge.h"

void Gauge::setValue(float valueIn) {
  value = valueIn;
  fullColorPixels = floor(value * pixelsCount);
  remainder = value - fullColorPixels / pixelsCount;
  colorRatio = remainder * pixelsCount;
  partialColor = Colors::fade(color, colorRatio);
}

Color Gauge::render(float pos) {
  // Figure out which is the last pixel we should light.
  float posPixel = floor(pos * pixelsCount);

  // If this isn't the last pixel, just return the full color.
  if (posPixel < fullColorPixels) {
    return color;
  }

  // If this pixel is beyond the final lit pixel, paint it black.
  if (posPixel > fullColorPixels) {
    return BLACK;
  }

  // It's the last pixel to be lit, dim the color proportionally to the remainder.
  return partialColor;
}

void Gauge::asJson(JsonObject obj) const {
  Model::asJson(obj);
  obj["value"] = getValue();
  obj["pixelsCount"] = pixelsCount;
  obj["fullColorPixels"] = fullColorPixels;
  obj["value"] = getValue();
  obj["remainder"] = remainder;
  obj["colorRatio"] = colorRatio;
  colorAsJson(obj["fullColor"].to<JsonObject>(), color);
  colorAsJson(obj["partialColor"].to<JsonObject>(), partialColor);
}
