#include "Model.h"

void Model::colorAsJson(JsonObject obj, Color c) {
  obj["red"] = Colors::getRed(c);
  obj["green"] = Colors::getGreen(c);
  obj["blue"] = Colors::getBlue(c);
}
