#include "hexagon_ops.hpp"
#include "rng.hpp"
#include "hexagon.hpp"
// Hexagon
#include "utils.hpp"
// cr <>
#include <vector>
using std::vector;
#include <utility>
using std::get;
#include "itinerary.hpp"

namespace t_fl {

Hexagon2 pick_neighbour_pair (cr <Hexagon_v> left, cr <Hexagon_v> right) {
	/* We assume that the Hexagons are all the same size */
	bool valid = false;  // Whether the pair is valid or not
	int nl, nr, il, ir;
	nl = left.size();
	nr = right.size();

	while (!valid) {
		il = randint(0, nl-1);
		ir = randint(0, nr-1);

		valid = are_neighbours (left[il], right[ir]);
	}

	return Hexagon2 (left[il], right[ir]);
}

Hexagon_v closest_hexs (cr <Hexagon> left, cr <Hexagon> right) {
	Hexagon_v r = {right};

	while (r[0].size > left.size) {
		int min = -1;
		Hexagon_v r_lower;

		/* Consider each element currently in r */
		for (cr <Hexagon> hex : r) {
			cr <Hexagon_v> v = hex.explode();

			/* Consider each subelement */
			for (cr <Hexagon> h : v) {
				int val = dist (left, h);

				if (min == -1) { // initialise
					min = val;
					r_lower.push_back(h);
				} else if (min == val) { 
					r_lower.push_back(h);
				} else if (val < min) {
					min = val;
					r_lower.clear();
					r_lower.push_back(h);
				}
			}
		}
	
		r = r_lower;
	}
	
	return r;
}

Hexagon_v2 closer_hexs (cr <Hexagon> left, cr <Hexagon> right) {
	/* We assume the Hexagons have a size greater than 0 */
	const Hexagon l = left.smaller();
	const Hexagon r = right.smaller();

	return Hexagon_v2 (closest_hexs (r, left), closest_hexs (l, right));
}


// Finds the end point for left and start point for right which are adjacent hexagons
HexPoint2 link_between (cr <Hexagon> left, cr <Hexagon> right) {
	/* We assume that the two hexagons are neighbours */
	vector<Hexagon> ls = {left}, rs = {right};

	if (left.size < right.size) {
		rs = closest_hexs(left, right);
	}
	if (left.size > right.size) {
		ls = closest_hexs(right, left);
	}

	Hexagon l, r;
	Hexagon2 n = pick_neighbour_pair (ls, rs);
	l = get<0> (n);
	r = get<1> (n);

	/* Now, both sides have the same size */
	while (l.size > 0) {
		auto [ls, rs] = closer_hexs (l, r);
		Hexagon2 n = pick_neighbour_pair (ls, rs);
		l = get<0> (n);
		r = get<1> (n);
	}

	HexPoint2 p = HexPoint2 (HexPoint(l), HexPoint(r));

	return p;
}


list <Itinerary> simple_path (cr <Itinerary> itin) {
	Hexagon center = itin.hex.lower ();
	Hexagon start = Hexagon (itin.ends.from, center.size);
	hexagon end = Hexagon (itin.ends.to, center.size);
	// WIP
}

} // namespace t_fl

