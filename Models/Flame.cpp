#include "Flame.h"
#include "Gradient.h"
#include "ModelUtils.h"

Flame::Flame() : Model("Flame") {
  auto mgm = Gradient::make(BLACK, C1, C2, C3, C2, C1, BLACK);
  model = Map::make(0.0, 1.0, 0.0, 1.0, mgm);
  lastUpdateMS = -PERIOD_SEC;
}

void Flame::update(float timeStamp) {
  if ((timeStamp - lastUpdateMS) > PERIOD_SEC) {
    lastUpdateMS = timeStamp;

    float const lower = frand(0, 0.2);
    float const upper = frand(0.8, 1.0);

    model->setInRange(lower, upper);
    model->update(timeStamp);
  }
}

Color Flame::render(float pos) {
  return model->render(pos);
}

void Flame::asJson(JsonObject obj) const {
  Model::asJson(obj);
  colorAsJson(obj["Color1"].to<JsonObject>(), C1);
  colorAsJson(obj["Color2"].to<JsonObject>(), C2);
  colorAsJson(obj["Color3"].to<JsonObject>(), C3);
  model->asJson(obj["model"].to<JsonObject>());
}
