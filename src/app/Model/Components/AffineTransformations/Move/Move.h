/**
 * @file Move.h
 * @brief The header file describes the class move strategy
 */

#ifndef MOVE_FIGURE_H
#define MOVE_FIGURE_H

#include "../ITransformation/ITransformation.h"

namespace s21 {

/**
 * @brief The class describes the move strategy
 *
 * Class implements the ITransformationStrategy interface
 */
class MoveStrategy : public ITransformationStrategy {
 public:
  /**
   * @brief The method executable the move transformation
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