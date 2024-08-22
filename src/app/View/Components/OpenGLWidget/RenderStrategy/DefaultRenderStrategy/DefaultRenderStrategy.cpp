/**
 *  @file DefaultRenderStrategy.cpp
 *  @brief Source file implementing the class DefaultRenderStrategy
 */

#include "DefaultRenderStrategy.h"

#include "../../OpenGLWidget.h"

namespace s21 {

/**
 * @brief The method renders 3D model
 * @param widget The openGL widget
 */
void DefaultRenderStrategy::render(OpenGLWidget &widget) {
  const IResourceProvider &resourceProvider = widget.getResourceProvider();
  const std::vector<float> &vertices = resourceProvider.getVertices();
  if (vertices.empty()) return;

  const std::vector<unsigned> &indices = resourceProvider.getIndices();
  const SettingsPackage &settings = resourceProvider.getSettingsPackage();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  setUpProjection(resourceProvider);

  glLineWidth(settings.lineWidth);

  defineLineType(settings);

  widget.setUpCamera();

  glVertexPointer(3, GL_FLOAT, 0, vertices.data());

  glPointSize(settings.pointSize);

  glEnableClientState(GL_VERTEX_ARRAY);
  //////////////////////////////////////////
  glColor3f(settings.edges.red / 256.0f, settings.edges.green / 256.0f,
            settings.edges.blue / 256.0f);

  // Отрисовка ребер
  glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, indices.data());

  // Отрисовка вершин
  drawVertices(resourceProvider);

  if (widget.getDisplayAxes() == Choice::Yes) displayAxes();
  //////////////////////////////////////////
  glDisableClientState(GL_VERTEX_ARRAY);
}

/**
 * @brief The method draws vertices
 * @param resourceProvider - resource provider
 */
void DefaultRenderStrategy::drawVertices(
    const IResourceProvider &resourceProvider) {
  const SettingsPackage &settings = resourceProvider.getSettingsPackage();
  const std::vector<float> &vertices = resourceProvider.getVertices();
  const std::vector<unsigned> &indicesVertices =
      resourceProvider.getIndicesVertices();

  if (settings.vertexType == VertexType::None) return;

  (settings.vertexType == VertexType::Circle) ? glEnable(GL_POINT_SMOOTH)
                                              : glDisable(GL_POINT_SMOOTH);

  glColor3f(settings.vertices.red / 256.0f, settings.vertices.green / 256.0f,
            settings.vertices.blue / 256.0f);

  // Отрисовка вершин
  glDrawElements(GL_POINTS, vertices.size() / 3, GL_UNSIGNED_INT,
                 indicesVertices.data());
}

/**
 * @brief The method defines line type
 * @param settings - settings
 */
void DefaultRenderStrategy::defineLineType(const SettingsPackage &settings) {
  if (settings.lineType == LineType::Stipple) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(4, 0xAAAA);
  } else
    glDisable(GL_LINE_STIPPLE);
}

/**
 * @brief The method displays axes
 */
void DefaultRenderStrategy::displayAxes() {
  glEnableClientState(GL_COLOR_ARRAY);
  GLfloat verticesAxis[] = {
      0.0f, 0.0f, 0.0f,  // Начало
      1.5f, 0.0f, 0.0f,  // Конец X
      0.0f, 0.0f, 0.0f,  // Начало
      0.0f, 1.5f, 0.0f,  // Конец Y
      0.0f, 0.0f, 0.0f,  // Начало
      0.0f, 0.0f, 1.5f   // Конец Z
  };

  GLfloat colorsAxis[] = {1.0f, 0.0f, 0.0f,                    // X
                          1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // Y
                          0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // Z
                          0.0f, 0.0f, 1.0f};

  GLuint indicesAxis[] = {0, 1, 1, 0, 2, 3, 3, 2, 4, 5, 5, 4};

  glLineWidth(1);
  glDisable(GL_LINE_STIPPLE);

  glVertexPointer(3, GL_FLOAT, 0, verticesAxis);
  glColorPointer(3, GL_FLOAT, 0, colorsAxis);
  glDrawElements(GL_LINES, 12, GL_UNSIGNED_INT, indicesAxis);
  glDisableClientState(GL_COLOR_ARRAY);
}

/**
 * @brief The method sets up projection
 * @param resourceProvider - resource provider
 */
void DefaultRenderStrategy::setUpProjection(
    const IResourceProvider &resourceProvider) {
  const Point<float> &max = resourceProvider.getMaxPoint();

  double max_coordinate_ = std::max(max.x, std::max(max.y, max.z));

  if (max_coordinate_ < 1) max_coordinate_ = 2;

  // Ближнее расстояние отсечения
  GLdouble z_near = 0.001;

  // Дальнее расстояние отсечения
  GLdouble z_far = max_coordinate_ * 10;

  const SettingsPackage &settings = resourceProvider.getSettingsPackage();

  if (settings.projection ==
      ProjectionType::Central) {  // Central/Perspective projection
    // Поле зрения в градусах по оси y
    GLdouble fov_y = 90;
    GLdouble fH = tan(fov_y / 360 * M_PI) * z_near;
    GLdouble fW = fH;
    glFrustum(-fW, fW, -fH, fH, z_near, z_far);
    glTranslated(0, 0, -3);
  } else if (settings.projection ==
             ProjectionType::Parallel) {  // Parallel/Orthographic projection
    glOrtho(-max_coordinate_, max_coordinate_, -max_coordinate_,
            max_coordinate_, -max_coordinate_, z_far);
    glTranslated(0, 0, -3);
  }
}
}  // namespace s21