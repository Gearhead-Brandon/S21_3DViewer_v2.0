/**
 * @file CpuRenderStrategy.h
 * @brief Header file describing the class CpuRenderStrategy
 */

#ifndef CPU_RENDER_STRATEGY_H
#define CPU_RENDER_STRATEGY_H

#include "../IRenderStrategy/IRenderStrategy.h"

namespace s21 {
class IResourceProvider;
class SettingsPackage;

/**
 * @brief The class CpuRenderStrategy is used to render 3D models
 * @details The class CpuRenderStrategy is implementing the interface
 * IRenderStrategy
 */
class CpuRenderStrategy : public IRenderStrategy {

public:
  /**
   * @brief The method renders 3D model
   * @param widget The openGL widget
   */
  void render(OpenGLWidget &widget) override;

private:
  /**
   * @brief The method displays axes
   */
  void displayAxes();

  /**
   * @brief The method defines line type
   * @param settings - settings
   */
  void defineLineType(const SettingsPackage &settings);

  /**
   * @brief The method sets up projection
   * @param resourceProvider - resource provider
   */
  void setUpProjection(const IResourceProvider &resourceProvider);

  /**
   * @brief The method draws vertices
   * @param resourceProvider - resource provider
   */
  void drawVertices(const IResourceProvider &resourceProvider);
};
} // namespace s21

#endif