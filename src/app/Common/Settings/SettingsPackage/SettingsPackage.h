/**
 * @file SettingsPackage.h
 * @brief Header file describing the structure SettingsPackage
 */

#ifndef SETTINGS_PACKAGE_H
#define SETTINGS_PACKAGE_H

#include <iostream>

#include "../../Enum/LineType.h"
#include "../../Enum/ProjectionType.h"
#include "../../Enum/VertexType.h"
#include "../../Structures/RGB/RGB.h"

namespace s21 {

/**
 * @brief The structure SettingsPackage
 * @details The structure describes the settings package
 */
struct SettingsPackage {
  //! The background color
  RGB background;

  //! The vertices color
  RGB vertices;

  //! The edges color
  RGB edges;

  //! The line type
  LineType lineType;

  //! The line width
  std::size_t lineWidth;

  //! The vertex type
  VertexType vertexType;

  //! The point size
  std::size_t pointSize;

  //! The projection
  ProjectionType projection;

  /**
   * @brief The default constructor of the structure SettingsPackage
   */
  SettingsPackage();

  /**
   * @brief The destructor of the structure SettingsPackage
   */
  ~SettingsPackage() = default;
};
}  // namespace s21

#endif