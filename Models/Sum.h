#pragma once

#include <vector>

#include "Model.h"

/*
 * Sum models together, channel by channel, constraining each channel to maximum brightness
 * 
 * Position and time independent.
 */
class Sum;
typedef std::shared_ptr<Sum> SumPtr;

class Sum : public Model {
  public:
    Sum(std::vector<ModelPtr>::const_iterator modelsBegin, std::vector<ModelPtr>::const_iterator modelsEnd)
      : Model("Sum"), models(modelsBegin, modelsEnd) {}
    Sum(std::initializer_list<ModelPtr> modelArgs) : Model("Sum"), models(modelArgs) {}
    void update(float timeStamp) override;
    Color render(float pos) override;
    void asJson(JsonObject obj) const override;

    static SumPtr make(std::vector<ModelPtr>::const_iterator modelsBegin, std::vector<ModelPtr>::const_iterator modelsEnd) {
      return std::make_shared<Sum>(modelsBegin, modelsEnd);
    }
    static SumPtr make(std::initializer_list<ModelPtr> initList) {
      return std::make_shared<Sum>(initList);
    }

private:
    std::vector<ModelPtr> models;
};
