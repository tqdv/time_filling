#include <iostream>
#include "time_filling.hpp"


int main() {
	using namespace t_fl;

	int n = 365;  // Number of points
	std::vector <Hexagon> blocks;

	HexPoint from, to;

	std::vector<HexPoint> path = path_random (blocks, from, to);

	/* Display coordinates */
	for (cr<point> p : path) {
		std::cout << (Point) p;
	}
}
