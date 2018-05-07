#include "hexagon.hpp"
#include <array>
#include <iostream>
#include <random>
#include <unistd.h>
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include "controls.hpp"
#include "gui.hpp"


int main(int argc, char **argv) {
  QApplication app(argc, argv);
  Canvas canvas;
  Controls controls;

  QObject::connect(&controls, &Controls::fromChanged, &canvas,
                   &Canvas::setFrom);
  QObject::connect(&controls, &Controls::toChanged, &canvas, &Canvas::setTo);

  canvas.show();
  canvas.resize(500, 500);

  controls.show();

  return app.exec();
}
