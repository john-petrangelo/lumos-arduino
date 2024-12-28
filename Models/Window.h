#pragma once

#include "Model.h"

/*
 * TODO Window description
 */
class Window : public Model {
  public:
    Window(float rangeMin, float rangeMax,
           ModelPtr insideModel, ModelPtr outsideModel)
      : Model("Window"), rangeMin(rangeMin), rangeMax(rangeMax),
        insideModel(std::move(insideModel)), outsideModel(std::move(outsideModel)) { }
    void update(float timeStamp) override { insideModel->update(timeStamp); outsideModel->update(timeStamp); }
    Color render(float pos) override;
    void asJson(JsonObject obj) const override;

private:
    ModelPtr insideModel;
    ModelPtr outsideModel;
    float rangeMin, rangeMax;
};
