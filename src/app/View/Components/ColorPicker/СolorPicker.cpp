/**
 * @file СolorPicker.cpp
 * brief Source file with implementing of class ColorPicker methods
 */

#include "ColorPicker.h"

namespace s21 {

/**
 * @brief Constructor
 * @param parent The parent widget
 * @details Sets dimensions and specifies mouse position tracking
 */
ColorPicker::ColorPicker(QWidget *parent) : QWidget(parent) {
  setFixedSize(200, 200);
  setMouseTracking(true);
}

/**
 * @brief Mouse press event
 * @param event Press mouse event
 *
 * @details When click is happened on the widget with the mouse
 * it reads the color of the zone and writes it to the color variable.
 * And then emits a signal with the values of rgba variables.
 */
void ColorPicker::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    QColor color = pickColor(event->pos());
    RGB signal = {color.red(), color.green(), color.blue()};
    emit colorPickerClicked(signal);
  }
}

/**
 * @brief Paint event
 * @param event Paint event
 *
 * @details Fills the widget with a gradient obtained from the
 * createRainbowGradient() function in the form of a square.
 *
 * @sa createRainbowGradient()
 */
void ColorPicker::paintEvent([[maybe_unused]] QPaintEvent *event) {
  // Inner part
  QPainter painter(this);
  painter.fillRect(rect(), createRainbowGradient());

  // Border
  painter.setPen(QPen(Qt::black, 2));
  painter.drawRect(rect());
}

/**
 * @brief Pick color by mouse position
 * @param pos Mouse position
 * @return QColor picked
 *
 * @details the color of the pixel at the specified position as a QColor object
 */
QColor ColorPicker::pickColor(const QPoint &pos) {
  QPixmap pixmap = grab();
  return pixmap.toImage().pixelColor(pos);
}

/**
 * @brief Create rainbow gradient
 * @return Gradient
 *
 * @details Creates a left-to-right rainbow gradient in the form
 * of a QLinearGradient object.
 */
QLinearGradient ColorPicker::createRainbowGradient() {
  QLinearGradient gradient(rect().topLeft(), rect().topRight());
  gradient.setColorAt(0.0, Qt::red);
  gradient.setColorAt(0.16, Qt::yellow);
  gradient.setColorAt(0.33, Qt::green);
  gradient.setColorAt(0.50, Qt::cyan);
  gradient.setColorAt(0.67, Qt::blue);
  gradient.setColorAt(0.83, Qt::magenta);
  gradient.setColorAt(0.90, Qt::white);
  gradient.setColorAt(1.0, Qt::black);
  return gradient;
}
}  // namespace s21