#include <getopt.h>  // currently unused
#include <iostream>
#include <random>

#include "hexagon.hpp"
#include "utils.hpp"

int main (int argc, char **argv) {
	std::random_device rd;
	std::minstd_rand gen;
	gen.seed (rd ());

	HexagonPath path;
	PointPath pos;
	int from, to;
	bool status;

	for (int i = 0; i < 10; i++) {

		from = gen () % 7;
		to = gen () % 7;

		status = hexagon_path (from, to, path);

		if (status) {
			print_array (path);
			std::cout << std::endl;
		} else {
			std::cout << "Path not found from " << from << " to " << to
			          << std::endl;
		}
	}

	return 0;
}
