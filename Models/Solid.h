#pragma once

#include "Model.h"

/*
 * Set a solid color pattern, invariant with time.
 */
class Solid;
typedef std::shared_ptr<Solid> SolidPtr;
class Solid : public Model {
  public:
    explicit Solid(Color color) : Model("Solid"), color(color) {}
    Color render(float pos) override { return color; }
    void asJson(JsonObject obj) const override {
      Model::asJson(obj);
      colorAsJson(obj["color"].to<JsonObject>(), color);
    };

    static SolidPtr make(Color c) { return std::make_shared<Solid>(c); }
  private:
    Color color;
};
