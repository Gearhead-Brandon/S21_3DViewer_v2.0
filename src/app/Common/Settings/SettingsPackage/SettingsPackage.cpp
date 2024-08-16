/**
 * @file SettingsPackage.cpp
 * @brief Source file with implementing the structure SettingsPackage
 */

#include "SettingsPackage.h"

namespace s21 {

/**
 * @brief The default constructor of the structure SettingsPackage
 */
SettingsPackage::SettingsPackage()
    : background(255, 255, 255),
      vertices(),
      edges(),
      lineType{LineType::Solid},
      lineWidth{0},
      vertexType{VertexType::Square},
      pointSize{0},
      projection{ProjectionType::Central} {}
}  // namespace s21