/**
 * @file ITransformation.h
 * @brief The header file describes the interface ITransformation
 */

#ifndef ITRANSFORMATIONS_H
#define ITRANSFORMATIONS_H

#include <vector>

#include "../../../../Common/Enum/Axes.h"
#include "../../../../Common/Structures/Point.h"

namespace s21 {

/**
 * @brief The class describes the interface ITransformation
 */
class ITransformationStrategy {
 public:
  /**
   * @brief The virtual destructor
   */
  virtual ~ITransformationStrategy() = default;

  /**
   * @brief The method executable the transformation
   * @param vertices The vector of vertices
   * @param axis
   * @param value
   * @param center The center of the figure
   */
  virtual void executeTransformation(std::vector<float> &vertices, Axes axis,
                                     float value, Point<float> &center) = 0;
};
}  // namespace s21

#endif