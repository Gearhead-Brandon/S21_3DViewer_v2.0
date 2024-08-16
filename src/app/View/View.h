/**
 * @file View.h
 * @brief Header file describing the class View
 */

#ifndef VIEW_H
#define VIEW_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "../Common/Structures/RGB/RGB.h"
#include "../Controller/Controller.h"
#include "./Components/ColorPicker/ColorPicker.h"
#include "./Components/OpenGLWidget/OpenGLWidget.h"
#include "./Components/Style/StylesTables.h"

namespace s21 {

/**
 * @brief View of the application
 */
class View : public QMainWindow {
  Q_OBJECT

  /**
   * @brief Data structure for the slider
   */
  typedef struct {
    //! Minimum value
    int min_value;

    //! Maximum value
    int max_value;

    //! Current value
    int current_value;
  } SliderData;

  //! Controller
  ISceneLoader &sceneLoader_;

  //! OpenGL Widget
  OpenGLWidget openGLWidget_;

  //! Last values of the sliders for moving and scaling
  Point<int> lastMoveValue_;

  //! Last values of the sliders for rotation
  Point<int> lastRotationValue_;

 public:
  /**
   * @brief Constructor
   * @param controller
   */
  View(Controller &controller);

  /**
   * @brief Destructor
   */
  ~View() = default;

 private:
  /**
   * @brief Painting background
   */
  void paintEvent(QPaintEvent *event) override;

  /**
   * @brief Creating a widget for rendering 3D models
   */
  void createOpenGLWidget();

  /**
   * @brief Creating a layout for the main window
   */
  QHBoxLayout *createBoxLayout();

  /**
   * @brief Creating a grid and attaching elements to it
   */
  QGridLayout *createControlPanel();

  /**
   * @brief Creating a Model Loader Box
   */
  void createModelLoadBox(QGridLayout *grid);

  /**
   * @brief Creating a Model Information
   */
  QTextEdit *createModelInfo();

  /**
   * @brief Adding a photo/gif recording of models
   */
  void createScreenshotGifMakeButtons(QGridLayout *grid);

  /**
   * @brief Adding a selection of Model Projection Type
   */
  void createProjectionSelectionBox(QGridLayout *grid);

  /**
   * @brief Adding axes drawing selection
   */
  void createDisplayAxesBox(QGridLayout *grid);

  /**
   * @brief Adding a Move and Scale slider
   */
  void createMoveScaleBox(QGridLayout *grid);

  /**
   * @brief Factory for the Move and Scale slider
   */
  QHBoxLayout *moveScaleBoxFactory(const char *name, SliderData &data,
                                   AffineOps op, Axes axis, float coefficient,
                                   int *last);

  /**
   * @brief Adding a Color Pickers for changing the color of the background,
   * edges and vertices
   */
  void createColorChoiceBoxex(QGridLayout *grid);

  /**
   * @brief Factory for the Color Picker
   */
  QHBoxLayout *colorPickerFactory(const char *name, SettingsType type);

  /**
   * @brief Adding a selection of Line Type
   */
  void createLineTypeSelectionBox(QGridLayout *grid);

  /**
   * @brief Adding a selection of Line/Point Size
   */
  void createLinePointSizeSelectionBox(QGridLayout *grid);

  /**
   * @brief Factory for the Line/Point Size
   */
  QHBoxLayout *linePointIncreaseBoxFactory(const char *name, int max_value,
                                           SettingsType type);

  /**
   * @brief Adding a sliders for rotation
   */
  void addRotationBoxes(QGridLayout *grid);

  /**
   * @brief Factory for the rotation slider
   */
  QHBoxLayout *rotationBoxFactory(const char *name, Axes axis, int &last);

  /**
   * @brief Adding an application exit button
   */
  void createQuitButton(QGridLayout *grid);

  /**
   * @brief Adding a selection of Vertex Type
   */
  void addVertexTypeSelectionBox(QGridLayout *grid);

  /**
   * @brief Choosing a .obj file for loading the model
   */
  void loadModel();

  /**
   * @brief Updating the information about the model
   * @param path path to the model
   */
  void updateModelInfo(const std::string &path);

  /**
   * @brief Resetting the sliders to the default values
   */
  void resetSliders();

  /**
   * @brief Transforming the scene
   * @param op The operation
   * @param axis The axis
   * @param value The value
   */
  void transformScene(AffineOps op, Axes axis, float value);

  /**
   * @brief Make a screenshot of the 3D model
   */
  void makeScreenshot();

  /**
   * @brief Start a creation of a GIF
   */
  void onGifButton();

  /**
   * @brief Make a GIF
   * @sa QTimer
   * @sa onGifButton()
   *
   * @details Called when the timer started in the onGifButton method expires.
   * Collects 50 screenshots, the timer stops and a GIF file is created.
   */
  void makeGif();

  /**
   * @brief Quit the application
   */
  void quit();

  /**
   * @brief Key press event handler for exit the application
   */
  void keyPressEvent(QKeyEvent *event) override;

  /**
   * @brief Show an error message
   * @param message The error message
   * @sa QMessageBox
   */
  void showErrorMessage(const char *message);
};
}  // namespace s21

#endif