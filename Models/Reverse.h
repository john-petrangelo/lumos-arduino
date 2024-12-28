#pragma once

#include <utility>

#include "Model.h"

class Reverse;
typedef std::shared_ptr<Reverse> ReversePtr;

class Reverse : public Model {
  public:
    explicit Reverse(ModelPtr model) : Model("Reverse"), model(std::move(model)) { }
    void update(float timeStamp) override { model->update(timeStamp); }
    Color render(float pos) override { return model->render(1.0f - pos); }

    void asJson(JsonObject obj) const override {
      Model::asJson(obj);
      model->asJson(obj["model"].to<JsonObject>());
    }

    static ReversePtr make(ModelPtr model) { return std::make_shared<Reverse>(std::move(model)); }

private:
    ModelPtr model;
};
