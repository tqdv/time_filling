#include "time_filling.hpp"
#include <iostream>

using std::cout;
using t_fl::Hexagon_v;
using t_fl::Hexagon;
using t_fl::Coord;
using t_fl::HexPoint;
using t_fl::Itinerary;

int main () {
	cout << "Start\n";
	Hexagon_v v = {
		Hexagon (Coord (0, 0), 0),
		Hexagon (Coord (0, 1), 0)};
	cout << "Done init\n";
	std::list<Itinerary> itins = get_itinerary (v,
		HexPoint(0, 0), HexPoint(0, 1));


	cout << "(\n";
	for (cr <Itinerary> itin : itins) {
		cout << "{\n";
		cout << "\thex:\n";
		cout << "\t\tcenter: ";
		{
		auto [x, y] = itin.hex.center;
		cout << "(" << x << ", " << y << ")\n";
		}
		cout << "\t\tsize: ";
		cout << itin.hex.size << "\n";
		cout << "\tends:\n";
		cout << "\t\tfrom: ";
		{
		auto [x, y] = itin.ends.from;
		cout << "(" << x << ", " << y << ")\n";
		}
		cout << "\t\tto: ";
		{
		auto [x, y] = itin.ends.to;
		cout << "(" << x << ", " << y << ")\n";
		}
		cout << "}\n";
	}
	cout << ")\n";

	return 0;
}
