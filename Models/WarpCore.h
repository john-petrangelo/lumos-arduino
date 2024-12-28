#pragma once

#include "lumos-arduino/Colors.h"
#include "Model.h"

class WarpCore;
typedef std::shared_ptr<WarpCore> WarpCorePtr;

class WarpCore : public Model {
  public:
    WarpCore(float size, float frequency, float dutyCycle, Color color, bool dual);

    void update(float timeStamp) override;
    Color render(float pos) override;
    void asJson(JsonObject obj) const override;
    void set(float newFrequency, float newSize, float newDutyCycle, Color color, bool dual);

    static WarpCorePtr make(float size, float frequency, float dutyCycle, Color color, bool dual)
      { return std::make_shared<WarpCore>(size, frequency, dutyCycle, color, dual); }

    static Color const defaultColor;

private:
    void init();
    void handleDual();

    enum Mode { MODE_IN, MODE_OUT, MODE_DARK };

    Mode mode = MODE_IN;
    float lastModeChangeTime;

    ModelPtr mapModel;
    ModelPtr model;

    float size;
    float frequency;
    float dutyCycle;
    Color color;
    bool dual;

    float durationDark{};
    float durationIn{};
    float durationOut{};
};
