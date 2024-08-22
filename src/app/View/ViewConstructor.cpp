/**
 * @file ViewConstructor.cpp
 * Source file with implementing constructor of class View
 */

#include "View.h"

namespace s21 {

/**
 * @brief Constructor
 * @param controller
 */
View::View(Controller &controller)
    : QMainWindow(),
      sceneLoader_(controller),
      openGLWidget_(controller),
      lastMoveValue_{0, 0, 0},
      lastRotationValue_{0, 0, 0} {
  setWindowTitle(tr("3DViewer"));
  setGeometry(100, 100, 1100, 600);
  setStyleSheet(FontStyle);

  createOpenGLWidget();

  QGridLayout *ActionTabs = createControlPanel();

  QHBoxLayout *box = createBoxLayout();
  box->addWidget(&openGLWidget_);
  box->addLayout(ActionTabs);

  QWidget *centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);
  centralWidget->setLayout(box);
}

/**
 * @brief Painting background
 */
void View::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  char path[] = "./img/background.jpeg";
  painter.drawPixmap(openGLWidget_.width(), 0, width(), height(),
                     QPixmap(path));
}

/**
 * @brief Creating a widget for rendering 3D models
 */
void View::createOpenGLWidget() {
  sceneLoader_.addObserver(&openGLWidget_);

  QSizePolicy openGLWidgetSizePolicy(QSizePolicy::Expanding,
                                     QSizePolicy::Expanding);
  openGLWidget_.setSizePolicy(openGLWidgetSizePolicy);
}

/**
 * @brief Creating a grid and attaching elements to it
 */
QGridLayout *View::createControlPanel() {
  QGridLayout *grid = new QGridLayout;

  grid->setColumnMinimumWidth(1, 200);
  grid->setColumnStretch(1, 0);

  createModelLoadBox(grid);
  createScreenshotGifMakeButtons(grid);
  createProjectionSelectionBox(grid);
  createDisplayAxesBox(grid);

  createMoveScaleBox(grid);
  addRotationBoxes(grid);

  createColorChoiceBoxex(grid);
  createLineTypeSelectionBox(grid);
  createLinePointSizeSelectionBox(grid);
  createQuitButton(grid);
  addVertexTypeSelectionBox(grid);

  return grid;
}

/**
 * @brief Creating a layout for the main window
 */
QHBoxLayout *View::createBoxLayout() {
  QHBoxLayout *box = new QHBoxLayout;

  box->setContentsMargins(0, 0, 0, 0);
  box->setSpacing(1);
  box->setAlignment(Qt::AlignTop);
  box->setStretch(0, 1);
  box->setStretch(1, 1);

  return box;
}

/**
 * @brief Creating a Model Loader Box
 */
void View::createModelLoadBox(QGridLayout *grid) {
  QPushButton *button = new QPushButton(tr("Load model"));
  button->setStyleSheet(LoadButtonStyle);
  button->setToolTip("Загрузить модель из obj файла");

  connect(button, &QPushButton::clicked, this, &View::loadModel);

  QVBoxLayout *box = new QVBoxLayout;

  box->addWidget(createModelInfo());
  box->addWidget(button);
  box->setSpacing(2);
  box->setContentsMargins(10, 0, 10, 0);

  grid->addLayout(box, 0, 0);
}

/**
 * @brief Creating a Model Information
 */
QTextEdit *View::createModelInfo() {
  QTextEdit *modelInfo = new QTextEdit;
  modelInfo->setStyleSheet(TextEditStyle);

  modelInfo->setReadOnly(true);
  modelInfo->setMaximumHeight(70);
  modelInfo->setAlignment(Qt::AlignCenter);
  modelInfo->setText("Model: absent\nVertices: 0\nFaces: 0");

  return modelInfo;
}

/**
 * @brief Adding a photo/gif recording of models
 */
void View::createScreenshotGifMakeButtons(QGridLayout *grid) {
  QPushButton *screen = new QPushButton(tr("Screen"));
  screen->setStyleSheet(ScreenButtonStyle);
  screen->setToolTip("Скриншот модели");

  connect(screen, &QPushButton::clicked, this, &View::makeScreenshot);

  QPushButton *gifButton = new QPushButton(tr("GIF"));
  gifButton->setWhatsThis("gif button");
  gifButton->setStyleSheet(GifButtonStyle);
  gifButton->setToolTip("Запись gif-анимации");

  connect(gifButton, &QPushButton::clicked, this, &View::onGifButton);

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &View::makeGif);

  QVBoxLayout *box = new QVBoxLayout;
  box->addWidget(screen);
  box->addWidget(gifButton);
  box->setContentsMargins(15, 0, 10, 0);

  grid->addLayout(box, 0, 1);
}

/**
 * @brief Adding a selection of Model Projection Type
 */
void View::createProjectionSelectionBox(QGridLayout *grid) {
  QLabel *parallel = new QLabel(tr("Parallel"));
  parallel->setFixedWidth(64);
  parallel->setStyleSheet(LabelStyle);

  QLabel *chooseProjection = new QLabel(tr("\U0001F878 Projection \U0001F87A"));
  chooseProjection->setFixedWidth(120);
  chooseProjection->setAlignment(Qt::AlignCenter);
  chooseProjection->setStyleSheet(LabelStyle);
  chooseProjection->setToolTip("Изменить тип отображения модели");

  bool type =
      sceneLoader_.getSettingsPackage().projection == ProjectionType::Central
          ? false
          : true;

  QRadioButton *radioParallel = new QRadioButton("");
  radioParallel->setFixedWidth(17);
  radioParallel->setChecked(type);

  QRadioButton *radioCenter = new QRadioButton("Central");
  radioCenter->setChecked(!type);
  radioCenter->setStyleSheet(LabelStyle);

  QButtonGroup *group = new QButtonGroup;
  group->setExclusive(true);
  group->addButton(radioParallel);
  group->addButton(radioCenter);

  connect(
      group, &QButtonGroup::buttonClicked, this,
      [&parallelBtn = *radioParallel,
       &settings = sceneLoader_](QAbstractButton *button) {
        settings.setSetting({SettingsType::ProjectionType,
                             button == &parallelBtn ? ProjectionType::Parallel
                                                    : ProjectionType::Central});
      });

  QHBoxLayout *box = new QHBoxLayout;
  box->addWidget(parallel);
  box->addWidget(radioParallel);
  box->addWidget(chooseProjection);
  box->addWidget(radioCenter);
  box->setAlignment(Qt::AlignCenter);
  box->setContentsMargins(20, 0, 10, 0);

  grid->addLayout(box, 1, 0);
}

/**
 * @brief Adding axes drawing selection
 */
void View::createDisplayAxesBox(QGridLayout *grid) {
  QLabel *label = new QLabel(tr("Axis "));
  label->setFixedWidth(40);
  label->setAlignment(Qt::AlignCenter);
  label->setStyleSheet(LabelStyle);
  label->setToolTip("Отображение осей координат");

  QCheckBox *checkBox = new QCheckBox("");
  checkBox->setChecked(true);
  checkBox->setStyleSheet(LabelStyle);

  QObject::connect(checkBox, &QCheckBox::stateChanged, &openGLWidget_,
                   &OpenGLWidget::setDisplayAxes);

  QPushButton *button = new QPushButton(tr("DEFAULT"));
  button->setStyleSheet(RenderingTypeBtnDefaultStyle);
  button->setFixedSize(130, 27);
  button->setToolTip("ВЫбор типа отрисовки");

  connect(button, &QPushButton::clicked, this,
          [&openGLWidget = openGLWidget_, &button = *button](bool) {
            RenderingType type = openGLWidget.getRenderingType();
            (type == RenderingType::DEFAULT) ? button.setText("SHADERS")
                                             : button.setText("DEFAULT");
            (type == RenderingType::DEFAULT)
                ? button.setStyleSheet(RenderingTypeBtnShadersStyle)
                : button.setStyleSheet(RenderingTypeBtnDefaultStyle);
            openGLWidget.setRenderingType(type == RenderingType::DEFAULT
                                              ? RenderingType::SHADERS
                                              : RenderingType::DEFAULT);
          });

  QHBoxLayout *box = new QHBoxLayout;
  box->addWidget(label);
  box->addWidget(checkBox);
  box->addWidget(button);
  box->setContentsMargins(20, 0, 30, 0);
  box->setSpacing(0);

  grid->addLayout(box, 1, 1);
}

/**
 * @brief Adding a Move and Scale slider
 */
void View::createMoveScaleBox(QGridLayout *grid) {
  SliderData data = {-20, 20, 0};
  QHBoxLayout *xMoveBox = moveScaleBoxFactory("mX", data, AffineOps::Moving,
                                              Axes::X, 0.1, &lastMoveValue_.x);
  grid->addLayout(xMoveBox, 2, 0);

  data = {-20, 20, 0};
  QHBoxLayout *yMoveBox = moveScaleBoxFactory("mY", data, AffineOps::Moving,
                                              Axes::Y, 0.2, &lastMoveValue_.y);
  grid->addLayout(yMoveBox, 3, 0);

  data = {-20, 20, 0};
  QHBoxLayout *zMoveBox = moveScaleBoxFactory("mZ", data, AffineOps::Moving,
                                              Axes::Z, 0.1, &lastMoveValue_.z);
  grid->addLayout(zMoveBox, 4, 0);

  data = {1, 70, 5};
  QHBoxLayout *scBox =
      moveScaleBoxFactory("Sc", data, AffineOps::Scaling, Axes::X, 1, nullptr);

  grid->addLayout(scBox, 5, 0);
}

/**
 * @brief Factory for the Move and Scale slider
 */
QHBoxLayout *View::moveScaleBoxFactory(const char *name, SliderData &data,
                                       AffineOps op, Axes axis,
                                       float coefficient, int *last) {
  QLabel *label = new QLabel(tr(name));
  label->setFixedWidth(19);
  label->setAlignment(Qt::AlignCenter);
  label->setStyleSheet(LabelStyle);

  QSlider *slider = new QSlider(Qt::Horizontal, this);
  if (op == AffineOps::Scaling) slider->setWhatsThis("scale slider");
  slider->setRange(data.min_value, data.max_value);
  slider->setValue(data.current_value);
  slider->setStyleSheet(MoveSliderStyle);

  QObject::connect(
      slider, &QSlider::valueChanged, this,
      [this, op, axis, coefficient, last](int value) {
        if (op == AffineOps::Scaling)
          transformScene(AffineOps::Scaling, Axes::X, value);
        else if (op == AffineOps::Moving) {
          transformScene(
              op, axis,
              coefficient * ((*last == -100) ? value : value - *last));
          *last = value;
        }
      });

  QHBoxLayout *box = new QHBoxLayout;
  box->addWidget(label);
  box->addWidget(slider);
  box->setContentsMargins(10, 0, 10, 0);

  return box;
}

/**
 * @brief Adding a sliders for rotation
 */
void View::addRotationBoxes(QGridLayout *grid) {
  QHBoxLayout *xBox = rotationBoxFactory("xR", Axes::X, lastRotationValue_.x);
  grid->addLayout(xBox, 6, 0);

  QHBoxLayout *yBox = rotationBoxFactory("yR", Axes::Y, lastRotationValue_.y);
  grid->addLayout(yBox, 7, 0);

  QHBoxLayout *zBox = rotationBoxFactory("zR", Axes::Z, lastRotationValue_.z);
  grid->addLayout(zBox, 8, 0);
}

/**
 * @brief Factory for the rotation slider
 */
QHBoxLayout *View::rotationBoxFactory(const char *name, Axes axis, int &last) {
  // label
  QLabel *label = new QLabel(tr(name));
  label->setFixedWidth(21);
  label->setAlignment(Qt::AlignLeft);
  label->setStyleSheet(LabelStyle);

  // value
  QLabel *value = new QLabel("0");
  value->setAlignment(Qt::AlignCenter);
  value->setFixedWidth(40);
  value->setStyleSheet(ValueStyle);

  // slider
  QSlider *slider = new QSlider(Qt::Horizontal, this);
  slider->setRange(0, 360);
  slider->setValue(0);
  slider->setTickPosition(QSlider::TicksBothSides);
  slider->setTickInterval(90);

  QObject::connect(slider, &QSlider::valueChanged, this,
                   [value, axis, &last, this](int newValue) {
                     value->setText(QString::number(newValue));
                     transformScene(AffineOps::Rotation, axis, newValue - last);
                     last = newValue;
                   });

  // increase button
  QPushButton *increaseButton = new QPushButton("+");
  increaseButton->setStyleSheet(IncreaseButtonStyle);
  increaseButton->setFixedWidth(15);

  QObject::connect(increaseButton, &QPushButton::pressed, [slider]() {
    if (slider->value() < 360) slider->setValue(slider->value() + 1);
  });

  // decrease button
  QPushButton *decreaseButton = new QPushButton("-");
  decreaseButton->setStyleSheet(DecreaseButtonStyle);
  decreaseButton->setFixedWidth(15);

  QObject::connect(decreaseButton, &QPushButton::clicked, [slider]() {
    if (slider->value() > 0) slider->setValue(slider->value() - 1);
  });

  // box
  QHBoxLayout *box = new QHBoxLayout;
  box->addWidget(label);
  box->addWidget(value);
  box->addWidget(slider);
  box->addWidget(increaseButton);
  box->addWidget(decreaseButton);
  box->setContentsMargins(10, 0, 10, 0);

  return box;
}

/**
 * @brief Adding a Color Pickers for changing the color of the background, edges
 * and vertices
 */
void View::createColorChoiceBoxex(QGridLayout *grid) {
  QHBoxLayout *background =
      colorPickerFactory("Background    ", SettingsType::BackgroundColor);
  grid->addLayout(background, 2, 1);

  QHBoxLayout *edges =
      colorPickerFactory("Edges color     ", SettingsType::EdgesColor);
  grid->addLayout(edges, 4, 1);

  QHBoxLayout *vertices =
      colorPickerFactory("Vertices color", SettingsType::VerticesColor);
  grid->addLayout(vertices, 6, 1);
}

/**
 * @brief Factory for the Color Picker
 */
QHBoxLayout *View::colorPickerFactory(const char *name, SettingsType type) {
  QLabel *label = new QLabel(tr(name));
  label->setAlignment(Qt::AlignCenter);
  label->setStyleSheet(LabelStyle);

  ColorPicker *color_picker = new ColorPicker(nullptr);
  color_picker->setFixedSize(130, 20);
  color_picker->setStyleSheet("margin-left: 50px;");

  QObject::connect(color_picker, &ColorPicker::colorPickerClicked, this,
                   [type, &settings = sceneLoader_](RGB color) {
                     settings.setSetting({type, color});
                   });

  QHBoxLayout *box = new QHBoxLayout;
  box->setSpacing(3);
  box->addWidget(label);
  box->addWidget(color_picker);
  box->setContentsMargins(10, 0, 10, 0);

  return box;
}

/**
 * @brief Adding a selection of Line Type
 */
void View::createLineTypeSelectionBox(QGridLayout *grid) {
  QLabel *label = new QLabel(tr("Line type"));
  label->setAlignment(Qt::AlignCenter);
  label->setFixedWidth(80);
  label->setStyleSheet(LabelStyle);
  label->setToolTip(
      "Изменение типа отображения линий на сплошной или пунктирный");

  ///////////////////////////////////////////////////////
  QRadioButton *LineTypeButton = new QRadioButton("Solid");
  LineType type = sceneLoader_.getSettingsPackage().lineType;
  LineTypeButton->setChecked(type == LineType::Solid ? false : true);

  if (type == LineType::Stipple) {
    LineTypeButton->setText("Dotted");
    LineTypeButton->setStyleSheet(LineButtonStyleDotted);
  } else
    LineTypeButton->setStyleSheet(LineButtonStyleSolid);

  QObject::connect(LineTypeButton, &QRadioButton::toggled, this,
                   [LineTypeButton, &settings = sceneLoader_](bool value) {
                     LineTypeButton->setText(value ? "Dotted" : "Solid");
                     LineTypeButton->setStyleSheet(
                         value ? LineButtonStyleDotted : LineButtonStyleSolid);
                     settings.setSetting({SettingsType::LineType,
                                          static_cast<LineType>(value)});
                   });

  ///////////////////////////////////////////////////////
  QHBoxLayout *box = new QHBoxLayout;
  box->addWidget(label);
  box->addWidget(LineTypeButton);
  box->setContentsMargins(5, 0, 90, 0);

  grid->addLayout(box, 3, 1);
}

/**
 * @brief Adding a selection of Line/Point Size
 */
void View::createLinePointSizeSelectionBox(QGridLayout *grid) {
  QHBoxLayout *lineWidthBox =
      linePointIncreaseBoxFactory("Thickness ", 20, SettingsType::LineWidth);
  grid->addLayout(lineWidthBox, 5, 1);

  QHBoxLayout *pointSizeBox =
      linePointIncreaseBoxFactory("Point size ", 30, SettingsType::PointSize);
  grid->addLayout(pointSizeBox, 7, 1);
}

/**
 * @brief Factory for the Line/Point Size
 */
QHBoxLayout *View::linePointIncreaseBoxFactory(const char *name, int max_value,
                                               SettingsType type) {
  // label
  QLabel *label = new QLabel(tr(name));
  label->setStyleSheet(LabelStyle);

  // value
  char num[5] = {0};
  sprintf(num, "%lu",
          (type == SettingsType::LineWidth
               ? sceneLoader_.getSettingsPackage().lineWidth
               : sceneLoader_.getSettingsPackage().pointSize));

  QLabel *value = new QLabel(num);
  value->setAlignment(Qt::AlignCenter);
  value->setFixedWidth(40);
  value->setStyleSheet(ValueStyle);

  // slider
  QSlider *slider = new QSlider(Qt::Horizontal, this);
  slider->setWhatsThis("size slider");
  slider->setRange(1, max_value);  // Установка диапазона значений
  slider->setValue(type == SettingsType::LineWidth
                       ? sceneLoader_.getSettingsPackage().lineWidth
                       : sceneLoader_.getSettingsPackage()
                             .pointSize);  // Установка начального значения
  slider->setTickPosition(QSlider::TicksBothSides);
  slider->setTickInterval(5);

  QObject::connect(slider, &QSlider::valueChanged, [slider, value]() {
    value->setText(QString::number(slider->value()));
  });

  // connect(*slider, &QSlider::valueChanged, this, pointerToFunction);
  QObject::connect(
      slider, &QSlider::valueChanged, this,
      [type, &settings = sceneLoader_](int value) {
        settings.setSetting({type, static_cast<std::size_t>(value)});
      });

  // box
  QHBoxLayout *box = new QHBoxLayout;
  box->setContentsMargins(11, 0, 10, 0);
  box->setSpacing(10);

  box->addWidget(label);
  box->addWidget(value);
  box->addWidget(slider);

  return box;
}

/**
 * @brief Adding an application exit button
 */
void View::createQuitButton(QGridLayout *grid) {
  QPushButton *button = new QPushButton(tr("Quit"));
  button->setStyleSheet(QuitButtonStyle);

  QObject::connect(button, &QPushButton::clicked, this, &View::quit);

  QHBoxLayout *box = new QHBoxLayout;
  box->addWidget(button);
  box->setContentsMargins(40, 0, 40, 0);

  grid->addLayout(box, 9, 0);
}

/**
 * @brief Adding a selection of Vertex Type
 */
void View::addVertexTypeSelectionBox(QGridLayout *grid) {
  // label
  QLabel *label = new QLabel(tr("Display type"));
  label->setAlignment(Qt::AlignCenter);
  label->setFixedWidth(100);
  label->setStyleSheet(LabelStyle);
  label->setToolTip("Изменения типа отображения точек");

  // combo box
  QComboBox *comboBox = new QComboBox;
  comboBox->addItem("Square");
  comboBox->addItem("Circle");
  comboBox->addItem("None");
  comboBox->setCurrentIndex(
      static_cast<int>(sceneLoader_.getSettingsPackage().vertexType));

  QObject::connect(comboBox, &QComboBox::activated, this,
                   [&settings = sceneLoader_](int index) {
                     settings.setSetting({SettingsType::VertexType,
                                          static_cast<VertexType>(index)});
                   });

  // box
  QHBoxLayout *box = new QHBoxLayout;
  box->setSpacing(3);
  box->addWidget(label);
  box->addWidget(comboBox);
  box->setContentsMargins(8, 0, 10, 0);

  grid->addLayout(box, 8, 1);
}
}  // namespace s21