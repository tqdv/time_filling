#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <utility> // std::pair
#include "utils.hpp"

namespace t_fl {

using Real = float;  // Use this to set precision, maybe

struct Point {
	Real x;
	Real y;

	Point (Real, Real);
	friend std::ostream& operator<< (std::ostream&, cr<Point>);
};

/* x and y are coordinates along the following axis of a plane :
 * /-> 30° (y)
 * -->   0° (x)
 */
struct HexPoint {
	int x;
	int y;

	HexPoint (int, int);
	operator Point ();
};

/* The difference between Coord and HexPoint is that the former represents
 * coordinates in any 2D basis, whereas HexPoint represents them
 * in the Hexagonal 2D basis defined above */
struct Coord : public std::pair<int, int> {
	template <typename ... Types>
	Coord (Types ... Args) : std::pair<int, int>(Args ...) { }
	operator HexPoint ();
};
Coord operator+ (cr <Coord>, cr <Coord>);
Coord operator- (cr <Coord>, cr <Coord>);
Coord operator* (cr <Coord>, cr <int>);
Coord operator* (cr <int> a, cr <Coord> b) { return b * a; }
int norm (cr <Coord>);
int dist (cr <Coord>, cr <Coord>);

using Coord2 = std::pair<Coord, Coord>;

} // namespace t_fl

#endif  // POINT_HPP
