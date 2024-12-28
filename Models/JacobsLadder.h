#pragma once

#include "lumos-arduino/Colors.h"

#include "Shift.h"

class JacobsLadder;
typedef std::shared_ptr<JacobsLadder> JacobsLadderPtr;

class JacobsLadder : public Model {
  public:
    JacobsLadder(float size, float frequency, Color color, float jitterSize, float jitterPeriod);

    void update(float timeStamp) override;
    Color render(float pos) override;
    void asJson(JsonObject obj) const override;
    void set(float newFrequency, float newSize, Color newColor, float newJitterSize, float newJitterPeriod);

    static JacobsLadderPtr make(float size, float frequency, Color color, float jitterSize, float jitterPeriod)
      { return std::make_shared<JacobsLadder>(size, frequency, color, jitterSize, jitterPeriod); }

    static Color const defaultColor;

private:
    void init();

    float lastResetTime{};
    float lastJitterTime{};

    ModelPtr mapModel;
    ShiftPtr model;

    float size;
    float frequency;
    Color color;
    float jitterSize;
    float jitterPeriod;

    float duration{};
    float brightness{};
    float jitter{};
};
