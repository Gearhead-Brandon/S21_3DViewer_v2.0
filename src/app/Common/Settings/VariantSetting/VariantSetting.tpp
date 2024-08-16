/**
 * @file VariantSetting.tpp
 * @brief Source file with implementing the class VariantSetting
 */

#include "VariantSetting.h"

namespace s21 {

/**
 * @brief Constructor
 * @param type The type of setting
 * @param data The possible data of the setting
 */
template <typename T>
VariantSetting::VariantSetting(SettingsType type, const T &data)
    : type_(type), data_(data){};

/**
 * @brief Getter of the data
 * @return The possible data of the setting
 */
template <typename T>
const T *VariantSetting::getValue() const {
  return std::get_if<T>(&data_);
}
}  // namespace s21