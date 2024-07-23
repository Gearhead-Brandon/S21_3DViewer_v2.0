/**
 * @file Rotate.cpp
 * @brief Source file with implementing the class rotate strategy
 */

#include "Rotate.h"
#include <cmath>

namespace s21 {

/**
 * @brief The method executable the rotation transformation
 * @param vertices The vector of vertices
 * @param axis
 * @param value
 * @param center The center of the figure
 */
void RotateStrategy::executeTransformation(std::vector<float> &vertices,
                                           Axes axis, float value,
                                           Point<float> &center) {
  int size = vertices.size();
  float x, y, z, cosV, sinV;
  value = value * M_PI / 180.0;

  cosV = cos(value);
  sinV = sin(value);

  float cX = center.x, cY = center.y, cZ = center.z;

  if (axis == Axes::X)
    for (int i = 0; i < size; i += 3) {
      y = vertices[i + 1] - cY;
      z = vertices[i + 2] - cZ;

      vertices[i + 1] = y * cosV - z * sinV;
      vertices[i + 2] = y * sinV + z * cosV;

      vertices[i + 1] += cY;
      vertices[i + 2] += cZ;
    }

  if (axis == Axes::Y)
    for (int i = 0; i < size; i += 3) {
      x = vertices[i] - cX;
      z = vertices[i + 2] - cZ;

      vertices[i] = x * cosV + z * sinV;
      vertices[i + 2] = -x * sinV + z * cosV;

      vertices[i] += cX;
      vertices[i + 2] += cZ;
    }

  if (axis == Axes::Z)
    for (int i = 0; i < size; i += 3) {
      x = vertices[i] - cX;
      y = vertices[i + 1] - cY;

      vertices[i] = x * cosV - y * sinV;
      vertices[i + 1] = x * sinV + y * cosV;

      vertices[i] += cX;
      vertices[i + 1] += cY;
    }
}
} // namespace s21