#include <iostream>
#include "time_filling.hpp"
#include "utils.hpp"

using std::cout;
using namespace t_fl;

int main () {
	init_default_base (3);
	Hexagon edge (Coord (1, 0), 2);
	Hexagon first = edge.smaller () + Coord (2, -1);
	Hexagon_v hexs = {
		Hexagon (Coord (-1, 0), 2),
		Hexagon (Coord (-1, 1), 2),
		Hexagon (Coord (0, 1), 2),
		Hexagon (Coord (0, 0), 2),
		Hexagon (Coord (0, -1), 2),
		Hexagon (Coord (1, -1) ,2),
		edge,
		first,
		first + Coord (1, 0),
		first + Coord (2, -1),
		first + Coord (1, -1)
	};

	HexPoint a (-10, -1);
	HexPoint b (16, -4);
	//HexPoint b (-8, 4);

	auto out =
		point_hexpoint (
				rec_simple_path (hexs, a, b)
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
