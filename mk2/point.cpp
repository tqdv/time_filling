#include "point.hpp"
#include <cmath>

using std::sqrt;

namespace t_fl {

Point::Point (Real x, Real y) : x(x), y(y) { }

/* Maybe this fails because of namespacing */
std::ostream& operator<< (std::ostream &out, cr<Point> p) {
	out << "(" << p.x << ", " << p.y << ")";
	return out;
}

HexPoint::HexPoint (int x, int y) : x(x), y(y) { }

HexPoint::operator Point () {
	Real xx = x;
	Real yy = y;
	/* Base vectors are (1, 0) and (1/2, sqrt(3)/2) */
	return Point (xx + yy / 2, sqrt(3) / 2 * yy);
}

}  // namespace t_fl
