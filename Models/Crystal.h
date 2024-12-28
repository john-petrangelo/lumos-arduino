#pragma once

#include "Model.h"

class Crystal;
typedef std::shared_ptr<Crystal> CrystalPtr;

class Crystal : public Model {
public:
    Crystal(Color upperColor, float upperPeriodSec,
            Color middleColor, float middlePeriodSec,
            Color lowerColor, float lowerPeriodSec);

    // Special constructor to make "The Dark Crystal"
    Crystal();

    void update(float timeStamp) override { model->update(timeStamp); }
    Color render(float pos) override { return model->render(pos); };
    void asJson(JsonObject obj) const override;

  static CrystalPtr make() { return std::make_shared<Crystal>(); }

private:
    ModelPtr model;

    static std::shared_ptr<Model> makeCrystal(
            Color upperColor, float upperPeriodSec,
            Color middleColor, float middlePeriodSec,
            Color lowerColor, float lowerPeriodSec);
};
