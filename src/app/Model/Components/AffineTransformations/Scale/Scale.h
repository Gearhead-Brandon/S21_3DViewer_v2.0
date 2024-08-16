/**
 * @file Scale.h
 * @brief The header file describes the class scale strategy
 */

#ifndef SCALING_FIGURE_H
#define SCALING_FIGURE_H

#include "../ITransformation/ITransformation.h"

namespace s21 {

/**
 * @brief The class describes the scale strategy
 *
 * The class implements the ITransformationStrategy interface
 */
class ScaleStrategy : public ITransformationStrategy {
 public:
  /**
   * @brief The method executable the scale transformation
   * @param vertices The vector of vertices
   * @param axis
   * @param value
   * @param center The center of the figure
   */
  void executeTransformation(std::vector<float> &vertices, Axes axis,
                             float value, Point<float> &center) override;
};
}  // namespace s21

#endif