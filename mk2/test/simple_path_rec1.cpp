#include <iostream>
#include "time_filling.hpp"
#include "utils.hpp"

using std::cout;

int main () {
	t_fl::init_default_base (3);
	t_fl::Coord c (0, 0);
	t_fl::Coord a (-3, -8);
	t_fl::Coord b (10, 1);
	t_fl::Hexagon h (c, 3);
	t_fl::Endpoints e (a, b);
	t_fl::Itinerary itin (h, e);

	auto out =
		point_hexpoint (
				t_fl::rec_simple_path ({h}, a, b)
				)
		;

	cout << "[\n";
	for (auto p : out) {
		{
		const auto &[x, y] = p;
		cout << "(" << x << ", " << y << "),\n";
		}
	}
	cout << "]\n";

	return 0;
}
