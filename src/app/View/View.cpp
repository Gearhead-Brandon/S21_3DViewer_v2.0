/**
 * @file View.cpp
 * @brief Source file with implementing class View methods
 */

#include "View.h"
#include "../Common/FacadeOpResult/FacadeOpResult.h"

namespace s21 {

/**
 * @brief Choosing a .obj file for loading the model
 */
void View::loadModel() {
  std::string path =
      QFileDialog::getOpenFileName(this, tr("Open File")).toStdString();
  if (path.empty())
    return;

  size_t dotPosition = path.find_last_of(".");
  if (dotPosition != std::string::npos && path.substr(dotPosition) != ".obj") {
    showErrorMessage("Is not obj file");
    return;
  }

  FacadeOpResult result = sceneLoader_.loadScene(path);

  if (!result.IsSuccess()) {
    showErrorMessage(result.getErrorMessage().c_str());
    return;
  };

  resetSliders();

  updateModelInfo(path);
}

/**
 * @brief Updating the information about the model
 * @param path path to the model
 */
void View::updateModelInfo(const std::string &path) {
  int vertices = sceneLoader_.getVerticesCount();
  int faces = sceneLoader_.getFacetsCount();

  std::string inf = "Model: " + path.substr(path.find_last_of('/') + 1) +
                    "\nVertices: " + std::to_string(vertices) +
                    "\nFaces: " + std::to_string(faces);

  QList<QTextEdit *> modelInfo = findChildren<QTextEdit *>();
  modelInfo[0]->setText(QString::fromUtf8(inf.c_str()));
}

/**
 * @brief Resetting the sliders to the default values
 */
void View::resetSliders() {
  lastMoveValue_ = {-100, -100, -100};
  lastRotationValue_ = {0, 0, 0};

  QList<QSlider *> sliders = findChildren<QSlider *>();

  std::for_each(sliders.begin(), sliders.end(), [](QSlider *slider) {
    if (slider->whatsThis() == "size slider")
      return;

    int value = 0;

    if (slider->whatsThis() == "scale slider")
      value = 5;

    slider->setValue(value);
  });
}

/**
 * @brief Show an error message
 * @param message The error message
 * @sa QMessageBox
 */
void View::showErrorMessage(const char *message) {
  QMessageBox msgBox;
  msgBox.setText(tr("Error"));
  msgBox.setInformativeText(tr(message));
  msgBox.setFont(QFont("Arial", 24));
  msgBox.setFixedSize(500, 200);
  msgBox.setIcon(QMessageBox::Critical);
  msgBox.exec();
}

/**
 * @brief Transforming the scene
 * @param op The operation
 * @param axis The axis
 * @param value The value
 */
void View::transformScene(AffineOps op, Axes axis, float value) {
  FacadeOpResult res = sceneLoader_.transformScene(op, axis, value);
}

/**
 * @brief Make a screenshot of the 3D model
 */
void View::makeScreenshot() {
  QScreen *screen = QGuiApplication::primaryScreen();
  QPixmap pixmap =
      screen->grabWindow(0, openGLWidget_.mapToGlobal(QPoint(0, 0)).x(),
                         openGLWidget_.mapToGlobal(QPoint(0, 0)).y(),
                         openGLWidget_.width(), openGLWidget_.height());

  QFileDialog dialog(nullptr, "Save Image", "image",
                     "JPEG (*.jpg);;BMP (*.bmp)");

  dialog.setAcceptMode(QFileDialog::AcceptSave);

  if (dialog.exec()) {
    QString filePath = dialog.selectedFiles().first();
    QString extension =
        QFileInfo(filePath).suffix(); // Получаем расширение файла

    QString selectedFilter =
        dialog.selectedNameFilter(); // Получаем выбранный фильтр

    if (extension.isEmpty()) {
      selectedFilter = dialog.selectedNameFilter(); // Получаем выбранный фильтр

      if (selectedFilter == "JPEG (*.jpg)")
        filePath += ".jpg";
      else if (selectedFilter == "BMP (*.bmp)")
        filePath += ".bmp";
    }

    pixmap.save(filePath, nullptr, 100);
  }

  dialog.deleteLater();
}

/**
 * @brief Start a creation of a GIF
 */
void View::onGifButton() {
  QString gifName = QFileDialog::getSaveFileName(
      this, tr("Save a gif animation"), "Screen Cast.gif", tr("gif (*.gif)"));

  if (!gifName.isEmpty()) {
    QList<QPushButton *> buttons = findChildren<QPushButton *>();
    (*std::find_if(buttons.begin(), buttons.end(), [](QPushButton *button) {
      return button->whatsThis() == "gif button";
    }))->setDisabled(true);

    sceneLoader_.gifName(gifName);

    QList<QTimer *> timers = findChildren<QTimer *>();
    timers[0]->setInterval(100);
    timers[0]->start();
  }
}

/**
 * @brief Make a GIF
 * @sa QTimer
 * @sa onGifButton()
 *
 * @details Called when the timer started in the onGifButton method expires.
 * Collects 50 screenshots, the timer stops and a GIF file is created.
 */
void View::makeGif() {
  QImage image = openGLWidget_.grabFramebuffer();
  QSize imageSize(640, 480);
  QImage scaledImage = image.scaled(imageSize);

  sceneLoader_.addFrame(scaledImage);

  if (sceneLoader_.gifComplete()) {
    QList<QTimer *> timers = findChildren<QTimer *>();
    timers[0]->stop();

    QList<QPushButton *> buttons = findChildren<QPushButton *>();
    (*std::find_if(buttons.begin(), buttons.end(), [](QPushButton *button) {
      return button->whatsThis() == "gif button";
    }))->setEnabled(true);
  }
}

/**
 * @brief Key press event handler for exit the application
 */
void View::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape)
    quit();
}

/**
 * @brief Quit the application
 */
void View::quit() { QApplication::quit(); }
} // namespace s21