/**
 * @file IRenderStrategy.h
 * @brief Header file describing the interface IRenderStrategy
 */

#ifndef IRENDER_STRATEGY_H
#define IRENDER_STRATEGY_H

namespace s21 {
class OpenGLWidget;

/**
 * @brief The interface IRenderStrategy is used to render 3D models
 */
class IRenderStrategy {
public:
  /**
   * @brief Virtual destructor
   */
  virtual ~IRenderStrategy() = default;

  /**
   * @brief The method renders 3D model
   * @param widget The openGL widget
   */
  virtual void render(OpenGLWidget &widget) = 0;
};
} // namespace s21

#endif