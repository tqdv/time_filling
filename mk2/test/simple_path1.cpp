#include <iostream>
#include "time_filling.hpp"
#include "utils.hpp"

using std::cout;

int main () {
	t_fl::init_default_base (1);
	t_fl::Coord c (0, 0);
	t_fl::Coord a (0, 1);
	t_fl::Coord b (1, 0);
	t_fl::Hexagon h (c, 1);
	t_fl::Endpoints e (a, b);
	t_fl::Itinerary itin (h, e);

	std::list <t_fl::Itinerary> out = simple_path (itin);

	cout << "Simple test to see if simple_path works\n";
	for (cr <t_fl::Itinerary> i : out) {
		cout << "{\n";
		cout << "\thex: (";
		{
		const auto &[x, y] = i.hex.center;
		cout << "(" << x << ", " << y << ")";
		}
		cout << ", ";
		cout << i.hex.size << ")\n";
		cout << "\t";
		{
		const auto &[x, y] = i.ends.from;
		cout << "(" << x << ", " << y << ")";
		}
		cout << " -> ";
		{
		const auto &[x, y] = i.ends.to;
		cout << "(" << x << ", " << y << ")";
		}
		cout << "\n";
		cout << "}\n";
	}

	return 0;
}
