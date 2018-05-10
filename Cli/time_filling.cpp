#include <getopt.h>  // currently unused
#include <iostream>
#include <optional>
#include <random>

#include "hexagon.hpp"
#include "utils.hpp"

int main (int argc, char **argv) {
	std::random_device rd;
	std::minstd_rand gen;
	gen.seed (rd ());

	std::optional<Path> path;
	int from, to;

	for (int i = 0; i < 10; i++) {

		from = gen () % 7;
		to = gen () % 7;
		path = shape_path (hexagon, from, to);

		if (path.has_value ()) {
			print_vector (*path);
			std::cout << '\n';
		} else {
			std::cout << "Path not found from " << from << " to " << to << '\n';
		}
	}

	return 0;
}
