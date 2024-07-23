/**
 * @file Model.h
 * @brief The header file describes the class Model for working with the model
 */

#ifndef MODEL_H
#define MODEL_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <iostream>

#include "./Components/FileReader/FileReader.h"
#include "./Components/GifMaker/GifMaker.h"
#include "./Components/Scene/Scene.h"
#include "./Components/Settings/Settings.h"
#include <iostream>

#include "../Common/Observer/Observable/Observable.h"

namespace s21 {

/**
 * @brief The class Model for working with the model
 * @details Model implements the interface Observable
 */
class Model : public Observable {

  //! File reader for reading the .obj file
  IFileReader *fileReader_;

  //! Scene for working with the 3D model
  Scene scene_;

  //! Settings for the View
  Settings settings_;

  //! Gif maker for creating GIF animation
  GifMaker gifMaker_;

public:
  /**
   * @brief Constructor
   */
  Model();

  /**
   * @brief Destructor
   */
  ~Model();

  /**
   * @brief The method loads the .obj file
   * @param file_name The name of the .obj file
   * @returns FacadeOpResult
   */
  FacadeOpResult loadScene(const std::string &file_name);

  /**
   * @brief The method transforms the scene
   * @param op - affine operation type
   * @param axis - axis
   * @param value - value
   * @returns FacadeOpResult
   */
  FacadeOpResult transformScene(AffineOps op, Axes axis, float value);

  /**
   * @brief The method returns the 3D figure
   * @returns Figure&
   */
  Figure &getFigure();

  /**
   * @brief The method returns the number of vertices
   * @returns std::size_t
   */
  std::size_t getVerticesCount();

  /**
   * @brief The method returns the number of facets
   * @returns std::size_t
   */
  std::size_t getFacetsCount();

  /**
   * @brief The method returns the settings package
   * @returns SettingsPackage
   */
  const SettingsPackage &getSettingsPackage();

  /**
   * @brief The method sets the setting
   * @param setting - setting variant
   */
  void setSetting(const VariantSetting &setting);

  /**
   * @brief The method adds a frame to the GIF
   * @param frame
   */
  void addFrame(const QImage &frame);

  /**
   * @brief The method returns the name of the GIF
   * @param name - name of the GIF
   */
  void gifName(QString &name);

  /**
   * @brief The method checks the completion of the GIF
   * @returns true if the GIF is complete, false otherwise
   */
  bool gifComplete();
};
} // namespace s21

#endif