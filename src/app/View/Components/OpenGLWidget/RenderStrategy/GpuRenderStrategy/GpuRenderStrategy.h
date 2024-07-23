/**
 *  @file GpuRenderStrategy.h
 *  @brief Header file describing the class GpuRenderStrategy
 */

#ifndef GPU_RENDER_STRATEGY_H
#define GPU_RENDER_STRATEGY_H

#include "../IRenderStrategy/IRenderStrategy.h"
#include <GL/gl.h>
#include <vector>

namespace s21 {
class IResourceProvider;

/**
 * @brief The class GpuRenderStrategy is used to render 3D models
 * @details The class GpuRenderStrategy is implementing the interface
 * IRenderStrategy
 */
class GpuRenderStrategy : public IRenderStrategy {

public:
  /**
   * @brief The method renders 3D model
   * @param widget The openGL widget
   */
  void render(OpenGLWidget &widget) override;

private:
  /**
   * @brief The method sets up projection
   * @param resourceProvider - resource provider
   * @param projection - projection matrix
   */
  void setUpProjection(const IResourceProvider &resourceProvider,
                       float *projection);

  /**
   * @brief The method creates VBO
   * @param widget - openGL widget
   * @param vertices - vertices
   * @return VBO
   */
  GLuint createVBO(OpenGLWidget &widget, const std::vector<float> &vertices);

  /**
   * @brief The method creates EBO
   * @param widget - openGL widget
   * @param resourceProvider - resource provider
   * @return EBO
   */
  GLuint createEBO(OpenGLWidget &widget,
                   const IResourceProvider &resourceProvider);

  /**
   * @brief The method creates VAO
   * @param widget - openGL widget
   * @return VAO
   */
  GLuint createVAO(OpenGLWidget &widget);

  /**
   * @brief The method draws vertices
   * @param widget - openGL widget
   */
  void drawVertices(OpenGLWidget &widget);

  /**
   * @brief The method draws axes
   * @param widget - openGL widget
   */
  void drawAxes(OpenGLWidget &widget);

  /**
   * @brief Create orthographic projection matrix
   * @param left - left border
   * @param right - right border
   * @param bottom - bottom border
   * @param top - top border
   * @param nearPlane - near border
   * @param farPlane - far border
   * @param projectionMatrix - projection matrix
   */
  void createOrthographicProjectionMatrix(float left, float right, float bottom,
                                          float top, float nearPlane,
                                          float farPlane,
                                          float *projectionMatrix);

  /**
   * @brief Create perspective projection matrix
   * @param fov - field of view
   * @param aspectRatio - aspect ratio
   * @param nearPlane - near border
   * @param farPlane - far border
   * @param projectionMatrix - projection matrix
   *
   */
  void createPerspectiveProjectionMatrix(float fov, float aspectRatio,
                                         float nearPlane, float farPlane,
                                         float *projectionMatrix);
};
} // namespace s21

#endif