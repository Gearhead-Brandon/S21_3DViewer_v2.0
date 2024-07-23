/**
 * @file Move.cpp
 * @brief Source file with implementing the class move strategy
 */

#include "Move.h"

namespace s21 {

/**
 * @brief The method executable the move transformation
 * @param vertices The vector of vertices
 * @param axis
 * @param value
 * @param center The center of the figure
 */
void MoveStrategy::executeTransformation(std::vector<float> &vertices,
                                         Axes axis, float value,
                                         Point<float> &center) {
  int axisIndex = static_cast<int>(axis);
  int size = vertices.size();

  for (int i = axisIndex; i < size; i += 3)
    vertices[i] += value;

  if (axis == Axes::X)
    center.x += value;

  if (axis == Axes::Y)
    center.y += value;

  if (axis == Axes::Z)
    center.z += value;
}
} // namespace s21