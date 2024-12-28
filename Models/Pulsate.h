#pragma once

#include "Model.h"

/*
 * Pulsate
 * 
 * Adjust the brightness of the underlying model between two percentages over a given period.
 * For example, the brightness may vary from 20% to 100% and back down to 20% over 3 seconds.
 * 
 * Constructors:
 *   Pulsate(dimmest, brightest, dimSecs, brightenSecs, model) - varies between dimmest and brightest,
 *      taking dimSecs to dim and brightenSecs to brighten
 *
 * Possible future constructors:
 *   Pulsate(period, model) - varies 0%-100% over the period in seconds, period is divided evenly between up and down
 *   Pulsate(dimmest, brightest, period, model) - varies between dimmest and brightest over the period
 *    
 * Requires underlying model
 * Position independent, time dependent
 */
class Pulsate : public Model {
  public:
    Pulsate(float dimmest, float brightest, float dimSecs, float brightenSecs, std::shared_ptr<Model> model)
      : Model("Pulsate"), model(std::move(model)), dimmest(dimmest), brightest(brightest),
        dimSecs(dimSecs), brightenSecs(brightenSecs), periodSecs(dimSecs + brightenSecs) {}
    void update(float timeStamp) override;
    Color render(float pos) override;
    void asJson(JsonObject obj) const override;

  private:
    float dimness = 0.0;

    float const dimmest;
    float const brightest;
    float const dimSecs;
    float const brightenSecs;
    float const periodSecs;
    std::shared_ptr<Model> model;
};
