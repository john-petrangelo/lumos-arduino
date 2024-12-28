#pragma once

#include "Model.h"

class Gauge : public Model {
public: Gauge(uint16_t pixelsCount, Color color, float value = 0.0)
            : Model("Gauge"), pixelsCount(pixelsCount), color(color) { setValue(value); }
    Color render(float pos) override;
    void asJson(JsonObject obj) const override;

    float getValue() const { return value; }
    void setValue(float value);

private:
    float const pixelsCount;
    Color const color;
    float value = 0.0;
    float fullColorPixels = 0.0;
    float remainder = 0.0;
    float colorRatio = 0.0;
    Color partialColor = BLACK;
};
