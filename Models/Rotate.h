#pragma once

#include <utility>

#include "Model.h"

class Rotate;
typedef std::shared_ptr<Rotate> RotatePtr;

// An animation that rotates lights to the left or right. Wraps around so that
// once a color reaches the end, then it wraps around to the other end.
// The speed of rotation is given as a frequency expressed in Hz. A frequency
// of zero is stopped. Positive speed rotates up, negative speed rotates down.
class Rotate : public Model {
  public:
    Rotate(float speed, ModelPtr model) : Model("Rotate"), speed(speed), model(std::move(model)) {}
    Rotate(char const *name, float speed, ModelPtr model) : Model(name), speed(speed), model(std::move(model)) {}
    void update(float timeStamp) override;
    Color render(float pos) override;
    void asJson(JsonObject obj) const override;
    void setSpeed(float newSpeed) { speed = newSpeed; }
    void setModel(std::shared_ptr<Model> newModel) { model = std::move(newModel); }

    static RotatePtr make(float speed, const ModelPtr& model) {
      return std::make_shared<Rotate>(speed, model);
    }

private:
    float speed;
    float rotationOffset = 0.0;
    float prevTimeStamp = 0.0;
    std::shared_ptr<Model> model;
};
