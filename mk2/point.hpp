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

using Coord = std::pair<int, int>;

} // namespace t_fl

#endif  // POINT_HPP
