#include "hexagon.hpp"

#include <vector>
#include "point.hpp"
#include "utils.hpp"

namespace t_fl {

void init_default_base(int n) {
	/* We assume n >= 0 */
	bases.reserve(n+1);
	bases[0] = Coord2 (Coord (1, 0), Coord (0, 1));
	
	for (int i = 1; i <= n; i++) {
		if (i % 2 == 1) {
			bases[i] = Coord2 (Coord (2, 1), Coord (-1, 2));
		} else {
			bases[i] = Coord2 (Coord (3, -1), Coord (1, 2));
		}
	}
}

/* Hexagon */

Hexagon::Hexagon (Coord c, int s) : center (c), size (s) { }

Hexagon::operator HexPoint () {
	auto [x, y] = center;
	Coord c;

	for (int i = size; i > 0; i--) {
		const auto &[cx, cy] = bases[i];
		c = x * cx + y * cy;
		auto [x, y] = c;
	}

	return HexPoint (x, y);
}

Coord operator- (cr <Hexagon> left, cr <Hexagon> other) {
	return left.center - other.center;
}

/* */

bool are_neighbours (cr <Hexagon> left,  cr <Hexagon> right) {
	return norm (left - right) == 1;
}

}  // namespace t_fl
