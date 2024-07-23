/**
 * @file Scale.cpp
 * @brief The source file with implementing the scale strategy
 */

#include "Scale.h"

namespace s21 {

/**
 * @brief The method executable the scale transformation
 * @param vertices The vector of vertices
 * @param axis
 * @param value
 * @param center The center of the figure
 */
void ScaleStrategy::executeTransformation(std::vector<float> &vertices, Axes,
                                          float value, Point<float> &center) {
  int size = vertices.size();

  for (int i = 0; i < size; i += 3) {
    vertices[i] -= center.x;
    vertices[i + 1] -= center.y;
    vertices[i + 2] -= center.z;

    vertices[i] *= value;
    vertices[i + 1] *= value;
    vertices[i + 2] *= value;

    vertices[i] += center.x;
    vertices[i + 1] += center.y;
    vertices[i + 2] += center.z;
  }
}
} // namespace s21