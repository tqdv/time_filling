#include <getopt.h>  // currently unused
#include <iostream>
#include <optional>
#include <vector>
#include <random>
#include <cmath>

#include "hexagon.hpp"
#include "utils.hpp"

int main (int argc, char **argv) {
	using std::sqrt;
	const float a = 5;
	
	Maybe<Hexagon> outermost = Hexagon::make_hexagon (sqrt(7) * a * (1 + sqrt(3)), M_PI / 48);
	Maybe<Hexagon> outer = Hexagon::make_hexagon (a * (1 + sqrt(3)), M_PI / 6);
	Maybe<Hexagon> inner = Hexagon::make_hexagon (a, 0);

	if (!outermost.has_value() || !outer.has_value() || !inner.has_value()) {
		return -1;
	}

	std::vector<Shape*> shapes {&(*outermost), &(*outer), &(*inner)};

	Maybe<PointPath> pos = shapes_positions (shapes, {5 * a, 5 * a}, {});
	if (!pos.has_value()) {return -1; }

	print_vector (*pos);
	std::cout << "\n";

	return 0;
}
