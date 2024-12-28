#pragma once

#include <utility>

#include "Model.h"

class Shift;
typedef std::shared_ptr<Shift> ShiftPtr;

// An animation that shifts lights to the left or right. Unlike Rotate, it does not
// wrap around once a color reaches the end.
class Shift : public Model {
  public:
    enum SHIFT_MODE {
        SHIFT_IN,
        SHIFT_OUT
    };

    /**
     * @brief Constructor for Shift.
     *
     * @param shiftMode Specifies that the model shifts from the outside in or from the inside out
     * @param shiftDuration The time taken to shift the complete length in or out
     *              - Positive values indicate low-to-high
     *              - Negative values indicate high-to-low
     * @param model The model to shift in or out
     */
     Shift(SHIFT_MODE shiftMode, float shiftDuration, ModelPtr model) :
             Model("Shift"), shiftMode(shiftMode), shiftDuration(shiftDuration), model(std::move(model)),
             shiftOffset(1.0f), startTime(0.0f), endTime(0.0f), updateTime(0.0f) {}
    void update(float timeStamp) override;
    Color render(float pos) override;
    void asJson(JsonObject obj) const override;

    void setSpeed(float newSpeed) { shiftDuration = newSpeed; }
    void setModel(std::shared_ptr<Model> newModel) { model = std::move(newModel); }

    // Start the shifting all over again
    void reset() { startTime = 0.0f; }

    static ShiftPtr make(SHIFT_MODE shiftMode, float shiftDuration, ModelPtr model) {
      return std::make_shared<Shift>(shiftMode, shiftDuration, std::move(model));
    }

    class In {
    public:
        static ShiftPtr make(float shiftDuration, ModelPtr model) {
          return std::make_shared<Shift>(SHIFT_IN, shiftDuration, std::move(model));
        }
    };

    class Out {
    public:
        static ShiftPtr make(float shiftDuration, ModelPtr model) {
          return std::make_shared<Shift>(SHIFT_OUT, shiftDuration, std::move(model));
        }
    };

  private:
    SHIFT_MODE shiftMode;
    float shiftDuration;
    float startTime;
    float endTime;
    float updateTime;
    float shiftOffset;
    std::shared_ptr<Model> model;
};
