/**
 * @file Controller.cpp
 * @brief Source file with implementing the class Controller
 */

#include "Controller.h"

namespace s21 {

/**
 * @brief Constructor
 * @param model Model reference
 */
Controller::Controller(Model &model) : model_(model) {}

///////////// IResourceProvider /////////////

/**
 * @brief The method returns the vector of vertices
 * @return std::vector<float>
 */
const std::vector<float> &Controller::getVertices() const {
  return model_.getFigure().getVertices();
}

/**
 * @brief The method returns the vector of indices
 * @return std::vector<unsigned>
 */
const std::vector<unsigned> &Controller::getIndices() const {
  return model_.getFigure().getIndices();
}

/**
 * @brief The method returns the vector of indices vertices
 * @return std::vector<unsigned>
 */
const std::vector<unsigned> &Controller::getIndicesVertices() const {
  return model_.getFigure().getIndicesVertices();
}

/**
 * @brief The method returns the max point
 * @return Point<float>
 */
const Point<float> &Controller::getMaxPoint() const {
  return model_.getFigure().getMaxPoint();
}

///////////// ISceneLoader //////////////

/**
 * @brief Add observer to Model
 * @param observer
 */
void Controller::addObserver(IObserver *observer) {
  model_.addObserver(observer);
}

/**
 * @brief Setter of settings
 * @param setting
 */
void Controller::setSetting(const VariantSetting &setting) {
  model_.setSetting(setting);
}

/**
 * @brief Load scene
 * @param path - path to obj file
 * @return FacadeOpResult
 */
FacadeOpResult Controller::loadScene(const std::string &path) {
  return model_.loadScene(path);
}

/**
 * @brief Getter of vertices count
 * @return std::size_t
 */
std::size_t Controller::getVerticesCount() { return model_.getVerticesCount(); }

/**
 * @brief Affine operations on scene
 * @param op - affine operation type
 * @param axis - axis
 * @param value - value
 * @return FacadeOpResult
 */
FacadeOpResult Controller::transformScene(AffineOps op, Axes axis,
                                          float value) {
  return model_.transformScene(op, axis, value);
}

/**
 * @brief Add frame to gif animation
 * @param frame
 */
void Controller::addFrame(const QImage &frame) { model_.addFrame(frame); }

/**
 * @brief The method sets the name of the gif file
 * @param name
 */
void Controller::gifName(QString &name) { model_.gifName(name); }

/**
 * @brief The method tells whether the gif is complete
 */
bool Controller::gifComplete() { return model_.gifComplete(); }

//////////////// Common /////////////////

/**
 * @brief Getter of facets count
 * @return std::size_t
 * @details The method returns the number of polygons in the model
 */
std::size_t Controller::getFacetsCount() const {
  return model_.getFacetsCount();
}

/**
 * @brief The method returns the settings package
 * @return SettingsPackage
 */
const SettingsPackage &Controller::getSettingsPackage() const {
  return model_.getSettingsPackage();
}
} // namespace s21