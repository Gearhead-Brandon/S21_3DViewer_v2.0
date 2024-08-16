/**
 * @file VariantSetting.h
 * @brief Header file describing the class VariantSetting
 */

#ifndef VARIANT_SETTING_H
#define VARIANT_SETTING_H

#include <iostream>
#include <variant>

#include "../../Enum/SettingsType.h"
#include "../SettingsPackage/SettingsPackage.h"

namespace s21 {

/**
 * @brief The class describes the variant setting
 */
class VariantSetting {
  //! The type of setting
  SettingsType type_;

  //! The possible data of the setting
  std::variant<RGB, std::size_t, LineType, VertexType, ProjectionType> data_;

 public:
  /**
   * @brief Constructor
   * @param type The type of setting
   * @param data The possible data of the setting
   */
  template <typename T>
  VariantSetting(SettingsType type, const T &data);

  /**
   * @brief Destructor
   */
  ~VariantSetting() = default;

  /**
   * @brief Getter of the data
   * @return The possible data of the setting
   */
  template <typename T>
  const T *getValue() const;

  /**
   * @brief Getter of the type
   * @return The type of setting
   */
  SettingsType getType() const { return type_; }
};
}  // namespace s21

#include "VariantSetting.tpp"

#endif