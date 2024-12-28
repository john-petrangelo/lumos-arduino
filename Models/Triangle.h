#pragma once

#include "Model.h"

class Triangle;
typedef std::shared_ptr<Triangle> TrianglePtr;

class Triangle : public Model {
public: Triangle(float rangeMin, float rangeMax, Color color)
            : Model("Triangle"), rangeMin(rangeMin), rangeMax(rangeMax), color(color) { }
    Color render(float pos) override;
    void asJson(JsonObject obj) const override;

    static TrianglePtr make(float rangeMin, float rangeMax, Color color) {
      return std::make_shared<Triangle>(rangeMin, rangeMax, color);
    }

private:
    float const rangeMin;
    float const rangeMax;
    Color const color;
};
