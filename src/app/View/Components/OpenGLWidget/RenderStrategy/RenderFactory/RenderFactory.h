/**
 *  @file RenderFactory.h
 *  @brief Header file describing the class RenderFactory
 */

#ifndef RENDER_FACTORY_H
#define RENDER_FACTORY_H

#include "../../Enum/RenderingType.h"
#include "../CpuRenderStrategy/CpuRenderStrategy.h"
#include "../GpuRenderStrategy/GpuRenderStrategy.h"

namespace s21 {

/**
 * @brief The class RenderFactory is used to create render strategies
 */
class RenderFactory {
 public:
  /**
   * @brief The destructor
   */
  ~RenderFactory() = default;

  /**
   * @brief The method creates render strategy
   * @param type - rendering type
   * @return IRenderStrategy*
   */
  IRenderStrategy *createRenderStrategy(RenderingType type);
};
}  // namespace s21

#endif