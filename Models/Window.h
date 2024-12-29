#pragma once

#include "Model.h"

/*
 * TODO Window description
 */
class Window : public Model {
  public:
    Window(float const rangeMin, float const rangeMax,
           ModelPtr insideModel, ModelPtr outsideModel)
      : Model("Window"), insideModel(std::move(insideModel)), outsideModel(std::move(outsideModel)),
        rangeMin(rangeMin), rangeMax(rangeMax) { }
    void update(float const timeStamp) override { insideModel->update(timeStamp); outsideModel->update(timeStamp); }
    Color render(float pos) override;
    void asJson(JsonObject obj) const override;

private:
    ModelPtr insideModel;
    ModelPtr outsideModel;
    float rangeMin, rangeMax;
};
