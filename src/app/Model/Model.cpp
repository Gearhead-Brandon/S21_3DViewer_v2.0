#include "Model.h"

namespace s21 {

/**
 * @brief Constructor
 */
Model::Model()
    : fileReader_(new FileReader), scene_(), settings_(), gifMaker_() {}

/**
 * @brief Destructor
 */
Model::~Model() { delete fileReader_; }

/**
 * @brief The method loads the .obj file
 * @param file_name The name of the .obj file
 * @returns FacadeOpResult
 */
FacadeOpResult Model::loadScene(const std::string &path) {
  FacadeOpResult result = fileReader_->readScene(scene_.getFigure(), path);

  if (!result.IsSuccess()) return result;

  scene_.reset();

  notifyUpdate();

  return result;
}

/**
 * @brief The method returns the 3D figure
 * @returns Figure&
 */
Figure &Model::getFigure() { return scene_.getFigure(); }

/**
 * @brief The method returns the number of vertices
 * @returns std::size_t
 */
std::size_t Model::getVerticesCount() {
  return scene_.getFigure().getVertices().size() / 3;
}

/**
 * @brief The method returns the number of facets
 * @returns std::size_t
 */
std::size_t Model::getFacetsCount() {
  return scene_.getFigure().getFacetsCount();
}

/**
 * @brief The method transforms the scene
 * @param op - affine operation type
 * @param axis - axis
 * @param value - value
 * @returns FacadeOpResult
 */
FacadeOpResult Model::transformScene(AffineOps op, Axes axis, float value) {
  FacadeOpResult res = scene_.transformFigure(op, axis, value);
  if (!res.IsSuccess()) return res;

  notifyUpdate();

  return res;
}

/**
 * @brief The method returns the settings package
 * @returns SettingsPackage
 */
const SettingsPackage &Model::getSettingsPackage() {
  return settings_.getSettingsPackage();
}

/**
 * @brief The method sets the setting
 * @param setting - setting variant
 */
void Model::setSetting(const VariantSetting &setting) {
  settings_.setSettings(setting);
  notifyUpdate();
}

/**
 * @brief The method adds a frame to the GIF
 * @param frame
 */
void Model::addFrame(const QImage &frame) { gifMaker_.addFrame(frame); }

/**
 * @brief The method returns the name of the GIF
 * @param name - name of the GIF
 */
void Model::gifName(QString &name) { gifMaker_.gifName(name); }

/**
 * @brief The method checks the completion of the GIF
 * @returns true if the GIF is complete, false otherwise
 */
bool Model::gifComplete() { return gifMaker_.gifComplete(); }
}  // namespace s21