/**
 * @file Settings.h
 * @brief The header file describes the class Settings
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QApplication>
#include <QSettings>
#include <QVector3D>

#include "../../../Common/Settings/SettingsPackage/SettingsPackage.h"
#include "../../../Common/Settings/VariantSetting/VariantSetting.h"

namespace s21 {

/**
 * @brief The class Settings is need to work with the settings package
 */
class Settings {
  //! Settings package
  SettingsPackage settings_;

  //! Settings file path
  std::string settingsFilePath_;

 public:
  /**
   * @brief The constructor
   */
  Settings();

  /**
   * @brief The destructor
   */
  ~Settings() = default;

  /**
   * @brief Set new settings
   * @param newSetting - new settings
   */
  void setSettings(const VariantSetting &newSetting);

  /**
   * @brief Get current settings
   * @return current settings package
   */
  const SettingsPackage &getSettingsPackage();

 private:
  /**
   * @brief Set color settings
   * @param name
   * @param settings
   * @param color
   */
  void setColorSettings(const char *name, QSettings &settings,
                        const RGB *color);

  /**
   * @brief Load settings
   * Load settings from settings file
   */
  void loadSettings();
};
}  // namespace s21

#endif