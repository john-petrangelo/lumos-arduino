#pragma once

#include "lumos-arduino/Colors.h"
#include "Model.h"
#include "Map.h"

class Flame : public Model {
  public:
    Flame();

    void update(float timeStamp) override;
    Color render(float pos) override;
    void asJson(JsonObject obj) const override;

  private:
    Color const C1 = Colors::blend(RED, YELLOW, 0.5);
    Color const C2 = Colors::blend(RED, YELLOW, 0.7);
    Color const C3 = Colors::blend(RED, YELLOW, 0.9);

    MapPtr model{};

    float lastUpdateMS;
    float const PERIOD_SEC = 0.110;
};
