#include "hexagon.hpp"

#include <vector>
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

Coord lower (cr <Coord> c, int s) {
	const auto &[x, y] = c;
	const auto &[cx, cy] = bases[s];

	return x * cx + y * cy;
}

/* Hexagon */

Hexagon::Hexagon () {}

Hexagon::Hexagon (Coord c, int s) : center (c), size (s) { }

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

Hexagon::operator HexPoint () {
	Coord c = center;

	for (int i = size; i > 0; i--) {
		c = lower (c, i);
	}

	return HexPoint (c);
}

/* */

int dist (cr <Hexagon> left, cr <Hexagon> right) {
	return dist (left.center, right.center);
}

bool are_neighbours (cr <Hexagon> left,  cr <Hexagon> right) {
	return dist (left, right) == 1;
}

}  // namespace t_fl
