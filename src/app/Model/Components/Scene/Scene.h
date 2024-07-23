/**
 * @file Scene.h
 * @brief The header file describes the class Scene
 */

#ifndef SCENE_H
#define SCENE_H

#include "../../../Common/FacadeOpResult/FacadeOpResult.h"
#include "../AffineTransformations/Builder/AffineBuilder.h"
#include "../Figure/Figure.h"

namespace s21 {

/**
 * @brief Class describes the structure of the 3D Scene
 * @details Scene is need for the transformation of the figure
 */
class Scene {

  //! The figure of the 3D scene
  Figure figure_;

  //! The coefficient of the scale
  float scaleCoefficient_;

public:
  /**
   * @brief Constructor
   */
  Scene();

  /**
   * @brief Destructor
   */
  ~Scene() = default;

  /**
   * @brief The method returns the figure
   * @returns Figure&
   */
  Figure &getFigure();

  /**
   * @brief The method use affine transforms on the 3d figure
   * @param op The operation
   * @param axis The axis
   * @param value The value
   * @returns FacadeOpResult
   */
  FacadeOpResult transformFigure(AffineOps op, Axes axis, float value);

  /**
   * @brief The method resets the scene
   */
  void reset();
};
} // namespace s21

#endif