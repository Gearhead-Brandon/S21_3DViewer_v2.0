/**
 * @file Controller.h
 * @brief Header file describing the class Controller
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>

#include "../Common/IController/IResourceProvider.h"
#include "../Common/IController/ISceneLoader.h"
#include "../Common/Observer/IObserver.h"
#include "../Model/Model.h"

namespace s21 {

/**
 * @brief The class Controller is used to load the model and transform the scene
 * @details The Controller class is used to load the model and transform the
 * scene as a layer between the view and the model
 */
class Controller : public IResourceProvider, public ISceneLoader {
  //! Model reference
  Model &model_;

 public:
  /**
   * @brief Constructor
   * @param model Model reference
   */
  Controller(Model &model);

  /**
   * @brief Destructor
   */
  ~Controller() override{};

  ///////////////// IResourceProvider /////////////

  /**
   * @brief The method returns the vector of vertices
   * @return std::vector<float>
   */
  const std::vector<float> &getVertices() const override;

  /**
   * @brief The method returns the vector of indices
   * @return std::vector<unsigned>
   */
  const std::vector<unsigned> &getIndices() const override;

  /**
   * @brief The method returns the vector of indices vertices
   * @return std::vector<unsigned>
   */
  const std::vector<unsigned> &getIndicesVertices() const override;

  /**
   * @brief The method returns the max point
   * @return Point<float>
   */
  const Point<float> &getMaxPoint() const override;

  ///////////////// ISceneLoader /////////////

  /**
   * @brief Add observer to Model
   * @param observer
   */
  void addObserver(IObserver *observer) override;

  /**
   * @brief Setter of settings
   * @param setting
   */
  void setSetting(const VariantSetting &setting) override;

  /**
   * @brief Load scene
   * @param path - path to obj file
   * @return FacadeOpResult
   */
  FacadeOpResult loadScene(const std::string &path) override;

  /**
   * @brief Affine operations on scene
   * @param op - affine operation type
   * @param axis - axis
   * @param value - value
   * @return FacadeOpResult
   */
  FacadeOpResult transformScene(AffineOps op, Axes axis, float value) override;

  /**
   * @brief Getter of vertices count
   * @return std::size_t
   */
  std::size_t getVerticesCount() override;

  /**
   * @brief Add frame to gif animation
   * @param frame
   */
  void addFrame(const QImage &frame) override;

  /**
   * @brief The method sets the name of the gif file
   * @param name
   */
  void gifName(QString &name) override;

  /**
   * @brief The method tells whether the gif is complete
   */
  bool gifComplete() override;

  ///////////////// Common ///////////////////

  /**
   * @brief Getter of facets count
   * @return std::size_t
   * @details The method returns the number of polygons in the model
   */
  std::size_t getFacetsCount() const override;

  /**
   * @brief The method returns the settings package
   * @return SettingsPackage
   */
  const SettingsPackage &getSettingsPackage() const override;
};
}  // namespace s21

#endif