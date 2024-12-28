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

    static GradientPtr make(Color c1, Color c2) {
      return std::make_shared<Gradient>(std::initializer_list<Color>{c1, c2});
    }
    static GradientPtr make(Color c1, Color c2, Color c3) {
      return std::make_shared<Gradient>(std::initializer_list<Color>{c1, c2, c3});
    }
    static GradientPtr make(Color c1, Color c2, Color c3, Color c4) {
      return std::make_shared<Gradient>(std::initializer_list<Color>{c1, c2, c3, c4});
    }
    static GradientPtr make(Color c1, Color c2, Color c3, Color c4, Color c5) {
      return std::make_shared<Gradient>(std::initializer_list<Color>{c1, c2, c3, c4, c5});
    }
    static GradientPtr make(Color c1, Color c2, Color c3, Color c4, Color c5, Color c6) {
      return std::make_shared<Gradient>(std::initializer_list<Color>{c1, c2, c3, c4, c5, c6});
    }
    static GradientPtr make(Color c1, Color c2, Color c3, Color c4, Color c5, Color c6, Color c7) {
      return std::make_shared<Gradient>(std::initializer_list<Color>{c1, c2, c3, c4, c5, c6, c7});
    }
    static GradientPtr make(Color c1, Color c2, Color c3, Color c4, Color c5, Color c6, Color c7, Color c8) {
      return std::make_shared<Gradient>(std::initializer_list<Color>{c1, c2, c3, c4, c5, c6, c7, c8});
    }

  private:
    std::vector<Color> colors;
};
