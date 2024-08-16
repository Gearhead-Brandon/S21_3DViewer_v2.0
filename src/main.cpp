#include <QtGlobal>

#include "app/View/View.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  std::setlocale(LC_NUMERIC, "C");

  s21::Model model;

  s21::Controller controller(model);

  s21::View view(controller);

  view.show();

  return app.exec();
}