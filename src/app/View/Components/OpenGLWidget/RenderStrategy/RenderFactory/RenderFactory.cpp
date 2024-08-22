/**
 *  @file RenderFactory.cpp
 *  @brief Header file implementing the class RenderFactory
 */

#include "RenderFactory.h"

#include "../../OpenGLWidget.h"

namespace s21 {

/**
 * @brief The method creates render strategy
 * @param type - rendering type
 * @return IRenderStrategy*
 */
IRenderStrategy *RenderFactory::createRenderStrategy(RenderingType type) {
  switch (type) {
    case RenderingType::DEFAULT:
      return new DefaultRenderStrategy();
    case RenderingType::SHADERS:
      return new ShadersRenderStrategy();
    default:
      break;
  }

  return nullptr;
}
}  // namespace s21