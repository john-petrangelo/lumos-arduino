#include "Sum.h"

void Sum::update(float const timeStamp) {
  for (const ModelPtr& model : models) {
    model->update(timeStamp);
  }
}

Color Sum::render(float const pos) {
  Color sum = BLACK;
  for (const ModelPtr& model : models) {
    sum = Colors::add(sum, model->render(pos));
  }

  return sum;
}

void Sum::asJson(JsonObject const obj) const {
  Model::asJson(obj);
  auto const modelsArray = obj["models"].to<JsonArray>();
  for (ModelPtr const& model : models) {
    model->asJson(modelsArray.add<JsonObject>());
  }
}
