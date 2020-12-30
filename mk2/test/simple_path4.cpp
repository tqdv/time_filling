#include <iostream>
#include "time_filling.hpp"
#include "utils.hpp"

using std::cout;

int main () {
	t_fl::init_default_base (1);
	t_fl::Coord c (1, -1);
	t_fl::Coord a (3, -5);
	t_fl::Coord b (4, -4);
	t_fl::Hexagon h (c, 2);
	t_fl::Endpoints e (a, b);
	t_fl::Itinerary itin (h, e);

	t_fl::Hexagon_v out = simplify_hex1 (itin);

	cout << "Simple test to see if simple_path works\n";
	cout << "This is for debugging a weird case where only the distance == 2\n";
	cout << "case in simplify_hex1 gives the same values for all hexs from [1]\n";
	cout << "to [5]\n";
	for (auto h : out) {
		cout << "(";
		{
		const auto &[x, y] = h.center;
		cout << "(" << x << ", " << y << ")";
		}
		cout << ", ";
		cout << h.size << ")\n";
	}

	return 0;
}
