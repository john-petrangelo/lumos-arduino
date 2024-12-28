#pragma once

#include <ArduinoJson.h>
#include <memory>

#include "lumos-arduino/Colors.h"

class Model {
  public:
    explicit Model(char const *name) : name(name) { }
    virtual ~Model() = default;

    // Updates the model to the current timestamp. Models that change with time (animations)
    // will need to implement this function. A default implementation is provided for static
    // models that do not change with time.
    virtual void update(float timeStamp) {}

    // Returns the color that should be displayed at the specified pos at the current time.
    virtual Color render(float pos) = 0;

    // Returns the name of this model, provided in the constructor.
    char const * getName() const { return name; }

    // Adds a description of the model to a JSON object, default behavior just adds the name
    virtual void asJson(JsonObject obj) const {
      if (!obj["name"].set(getName())) {
        obj["name"] = "<noname>";
      }
    }

protected:
    static void colorAsJson(JsonObject obj, Color c);

private:
    char const *name;
};
typedef std::shared_ptr<Model> ModelPtr;
