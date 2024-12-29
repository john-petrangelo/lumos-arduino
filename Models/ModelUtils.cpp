#include <cstdlib>

#include "ModelUtils.h"

float frand(float const fmin, float const fmax) {
  // Scale the result of rand() to the range [fmin, fmax]
  float const random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  return fmin + random * (fmax - fmin);
}
