/**
 * @file
 * @brief Header file describing the class for rendering 3D models using opengl
 */

#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <unistd.h>

#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QtOpenGLWidgets>
#include <fstream>
#include <vector>

#include "../../../Common/IController/IResourceProvider.h"
#include "../../../Common/Observer/IObserver.h"
#include "./RenderStrategy/RenderFactory/RenderFactory.h"
#include "Enum/Choice.h"
#include "Enum/RenderingType.h"

namespace s21 {

/**
 * @brief Class for rendering 3D models using opengl
 * @details Class implements the interface IObserver
 */
class OpenGLWidget : public QOpenGLWidget,
                     public QOpenGLFunctions_4_5_Core,
                     public IObserver {
  Q_OBJECT

  //! Resource provider
  IResourceProvider &resourceProvider_;

  //! Render strategy
  IRenderStrategy *renderStrategy_;

  //! OpenGL shader program
  QOpenGLShaderProgram shaderProgram_;

  //! Axes display
  Choice displayAxes_;

  //! Rendering type
  RenderingType renderingType_;

  //! Variable with x rotation value using mouse
  float xRot_;

  //! Variable with y rotation value using mouse
  float yRot_;

  //! Variable with mouse scaling value
  float scaleMouse_;

  //! Variable with mouse position
  QPoint mPos_;

 public:
  /**
   * @brief Constructor of class
   */
  OpenGLWidget(IResourceProvider &controller);

  /**
   * @brief Destructor of class
   */
  ~OpenGLWidget() = default;

  /**
   * @brief Set axes display
   */
  void setDisplayAxes(bool value);

  /**
   * @brief Get axes display
   * @return axes display
   */
  Choice getDisplayAxes();

  /**
   * @brief Set rendering type
   * @param type - rendering type
   */
  void setRenderingType(RenderingType type);

  /**
   * @brief Get rendering type
   * @return rendering type
   */
  RenderingType getRenderingType();

  /**
   * @brief Get shader program
   * @return shader program
   */
  QOpenGLShaderProgram &getShaderProgram();

  /**
   * @brief Get resource provider
   * @return resource provider
   */
  IResourceProvider &getResourceProvider() const;

  /**
   * @brief Set up camera
   */
  void setUpCamera();

 private:
  /**
   * @brief Clean up
   * @details The function cleans up old OpenGL environment
   */
  void cleanUp();

  /**
   * @brief Read shader file
   * @param filename - name of shader file
   * @return shader code
   * @details The function reads a shader file and returns its code
   */
  std::string readShaderFile(const char *filename);

  /**
   * @brief Initialization of OpenGL
   */
  void initializeGL() override;

  /**
   * @brief Resize OpenGL widget
   */
  void resizeGL(int w, int h) override;

  /**
   * @brief Paint 3D model
   */
  void paintGL() override;

  /**
   * @brief Mouse press event
   * @param mo - mouse press event
   * @details Sets the mouse position
   */
  void mousePressEvent(QMouseEvent *mo) override;

  /**
   * @brief Mouse move event
   * @param mo Mouse move event
   * @details Sets the mouse move
   */
  void mouseMoveEvent(QMouseEvent *mo) override;

  /**
   * @brief Mouse wheel event
   */
  void wheelEvent(QWheelEvent *event) override;

  /**
   * @brief Change scale model by wheel
   * @param factor Scale factor
   */
  void changeScale(float factor);

  /**
   * @brief Update model when the model is changed
   */
  void update() override;
};
}  // namespace s21

#endif