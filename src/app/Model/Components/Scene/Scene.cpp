/**
 * @file Scene.cpp
 * @brief The source file with implementing the class Scene
 */

#include "Scene.h"

#include <iostream>

namespace s21 {

/**
 * @brief Constructor
 */
Scene::Scene() : figure_(), scaleCoefficient_(0.5) {}

/**
 * @brief The method resets the scene
 */
void Scene::reset() { scaleCoefficient_ = 0.5; }

/**
 * @brief The method returns the figure
 * @returns Figure&
 */
Figure &Scene::getFigure() { return figure_; }

/**
 * @brief The method use affine transforms on the 3d figure
 * @param op The operation
 * @param axis The axis
 * @param value The value
 * @returns FacadeOpResult
 */
FacadeOpResult Scene::transformFigure(AffineOps op, Axes axis, float value) {
  if (figure_.getVertices().empty())
    return FacadeOpResult(false, "Figure does not loaded");

  if (op == AffineOps::Scaling) {
    value /= 10;
    float temp = value / scaleCoefficient_;
    scaleCoefficient_ = value;
    value = temp;
  }

  AffineBuilder builder;
  ITransformationStrategy *strategy = builder.buildTransformStrategy(op);

  figure_.setTransformStrategy(strategy);

  figure_.executeTransformStrategy(axis, value);

  return FacadeOpResult(true, "Figure transformed");
}
}  // namespace s21