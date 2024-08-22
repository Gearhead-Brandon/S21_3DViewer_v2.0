#include "ShadersRenderStrategy.h"

#include "../../OpenGLWidget.h"

namespace s21 {

/**
 * @brief The method renders 3D model
 * @param widget The openGL widget
 */
void ShadersRenderStrategy::render(OpenGLWidget &widget) {
  const IResourceProvider &resourceProvider = widget.getResourceProvider();
  const std::vector<float> &vertices = resourceProvider.getVertices();
  if (vertices.empty()) return;

  const std::vector<unsigned> &indices = resourceProvider.getIndices();
  const SettingsPackage &settings = resourceProvider.getSettingsPackage();

  bool res = widget.getShaderProgram().bind();
  if (!res) return;

  GLuint VBO = createVBO(widget, vertices);
  GLuint EBO = createEBO(widget, resourceProvider);
  GLuint VAO = createVAO(widget);

  float projection[16] = {0.0f};
  setUpProjection(resourceProvider, projection);

  GLint projectionLocation = widget.glGetUniformLocation(
      widget.getShaderProgram().programId(), "projection");
  widget.glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projection);

  glLineWidth(settings.lineWidth);

  GLint lineTypeShader = widget.glGetUniformLocation(
      widget.getShaderProgram().programId(), "lineType");
  widget.glUniform1i(lineTypeShader, 0);

  drawVertices(widget);

  lineTypeShader = widget.glGetUniformLocation(
      widget.getShaderProgram().programId(), "lineType");
  widget.glUniform1i(lineTypeShader, static_cast<int>(settings.lineType));

  GLint edgeColorLocation = widget.glGetUniformLocation(
      widget.getShaderProgram().programId(), "fragmentColor");
  widget.glUniform3f(edgeColorLocation, settings.edges.red / 256.0f,
                     settings.edges.green / 256.0f,
                     settings.edges.blue / 256.0f);

  // Отрисовка линий
  glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, indices.data());

  widget.glDeleteBuffers(1, &VBO);

  if (widget.getDisplayAxes() == Choice::Yes) drawAxes(widget);

  widget.glBindVertexArray(0);
  widget.getShaderProgram().release();

  widget.glDeleteBuffers(1, &EBO);
  widget.glDeleteVertexArrays(1, &VAO);
}

/**
 * @brief The method creates VBO
 * @param widget - openGL widget
 * @param vertices - vertices
 * @return VBO
 */
GLuint ShadersRenderStrategy::createVBO(OpenGLWidget &widget,
                                        const std::vector<float> &vertices) {
  GLuint VBO = 0;
  widget.glGenBuffers(1, &VBO);
  widget.glBindBuffer(GL_ARRAY_BUFFER, VBO);
  widget.glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                      vertices.data(), GL_STATIC_DRAW);

  return VBO;
}

/**
 * @brief The method creates EBO
 * @param widget - openGL widget
 * @param resourceProvider - resource provider
 * @return EBO
 */
GLuint ShadersRenderStrategy::createEBO(
    OpenGLWidget &widget, const IResourceProvider &resourceProvider) {
  GLuint EBO = 0;
  widget.glGenBuffers(1, &EBO);
  widget.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  widget.glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                      resourceProvider.getFacetsCount() * sizeof(unsigned int),
                      resourceProvider.getIndices().data(), GL_STATIC_DRAW);

  return EBO;
}

/**
 * @brief The method creates VAO
 * @param widget - openGL widget
 * @return VAO
 */
GLuint ShadersRenderStrategy::createVAO(OpenGLWidget &widget) {
  GLuint VAO = 0;
  widget.glGenVertexArrays(1, &VAO);
  widget.glBindVertexArray(VAO);
  widget.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                               (void *)0);
  widget.glEnableVertexAttribArray(0);

  return VAO;
}

/**
 * @brief The method draws vertices
 * @param widget - openGL widget
 */
void ShadersRenderStrategy::drawVertices(OpenGLWidget &widget) {
  const IResourceProvider &resourceProvider = widget.getResourceProvider();
  const SettingsPackage &settings = resourceProvider.getSettingsPackage();

  if (settings.vertexType != VertexType::None) {
    const std::vector<unsigned> &indicesVertices =
        resourceProvider.getIndicesVertices();

    (settings.vertexType == VertexType::Circle) ? glEnable(GL_POINT_SMOOTH)
                                                : glDisable(GL_POINT_SMOOTH);

    GLint pointSizeShader = widget.glGetUniformLocation(
        widget.getShaderProgram().programId(), "pointSize");
    widget.glUniform1f(pointSizeShader, settings.pointSize);

    GLint vertexColorLocation = widget.glGetUniformLocation(
        widget.getShaderProgram().programId(), "fragmentColor");
    widget.glUniform3f(vertexColorLocation, settings.vertices.red / 256.0f,
                       settings.vertices.green / 256.0f,
                       settings.vertices.blue / 256.0f);

    glDrawElements(GL_POINTS, indicesVertices.size(), GL_UNSIGNED_INT,
                   indicesVertices.data());
  }
}

/**
 * @brief The method draws axes
 * @param widget - openGL widget
 */
void ShadersRenderStrategy::drawAxes(OpenGLWidget &widget) {
  std::vector<float> axisVertices = {
      0.0f, 0.0f, 0.0f, 1.5f, 0.0f, 0.0f,  // X
      0.0f, 0.0f, 0.0f, 0.0f, 1.5f, 0.0f,  // Y
      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.5f   // Z
  };

  // Создать новый буфер для вершин осей координат
  GLuint axisVBO = createVBO(widget, axisVertices);

  // Нарисовать вершины осей координат
  widget.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                               (void *)0);
  widget.glEnableVertexAttribArray(0);

  glLineWidth(1);

  GLint lineTypeShader = widget.glGetUniformLocation(
      widget.getShaderProgram().programId(), "lineType");
  widget.glUniform1i(lineTypeShader, static_cast<int>(LineType::Solid));

  // Установить uniform переменные для цветов в шейдере
  GLint colorLocation = widget.glGetUniformLocation(
      widget.getShaderProgram().programId(), "fragmentColor");

  // Нарисовать оси координат по очереди с разными цветами
  int numberOfVerticesForAxisX = 2;  // Количество вершин для оси X
  int numberOfVerticesForAxisY = 2;  // Количество вершин для оси Y
  int numberOfVerticesForAxisZ = 2;  // Количество вершин для оси Z

  // Нарисовать ось X (красный цвет)
  widget.glUniform3f(colorLocation, 1.0f, 0.0f,
                     0.0f);  // Красный цвет для оси X
  glDrawArrays(GL_LINES, 0, numberOfVerticesForAxisX);

  // Нарисовать ось Y (зеленый цвет)
  widget.glUniform3f(colorLocation, 0.0f, 1.0f,
                     0.0f);  // Зеленый цвет для оси Y
  glDrawArrays(GL_LINES, numberOfVerticesForAxisX, numberOfVerticesForAxisY);

  // Нарисовать ось Z (синий цвет)
  widget.glUniform3f(colorLocation, 0.0f, 0.0f, 1.0f);  // Синий цвет для оси Z
  glDrawArrays(GL_LINES, numberOfVerticesForAxisX + numberOfVerticesForAxisY,
               numberOfVerticesForAxisZ);

  // Удалить буфер вершин осей координат
  widget.glDeleteBuffers(1, &axisVBO);
}

/**
 * @brief The method sets up projection
 * @param resourceProvider - resource provider
 * @param projection - projection matrix
 */
void ShadersRenderStrategy::setUpProjection(
    const IResourceProvider &resourceProvider, float *projection) {
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
    createPerspectiveProjectionMatrix(fov_y, fW / fH, z_near, z_far,
                                      projection);
  } else if (settings.projection ==
             ProjectionType::Parallel)  // Parallel/Orthographic projection
    createOrthographicProjectionMatrix(-max_coordinate_, max_coordinate_,
                                       -max_coordinate_, max_coordinate_,
                                       -max_coordinate_, z_far, projection);
}

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
void ShadersRenderStrategy::createOrthographicProjectionMatrix(
    float left, float right, float bottom, float top, float nearPlane,
    float farPlane, float *projectionMatrix) {
  projectionMatrix[0] = 2.0f / (right - left);
  // projectionMatrix[1] = 0.0f;
  // projectionMatrix[2] = 0.0f;
  // projectionMatrix[3] = 0.0f;

  // projectionMatrix[4] = 0.0f;
  projectionMatrix[5] = 2.0f / (top - bottom);
  // projectionMatrix[6] = 0.0f;
  // projectionMatrix[7] = 0.0f;

  // projectionMatrix[8] = 0.0f;
  // projectionMatrix[9] = 0.0f;
  projectionMatrix[10] = -2.0f / (farPlane - nearPlane);
  // projectionMatrix[11] = 0.0f;

  projectionMatrix[12] = -(right + left) / (right - left);
  projectionMatrix[13] = -(top + bottom) / (top - bottom);
  projectionMatrix[14] = -(farPlane + nearPlane) / (farPlane - nearPlane);
  projectionMatrix[15] = 1.0f;
}

/**
 * @brief Create perspective projection matrix
 * @param fov - field of view
 * @param aspectRatio - aspect ratio
 * @param nearPlane - near border
 * @param farPlane - far border
 * @param projectionMatrix - projection matrix
 */
void ShadersRenderStrategy::createPerspectiveProjectionMatrix(
    float fov, float aspectRatio, float nearPlane, float farPlane,
    float *projectionMatrix) {
  float f = 1.0f / tan(fov * 0.5f);

  projectionMatrix[0] = f / aspectRatio;
  // projectionMatrix[1] = 0.0f;
  // projectionMatrix[2] = 0.0f;
  // projectionMatrix[3] = 0.0f;

  // projectionMatrix[4] = 0.0f;
  projectionMatrix[5] = f;
  // projectionMatrix[6] = 0.0f;
  // projectionMatrix[7] = 0.0f;

  // projectionMatrix[8] = 0.0f;
  // projectionMatrix[9] = 0.0f;
  projectionMatrix[10] = (farPlane + nearPlane) / (nearPlane - farPlane);
  projectionMatrix[11] = -1.0f;

  // projectionMatrix[12] = 0.0f;
  // projectionMatrix[13] = 0.0f;
  projectionMatrix[14] = (2.0f * farPlane * nearPlane) / (nearPlane - farPlane);
  // projectionMatrix[15] = 0.0f;
}
}  // namespace s21