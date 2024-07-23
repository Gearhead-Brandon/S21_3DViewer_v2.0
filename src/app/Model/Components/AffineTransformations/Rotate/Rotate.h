/**
 * @file Rotate.h
 * @brief The header file describes the class rotate strategy
 */

#ifndef ROTATION_FIGURE_H
#define ROTATION_FIGURE_H

#include "../ITransformation/ITransformation.h"

namespace s21 {

/**
 * @brief The class describes the rotate strategy
 *
 * Class implements the ITransformationStrategy interface
 */
class RotateStrategy : public ITransformationStrategy {
public:
  /**
   * @brief The method executable the rotation transformation
   * @param vertices The vector of vertices
   * @param axis
   * @param value
   * @param center The center of the figure
   */
  void executeTransformation(std::vector<float> &vertices, Axes axis,
                             float value, Point<float> &center) override;
};
} // namespace s21

#endif