#include "Sum.h"

void Sum::update(float timeStamp) {
  for (const ModelPtr& model : models) {
    model->update(timeStamp);
  }
}

Color Sum::render(float pos) {
  Color sum = BLACK;
  for (const ModelPtr& model : models) {
    sum = Colors::add(sum, model->render(pos));
  }

  return sum;
}

void Sum::asJson(JsonObject obj) const {
  Model::asJson(obj);
  JsonArray modelsArray = obj["models"].to<JsonArray>();
  for (const ModelPtr& model : models) {
    model->asJson(modelsArray.add<JsonObject>());
  }
}
