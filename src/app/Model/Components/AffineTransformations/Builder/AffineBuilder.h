/**
 * @file AffineBuilder.h
 * @brief The header file describes the class AffineBuilder
 */

#ifndef AFFINE_BUILDER_H
#define AFFINE_BUILDER_H

#include "../../../../Common/Enum/AffineOps.h"
#include "../ITransformation/ITransformation.h"

namespace s21 {

/**
 * @brief The class makes the construction of the ITransformationStrategy
 * @details The class is used in the builder pattern
 */
class AffineBuilder {
 public:
  /**
   * @brief The default constructor
   */
  AffineBuilder() = default;

  /**
   * @brief The default destructor
   */
  ~AffineBuilder() = default;

  /**
   * @brief The method builds the ITransformationStrategy
   * @param op The type of the transformation
   * @returns ITransformationStrategy*
   */
  ITransformationStrategy *buildTransformStrategy(AffineOps op);
};
}  // namespace s21

#endif