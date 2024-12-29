#pragma once

/**
 * Re-maps a number from one range to another. That is, a value of fromLow would get mapped to toLow,
 * a value of fromHigh to toHigh, values in-between to values in-between, etc.
 *
 * This is taken directly from the Arduino map function described here:
 * https://www.arduino.cc/reference/en/language/functions/math/map/
 * 
 * ...except it has been re-applied to floats instead of longs.
 */
inline float fmap(float const x, float const in_min, float const in_max, float const out_min, float const out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * Return a random float between fmin and fmax.
 */
float frand(float fmin, float fmax);

/**
 * Returns the sign of the given value as an integer.
 * - If the value is negative, returns -1.
 * - If the value is positive, returns 1.
 * - If the value is zero, returns 0.
 */
template <typename T>
T sign(T const val) {
  return (T(0) < val) - (val < T(0));
}
