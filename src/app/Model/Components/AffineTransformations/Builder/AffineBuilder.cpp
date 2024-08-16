/**
 * @file AffineBuilder.cpp
 * @brief The source file with the implementation of the class AffineBuilder
 */

#include "AffineBuilder.h"

#include "../Move/Move.h"
#include "../Rotate/Rotate.h"
#include "../Scale/Scale.h"

namespace s21 {

/**
 * @brief The method builds the ITransformationStrategy
 * @param op The type of the transformation
 * @returns ITransformationStrategy*
 */
auto AffineBuilder::buildTransformStrategy(AffineOps op)
    -> ITransformationStrategy* {
  switch (op) {
    case AffineOps::Moving:
      return new MoveStrategy();
    case AffineOps::Rotation:
      return new RotateStrategy();
    case AffineOps::Scaling:
      return new ScaleStrategy();
    default:
      break;
  }

  return nullptr;
}
}  // namespace s21