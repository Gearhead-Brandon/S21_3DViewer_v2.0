/**
 * @file RGB.cpp
 * @brief Source file with implementing the structure RGB
 */

#include "RGB.h"

namespace s21 {

/**
 * @brief The default constructor of the structure RGB
 */
RGB::RGB() : red(0), green(0), blue(0) {}

/**
 * @brief The constructor of the structure RGB from three integer values
 */
RGB::RGB(int red, int green, int blue) : red(red), green(green), blue(blue) {}

/**
 * @brief The constructor of the structure RGB from three float values
 */
RGB::RGB(float red, float green, float blue)
    : red(static_cast<int>(red)), green(static_cast<int>(green)),
      blue(static_cast<int>(blue)) {}
} // namespace s21