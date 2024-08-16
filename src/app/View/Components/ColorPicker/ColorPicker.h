/**
 * @file ColorPicker.h
 * @brief Header file describing the class ColorPicker
 */

#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QtWidgets>

#include "../../../Common/Structures/RGB/RGB.h"

namespace s21 {

/**
 * @brief Class ColorPicker is used to pick color by mouse
 */
class ColorPicker : public QWidget {
  Q_OBJECT

 signals:

  /**
   * @brief Signal emitted when color is picked
   * @param red Red color
   * @param green Green color
   * @param blue Blue color
   * @param alpha Alpha value
   */
  void colorPickerClicked(RGB color);

 public:
  /**
   * @brief Constructor
   * @param parent The parent widget
   * @details Sets dimensions and specifies mouse position tracking
   */
  ColorPicker(QWidget *parent);

 private:
  /**
   * @brief Mouse press event
   * @param event Press mouse event
   *
   * @details When click is happened on the widget with the mouse
   * it reads the color of the zone and writes it to the color variable.
   * And then emits a signal with the values of rgba variables.
   */
  void mousePressEvent(QMouseEvent *event) override;

  /**
   * @brief Paint event
   * @param event Paint event
   *
   * @details Fills the widget with a gradient obtained from the
   * createRainbowGradient() function in the form of a square.
   *
   * @sa createRainbowGradient()
   */
  void paintEvent(QPaintEvent *event) override;

  /**
   * @brief Pick color by mouse position
   * @param pos Mouse position
   * @return QColor picked
   *
   * @details the color of the pixel at the specified position as a QColor
   * object
   */
  QColor pickColor(const QPoint &pos);

  /**
   * @brief Create rainbow gradient
   * @return Gradient
   *
   * @details Creates a left-to-right rainbow gradient in the form
   * of a QLinearGradient object.
   */
  QLinearGradient createRainbowGradient();
};
}  // namespace s21

#endif