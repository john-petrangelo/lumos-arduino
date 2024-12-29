#include "ModelUtils.h"
#include "Map.h"

Color Map::render(float const pos) {
  if ((inRangeMin <= pos) && (pos <= inRangeMax)) {
    float const outPos = fmap(pos, inRangeMin, inRangeMax, outRangeMin, outRangeMax);
    return model->render(outPos);
  }

  // Everything outside the "in range" will be BLACK
  return BLACK;
}

void Map::asJson(JsonObject const obj) const {
  Model::asJson(obj);
  obj["inRangeMin"] = inRangeMin;
  obj["inRangeMax"] = inRangeMax;
  obj["outRangeMin"] = outRangeMin;
  obj["outRangeMax"] = outRangeMax;
  model->asJson(obj["model"].to<JsonObject>());
}
