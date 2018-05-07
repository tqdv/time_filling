#include <iostream>
#include <array>
#include <random>
#include <getopt.h>
#include <unistd.h>
#include "hexagon.hpp"
#ifdef TFILL_GUI
	#include <QApplication>
	#include <QMainWindow>
	#include <QWidget>
	#include <QPainter>
	#include "gui.hpp"
#endif

struct Options {
	bool gui = false;
} opts;

int main(int argc, char **argv) {
	static const option long_options[] = {
		{"gui", no_argument, nullptr, 'g'},
		{nullptr, 0, nullptr, 0}
	};
	
	int c;
	while ((c = getopt_long(argc, argv, "", long_options, nullptr)) != -1) {
		switch(c) {
		case 'g':
			opts.gui= true;
			break;
		
		default:
			break;
		}
	}

#ifdef TFILL_GUI
	std::optional<QApplication> app;
	std::optional<Canvas> canvas;
	if (opts.gui) {
		app.emplace(argc, argv);

		canvas.emplace();
		canvas->show();
		canvas->resize(500, 500);
		return app->exec();
	}			
#endif

	std::random_device rd;
	std::minstd_rand gen;
	gen.seed(rd());
	HexagonPath path;
	PointPath pos;
	Point center = {5.0, 5.0};
	int from, to;
	bool status;


	for (int i = 0; i < 10; i++) {

		from = gen() % 7;
		to = gen() % 7;

		status = hexagon_path(from, to, path);

		if (status) {
			print_array(path);
			std::cout << std::endl;
		} else {
			std::cout << "Path not found from " << from << " to " << to << std::endl;
		}
		sleep(1);
	}

	return 0;
}
