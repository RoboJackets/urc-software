#ifndef PREPROCESS_JOYSTICK_HPP_
#define PREPROCESS_JOYSTICK_HPP_

#include <algorithm>
struct PreProcessing
{
  static double clamp(double value, double m)
  {
    return std::min(m, std::max(value, -m));
  }

  static double invert(double value, bool invert)
  {
    return invert ? -value : value;
  }

  static double preprocess(double value, double m, bool inv)
  {
    return invert(clamp(value, m), inv);
  }
};

#endif  // !PREPROCESS_JOYSTICK_HPP_