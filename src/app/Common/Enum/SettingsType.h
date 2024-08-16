/**
 * @file SettingsType.h
 * @brief Header file describing enum of SettingsType
 */

#ifndef ENUM_SETTINGS_TYPE_H
#define ENUM_SETTINGS_TYPE_H

namespace s21 {

/**
 * @brief Enum of types of settings
 */
enum class SettingsType : int {
  BackgroundColor,
  VerticesColor,
  EdgesColor,
  LineType,
  LineWidth,
  VertexType,
  PointSize,
  ProjectionType
};
}  // namespace s21

#endif