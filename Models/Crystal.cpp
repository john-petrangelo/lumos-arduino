#include "Crystal.h"
#include "Pulsate.h"
#include "Sum.h"
#include "Triangle.h"

Crystal::Crystal(Color upperColor, float upperPeriodSec,
                 Color middleColor, float middlePeriodSec,
                 Color lowerColor, float lowerPeriodSec)
        : Model("Crystal") {
  model = makeCrystal(upperColor, upperPeriodSec, middleColor, middlePeriodSec, lowerColor, lowerPeriodSec);
}

Crystal::Crystal()
        : Model("DarkCrystal"),
          model(makeCrystal(0xff00d0, 5.0,
                            0xff00d0, 8.0,
                            0xff00d0, 7.0)) {}

void Crystal::asJson(JsonObject obj) const {
  Model::asJson(obj);
  model->asJson(obj["model"].to<JsonObject>());}

ModelPtr Crystal::makeCrystal(
    Color upperColor, float upperPeriodSec,
    Color middleColor, float middlePeriodSec,
    Color lowerColor, float lowerPeriodSec) {

  ModelPtr upperTriangle = std::make_shared<Triangle>(0.6, 1.0, upperColor);
  ModelPtr upperPulsate = upperTriangle;
  if (upperPeriodSec <= 10.0) {
    upperPulsate = std::make_shared<Pulsate>(0.3, 1.0, upperPeriodSec/2.0, upperPeriodSec/2.0, upperTriangle);
  }

  ModelPtr middleTriangle = std::make_shared<Triangle>(0.3, 0.7, middleColor);
  ModelPtr middlePulsate = middleTriangle;
  if (middlePeriodSec <= 10.0) {
    middlePulsate = std::make_shared<Pulsate>(0.4, 1.0, middlePeriodSec/2.0, middlePeriodSec/2.0, middleTriangle);
  }

  ModelPtr lowerTriangle = std::make_shared<Triangle>(0.0, 0.4, lowerColor);
  ModelPtr lowerPulsate = lowerTriangle;
  if (lowerPeriodSec <= 10.0) {
    lowerPulsate = std::make_shared<Pulsate>(0.3, 1.0, lowerPeriodSec/2.0, lowerPeriodSec/2.0, lowerTriangle);
  }

  ModelPtr sum = Sum::make({upperPulsate, middlePulsate, lowerPulsate});

  return sum;
}
