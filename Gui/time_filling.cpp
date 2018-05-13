#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include <random>
#include <unistd.h>

#include "controls.hpp"
#include "gui.hpp"
#include "shapes.hpp"

int main (int argc, char **argv) {
	QApplication app (argc, argv);
	Canvas canvas;
	Controls controls;

	QObject::connect (
	   &controls, &Controls::fromChanged, &canvas, &Canvas::setFrom);
	QObject::connect (&controls, &Controls::toChanged, &canvas, &Canvas::setTo);

	canvas.show ();
	canvas.resize (500, 500);

	controls.show ();

	return app.exec ();
}
