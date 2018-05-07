#include <iostream>
#include <array>
#include <random>
#include <getopt.h>
#include <unistd.h>
#include "hexagon.hpp"

struct Options {
	bool gui = false;
} opts;

int main(int argc, char **argv) {
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
