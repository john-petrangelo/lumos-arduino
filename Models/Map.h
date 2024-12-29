#pragma once

#include <utility>

#include "Model.h"

/*
 * TODO Map description
 */
class Map;
typedef std::shared_ptr<Map> MapPtr;

class Map : public Model {
  public:
    Map(float const inRangeMin, float const inRangeMax, float const outRangeMin, float const outRangeMax,
        ModelPtr model)
      : Model("Map"), model(std::move(model)), inRangeMin(inRangeMin),
        inRangeMax(inRangeMax), outRangeMin(outRangeMin), outRangeMax(outRangeMax) { }
    void update(float timeStamp) override { model->update(timeStamp); }
    Color render(float pos) override;
    void asJson(JsonObject obj) const override;

    void setInRange(float const newInRangeMin, float const newInRangeMax) {
      this->inRangeMin = newInRangeMin;
      this->inRangeMax = newInRangeMax;
    }

    static MapPtr make(float inRangeMin, float inRangeMax, float outRangeMin, float outRangeMax, ModelPtr model) {
      return std::make_shared<Map>(inRangeMin, inRangeMax, outRangeMin, outRangeMax, std::move(model));
    }


  private:
    ModelPtr model;
    float inRangeMin, inRangeMax, outRangeMin, outRangeMax;
};
