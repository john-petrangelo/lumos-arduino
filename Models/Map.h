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
    Map(float inRangeMin, float inRangeMax, float outRangeMin, float outRangeMax,
        ModelPtr model)
      : Model("Map"), inRangeMin(inRangeMin), inRangeMax(inRangeMax),
        outRangeMin(outRangeMin), outRangeMax(outRangeMax), model(std::move(model)) { }
    void update(float timeStamp) override { model->update(timeStamp); }
    Color render(float pos) override;
    void asJson(JsonObject obj) const override;

    void setInRange(float newInRangeMin, float newInRangeMax) {
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
