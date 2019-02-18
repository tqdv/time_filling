#include "hexagon.hpp"

#include <vector>
#include <algorithm>
using std::transform;
#include <functional>
using std::bind;
#include <map>
// coord_node
#include "point.hpp"
#include "utils.hpp"

namespace t_fl {

void init_default_base(int n) {
	/* We assume n >= 0 */
	bases.clear();
	bases.reserve(n+1);
	bases.push_back (Coord2 (Coord (1, 0), Coord (0, 1)));
	
	for (int i = 1; i <= n; i++) {
		if (i % 2 == 1) {
			bases.push_back (Coord2 (Coord (2, 1), Coord (-1, 3)));
		} else {
			bases.push_back (Coord2 (Coord (3, -1), Coord (1, 2)));
		}
	}
}

FCoord2 invert_base (Coord2 base) {
	/* We assume it is possible */
	/*  x y
	 * [a b]
	 * [c d]
	 */
	auto [x, y] = base;
	auto [a, c] = x;
	auto [b, d] = y;
	float det = a * d - c * b; // For the float conversion

	return FCoord2 (
		FCoord ( d/det, -c/det),
		FCoord (-b/det,  a/det));
}

Coord lower (cr <Coord> c, int s) {
	const auto &[x, y] = c;
	const auto &[cx, cy] = bases[s];

	return x * cx + y * cy;
}

/* Hexagon */

Hexagon::Hexagon () {}

Hexagon::Hexagon (Coord c, int s) : center (c), size (s) { }

Hexagon::Hexagon (HexPoint p) : center ((Coord) p), size (0) { }

Hexagon::Hexagon (HexPoint p, int s) {
	/* Assume s > 0 */
	*this = (Hexagon) p;
	while (this->size < s) {
		*this = this->bigger();
	}
}

Hexagon_v Hexagon::explode () const {
	/* We assume $size > 0 */
	Hexagon_v v(7);

	cr <Coord> c = lower(center, size);

	int s = size - 1;
	auto f = [&c, s] (int x, int y) { return Hexagon (c + Coord(x, y), s); };
	v[0] = f (0, 0);
	v[1] = f (1, 0);
	v[2] = f (0, 1);
	v[3] = f (-1, 1);
	v[4] = f (-1, 0);
	v[5] = f (0, -1);
	v[6] = f (1, -1);

	return v;
}

Hexagon Hexagon::smaller () const {
	/* We assume that $size > 0 */
	Coord c = lower (center, size);
	return Hexagon (c, size -1);
}

Hexagon Hexagon::bigger () const {
	int s = size + 1;
	const auto &[x, y] = center;
	FCoord2 inv = invert_base (bases[s]); // This could be memoized

	const auto &[cx, cy] = inv;

	FCoord c = x * cx + y * cy;
	return Hexagon ((Coord) c, s);
}

Hexagon::operator HexPoint () {
	Coord c = center;

	for (int i = size; i > 0; i--) {
		c = lower (c, i);
	}

	return HexPoint (c);
}

Coord operator- (Hexagon l, Hexagon r) {
	return l.center - r.center;
}

Hexagon operator+ (Hexagon h, Coord c) {
	return Hexagon (h.center + c, h.size);
}
Hexagon operator+ (Coord c, Hexagon h) { return h + c; }

Hexagon hex_coord (cr <Hexagon> h, cr <Coord> c) {
	return h + c;
}
Hexagon_v hex_coord (cr <Hexagon> h, cr <Coord_v> cs) {
	Hexagon_v v (cs.size ());
	using namespace std::placeholders;

	auto f = bind (static_cast <Hexagon(*)(cr <Hexagon>, cr <Coord>)>
		(hex_coord), h, _1);
	transform (cs.begin(), cs.end(), v.begin(),
		f);

	return v;
}


/* Hexagon distance */

int dist (cr <Hexagon> left, cr <Hexagon> right) {
	return dist (left.center, right.center);
}

bool are_neighbours (cr <Hexagon> left,  cr <Hexagon> right) {
	return dist (left, right) == 1;
}

/* Node */

/* Assign a number to each point in the hexagon */
/*  2 1
 * 3 6 0
 *  4 5
 */
// The outer ring is 0..5 so you can work in mod 6
const std::map <Coord, Node> node_coord_m {
	{{ 1,  0}, 0},
	{{ 0,  1}, 1},
	{{-1,  1}, 2},
	{{-1,  0}, 3},
	{{ 0, -1}, 4},
	{{ 1, -1}, 5},
	{{ 0,  0}, 6}};
const std::map <Node, Coord> coord_node_m {
	{0, { 1,  0}},
	{1, { 0,  1}},
	{2, {-1,  1}},
	{3, {-1,  0}},
	{4, { 0, -1}},
	{5, { 1, -1}},
	{6, { 0,  0}}};

Node node_coord (cr <Coord> c) {
	return node_coord_m.at(c);  // Use .at for const correctness
}
Coord coord_node (cr <Node> n) {
	return coord_node_m.at(n);
}
Coord_v coord_node (cr <Node_v> ns) {
	Coord_v cs (ns.size ());
	
	// Choose the right overload
	auto f = static_cast <Coord(*)(cr <Node>)> (coord_node);
	transform (ns.begin(), ns.end(), cs.begin(), f);
		
	return cs;
}

}  // namespace t_fl
