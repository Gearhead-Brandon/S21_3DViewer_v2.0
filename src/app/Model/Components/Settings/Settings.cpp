/**
 * @file Settings.cpp
 * @brief The source file with the implementation of the class Settings
 */

#include "Settings.h"

namespace s21 {
static const char *settingsNames[] = {
    "BackgroundColor", "VerticesColor", "EdgesColor", "LineType",
    "LineWidth",       "VertexType",    "PointSize",  "ProjectionType"};

/**
 * @brief The constructor
 */
Settings::Settings()
    : settings_(),
      settingsFilePath_(
          (QApplication::applicationDirPath() + "/settings/settings.ini")
              .toStdString()) {
  loadSettings();
}

/**
 * @brief Get current settings
 * @return current settings package
 */
const SettingsPackage &Settings::getSettingsPackage() { return settings_; }

/**
 * @brief Set new settings
 * @param newSetting - new settings
 */
void Settings::setSettings(const VariantSetting &newSetting) {
  QSettings qsettings(settingsFilePath_.c_str(), QSettings::NativeFormat);
  qsettings.beginGroup("Settings 3DViewer");

  switch (newSetting.getType()) {
    case SettingsType::BackgroundColor: {
      const RGB *color = newSetting.getValue<RGB>();
      settings_.background = *color;
      setColorSettings(settingsNames[0], qsettings, color);
      break;
    }
    case SettingsType::VerticesColor: {
      const RGB *color = newSetting.getValue<RGB>();
      settings_.vertices = *color;
      setColorSettings(settingsNames[1], qsettings, color);
      break;
    }
    case SettingsType::EdgesColor: {
      const RGB *color = newSetting.getValue<RGB>();
      settings_.edges = *color;
      setColorSettings(settingsNames[2], qsettings, color);
      break;
    }
    case SettingsType::LineType: {
      const LineType *type = newSetting.getValue<LineType>();
      settings_.lineType = *type;
      qsettings.setValue(settingsNames[3], static_cast<bool>(*type));
      break;
    }
    case SettingsType::LineWidth: {
      const std::size_t *width = newSetting.getValue<std::size_t>();
      settings_.lineWidth = *width;
      qsettings.setValue(settingsNames[4], static_cast<int>(*width));
      break;
    }
    case SettingsType::VertexType: {
      const VertexType *type = newSetting.getValue<VertexType>();
      settings_.vertexType = *type;
      qsettings.setValue(settingsNames[5], static_cast<int>(*type));
      break;
    }
    case SettingsType::PointSize: {
      const std::size_t *size = newSetting.getValue<std::size_t>();
      settings_.pointSize = *size;
      qsettings.setValue(settingsNames[6], static_cast<int>(*size));
      break;
    }
    case SettingsType::ProjectionType: {
      const ProjectionType *type = newSetting.getValue<ProjectionType>();
      settings_.projection = *type;
      qsettings.setValue(settingsNames[7], static_cast<bool>(*type));
      break;
    }
  }

  qsettings.endGroup();
  qsettings.sync();
}

/**
 * @brief Set color settings
 * @param name
 * @param settings
 * @param color
 */
void Settings::setColorSettings(const char *name, QSettings &settings,
                                const RGB *color) {
  settings.setValue(name, QVector3D{static_cast<float>(color->red),
                                    static_cast<float>(color->green),
                                    static_cast<float>(color->blue)});
}

/**
 * @brief Load settings
 * Load settings from settings file
 */
void Settings::loadSettings() {
  QSettings settings(settingsFilePath_.c_str(), QSettings::NativeFormat);
  settings.beginGroup("Settings 3DViewer");

  if (settings.contains(settingsNames[0])) {  // backgroundColor
    QVector3D color = settings.value(settingsNames[0]).value<QVector3D>();
    settings_.background = RGB{color.x(), color.y(), color.z()};
  }

  if (settings.contains(settingsNames[1])) {  // verticesColor
    QVector3D color = settings.value(settingsNames[1]).value<QVector3D>();
    settings_.vertices = RGB{color.x(), color.y(), color.z()};
  }

  if (settings.contains(settingsNames[2])) {  // edgesColor
    QVector3D color = settings.value(settingsNames[2]).value<QVector3D>();
    settings_.edges = RGB{color.x(), color.y(), color.z()};
  }

  if (settings.contains(settingsNames[3]))  // lineType
    settings_.lineType =
        static_cast<LineType>(settings.value(settingsNames[3]).toBool());

  if (settings.contains(settingsNames[4]))  // lineWidth
    settings_.lineWidth =
        static_cast<std::size_t>(settings.value(settingsNames[4]).toInt());

  if (settings.contains(settingsNames[5]))  // vertexType
    settings_.vertexType =
        static_cast<VertexType>(settings.value(settingsNames[5]).toInt());

  if (settings.contains(settingsNames[6]))  // pointSize
    settings_.pointSize =
        static_cast<std::size_t>(settings.value(settingsNames[6]).toInt());

  if (settings.contains(settingsNames[7]))  // projectionType
    settings_.projection =
        static_cast<ProjectionType>(settings.value(settingsNames[7]).toBool());

  settings.endGroup();
}
}  // namespace s21