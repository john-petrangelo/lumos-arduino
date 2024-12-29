#pragma once

#include <vector>

#include "Model.h"

/*
 * Set a gradient color pattern. The number of defined color points is variable.
 */
class Gradient;
typedef std::shared_ptr<Gradient> GradientPtr;

class Gradient : public Model {
  public:
    Gradient(std::initializer_list<uint32_t> colorArgs) : Model("Gradient"), colors(colorArgs) {}
    Color render(float pos) override;
    void asJson(JsonObject obj) const override;

    static GradientPtr make(Color const c1, Color const c2) {
      return std::make_shared<Gradient>(std::initializer_list<Color>{c1, c2});
    }
    static GradientPtr make(Color const c1, Color const c2, Color const c3) {
      return std::make_shared<Gradient>(std::initializer_list<Color>{c1, c2, c3});
    }
    static GradientPtr make(Color const c1, Color const c2, Color const c3, Color const c4) {
      return std::make_shared<Gradient>(std::initializer_list<Color>{c1, c2, c3, c4});
    }
    static GradientPtr make(Color const c1, Color const c2, Color const c3, Color const c4, Color const c5) {
      return std::make_shared<Gradient>(std::initializer_list<Color>{c1, c2, c3, c4, c5});
    }
    static GradientPtr make(Color const c1, Color const c2, Color const c3, Color const c4, Color const c5,
        Color const c6) {
      return std::make_shared<Gradient>(std::initializer_list<Color>{c1, c2, c3, c4, c5, c6});
    }
    static GradientPtr make(Color const c1, Color const c2, Color const c3, Color const c4, Color const c5,
        Color const c6, Color const c7) {
      return std::make_shared<Gradient>(std::initializer_list<Color>{c1, c2, c3, c4, c5, c6, c7});
    }
    static GradientPtr make(Color const c1, Color const c2, Color const c3, Color const c4, Color const c5,
        Color const c6, Color const c7, Color const c8) {
      return std::make_shared<Gradient>(std::initializer_list<Color>{c1, c2, c3, c4, c5, c6, c7, c8});
    }

  private:
    std::vector<Color> colors;
};
