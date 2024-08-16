/**
 * @file ISceneLoader.h
 * @brief Interface for class ISceneLoader
 */

#ifndef ISCENE_LOADER_H
#define ISCENE_LOADER_H

#include <string>

#include "../Enum/AffineOps.h"
#include "../Enum/Axes.h"
#include "../Settings/SettingsPackage/SettingsPackage.h"
#include "../Settings/VariantSetting/VariantSetting.h"

class QImage;
class QString;

namespace s21 {
class IObserver;
class FacadeOpResult;
/**
 * @brief Interface for class ISceneLoader
 * @details The class ISceneLoader is used to load model and transform scene
 */
class ISceneLoader {
 public:
  /**
   * @brief Virtual destructor
   */
  virtual ~ISceneLoader() = default;

  /**
   * @brief Add observer to Model
   * @param observer
   */
  virtual void addObserver(IObserver *observer) = 0;

  /**
   * @brief Load scene
   * @param path - path to obj file
   * @return FacadeOpResult
   */
  virtual FacadeOpResult loadScene(const std::string &path) = 0;

  /**
   * @brief Affine operations on scene
   * @param op - affine operation type
   * @param axis - axis
   * @param value - value
   * @return FacadeOpResult
   */
  virtual FacadeOpResult transformScene(AffineOps op, Axes axis,
                                        float value) = 0;

  /**
   * @brief Getter of vertices count
   * @return std::size_t
   */
  virtual std::size_t getVerticesCount() = 0;

  /**
   * @brief Setter of settings
   * @param setting
   */
  virtual void setSetting(const VariantSetting &setting) = 0;

  /**
   * @brief Getter of facets count
   * @return std::size_t
   * @details The method returns the number of polygons in the model
   */
  virtual std::size_t getFacetsCount() const = 0;

  /**
   * @brief Getter of settings
   * @return SettingsPackage
   */
  virtual const SettingsPackage &getSettingsPackage() const = 0;

  /**
   * @brief Add frame to gif animation
   * @param frame
   */
  virtual void addFrame(const QImage &frame) = 0;

  /**
   * @brief The method sets the name of the gif file
   * @param name
   */
  virtual void gifName(QString &name) = 0;

  /**
   * @brief The method tells whether the gif is complete
   */
  virtual bool gifComplete() = 0;
};
}  // namespace s21

#endif