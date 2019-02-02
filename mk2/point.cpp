#include "point.hpp"

#include <cmath>
using std::sqrt;
using std::abs;
#include <algorithm>
using std::min;

namespace t_fl {

/* Point */

Point::Point (Real x, Real y) : x(x), y(y) { }

/* Maybe this fails because of namespacing */
std::ostream& operator<< (std::ostream &out, cr<Point> p) {
	out << "(" << p.x << ", " << p.y << ")";
	return out;
}

/* HexPoint */
HexPoint::HexPoint () {};

HexPoint::HexPoint (int x, int y) : x(x), y(y) { }

HexPoint::operator Point () {
	Real xx = x;
	Real yy = y;
	/* Base vectors are (1, 0) and (1/2, sqrt(3)/2) */
	return Point (xx + yy / 2, sqrt(3) / 2 * yy);
}

bool operator== (cr <HexPoint> left, cr <HexPoint> right) {
	return left.x == right.x && left.y == right.y;
}

/* Coord */

Coord operator+ (cr <Coord> a, cr <Coord> b) {
	const auto &[ax, ay] = a;
	const auto &[bx, by] = b;
	return Coord (ax + bx, ay+ by);
}

Coord operator- (cr <Coord> l, cr <Coord> r) {
	const auto &[lx, ly] = l;
	const auto &[rx, ry] = r;
	return Coord (lx - rx, ly - ry);
}

Coord operator* (cr <Coord> a, cr <int> b) {
	const auto &[x, y] = a;
	return Coord (b * x, b * y);
}
Coord operator* (cr <int> a, cr <Coord> b) { return b * a; }

Coord::operator HexPoint () {
	const auto &[x, y] = *this;
	return HexPoint (x, y);
}

int norm (cr <Coord> c) {
	const auto &[x, y] = c;
	if (x * y >= 0) {
		return abs (x + y);
	} else {
		// Consider the third axis (-1, 1)
		return min (
			abs (y) + abs (x + y), // Try on x
			abs (x) + abs (x + y)); // Try on y
	}
}

int dist (cr <Coord> left, cr <Coord> right) {
	return norm (left - right);
}

}  // namespace t_fl
