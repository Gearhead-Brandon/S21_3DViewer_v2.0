/*!
    @file
    @brief Source file describing class OpenGLWidget methods
*/
#include "OpenGLWidget.h"
#include <iostream>

namespace s21 {
/**
 * @brief Constructor of class
 */
OpenGLWidget::OpenGLWidget(IResourceProvider &resourceProvider)
    : QOpenGLWidget(nullptr), resourceProvider_(resourceProvider),
      renderStrategy_(RenderFactory().createRenderStrategy(RenderingType::NORMAL)),
      shaderProgram_(0), displayAxes_(Choice::Yes),
      renderingType_(RenderingType::NORMAL), xRot_(0.0f), yRot_(0.0f),
      scaleMouse_(1.0f) {}

/**
 * @brief Read shader file
 * @param filename - name of shader file
 * @return shader code
 * @details The function reads a shader file and returns its code
 */
std::string OpenGLWidget::readShaderFile(const char *filename) {
  std::ifstream file(filename);
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

/**
 * @brief Initialization of OpenGL
 */
void OpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_PROGRAM_POINT_SIZE);

  // Create and compile vertex shader
  QOpenGLShader vertexShader(QOpenGLShader::Vertex);
  vertexShader.compileSourceCode(
      readShaderFile("shaders/vertex_shader.glsl").c_str());

  // Create and compile fragment shader
  QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
  fragmentShader.compileSourceCode(
      readShaderFile("shaders/fragment_shader.glsl").c_str());

  // Create shader program and attach shaders
  shaderProgram_.addShader(&vertexShader);
  shaderProgram_.addShader(&fragmentShader);
  shaderProgram_.link();

  vertexShader.deleteLater();
  fragmentShader.deleteLater();
}

/**
 * @brief Resize OpenGL widget
 */
void OpenGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

/**
 * @brief Paint 3D model
 */
void OpenGLWidget::paintGL() {
  cleanUp();
  renderStrategy_->render(*this);
}

/**
 * @brief Clean up
 * @details The function cleans up old OpenGL environment
 */
void OpenGLWidget::cleanUp() {
  const SettingsPackage &settings = resourceProvider_.getSettingsPackage();

  glClearColor(settings.background.red / 256.0f,
               settings.background.green / 256.0f,
               settings.background.blue / 256.0f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * @brief Set up camera
 */
void OpenGLWidget::setUpCamera() {
  glRotatef(xRot_, 1, 0, 0);
  glRotatef(yRot_, 0, 1, 0);
  glScalef(scaleMouse_, scaleMouse_, scaleMouse_);
}

/**
 * @brief Set axes display
 */
void OpenGLWidget::setDisplayAxes(bool value) {
  displayAxes_ = static_cast<Choice>(!value);
  update();
}

/**
 * @brief Get axes display
 * @return axes display
 */
Choice OpenGLWidget::getDisplayAxes() { return displayAxes_; }

/**
 * @brief Set rendering type
 * @param type - rendering type
 */
void OpenGLWidget::setRenderingType(RenderingType type) {
  renderingType_ = type;

  delete renderStrategy_;
  RenderFactory factory;
  renderStrategy_ = factory.createRenderStrategy(renderingType_);

  update();
}

/**
 * @brief Get rendering type
 * @return rendering type
 */
RenderingType OpenGLWidget::getRenderingType() { return renderingType_; }

/**
 * @brief Get shader program
 * @return shader program
 */
QOpenGLShaderProgram &OpenGLWidget::getShaderProgram() {
  return shaderProgram_;
}

/**
 * @brief Get resource provider
 * @return resource provider
 */
IResourceProvider &OpenGLWidget::getResourceProvider() const {
  return resourceProvider_;
}

/**
 * @brief Update model when the model is changed
 */
void OpenGLWidget::update() { QOpenGLWidget::update(); }

/**
 * @brief Mouse press event
 * @param mo - mouse press event
 * @details Sets the mouse position
 */
void OpenGLWidget::mousePressEvent(QMouseEvent *mo) { mPos_ = mo->pos(); }

/**
 * @brief Mouse move event
 * @param mo Mouse move event
 * @details Sets the mouse move
 */
void OpenGLWidget::mouseMoveEvent(QMouseEvent *mo) {
  xRot_ = 1 / M_PI * (mo->pos().y() - mPos_.y());
  yRot_ = 1 / M_PI * (mo->pos().x() - mPos_.x());
  update();
}

/**
 * @brief Change scale model by wheel
 * @param factor Scale factor
 */
void OpenGLWidget::changeScale(float factor) {
  scaleMouse_ *= factor;
  update();
}

/**
 * @brief Mouse wheel event
 */
void OpenGLWidget::wheelEvent(QWheelEvent *event) {
  // Получить значение прокрутки колесика мыши
  int delta = event->angleDelta().y();

  // Определить множитель масштабирования на основе направления прокрутки
  float scaleFactor = 1.0f + 0.1f * (delta > 0 ? 1 : -1);

  // Изменить масштаб сцены
  changeScale(scaleFactor);
}
} // namespace s21