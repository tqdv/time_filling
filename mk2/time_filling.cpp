#include "time_filling.hpp"
#include <random>
#include <list>
#include <iterator>
#include <vector>
#include <utility>
#include "hexagon.hpp"
#include "utils.hpp"


using std::vector;
using std::list;
using std::next;
using std::get;

namespace t_fl {

/* RNG */

RNG init_rng() {
	RNG rng;
	std::random_device rd;
	rng.seed(rd());
	return rng;
}

int randint (int a, int b) {
	std::uniform_int_distribution<> dis(a, b);
	return dis(rng);
}

/* Endpoints */
bool Endpoints::is_loop () const {
	return from == to;
}

Itinerary::Itinerary (Hexagon h, Endpoints e) : hex(h), ends(e) { }

/* */

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


// Finds the end point for left and start point for right which are adjacent
HexPoint2 link_between (cr <Hexagon> left, cr <Hexagon> right) {
	/* We assume that the two hexagons are neighbours */
	vector<Hexagon> ls, rs;

	if (left.size <= right.size) {
		rs = closest_hexs(left, right);
	}
	if (left.size >= right.size) {
		ls = closest_hexs(right, left);
	}

	Hexagon l, r;
	Hexagon2 n = pick_neighbour_pair (ls, rs);
	l = get<0> (n);
	r = get<1> (n);

	/* Now, both sides have the same size */
	while (l.size > 1) {
		auto [ls, rs] = closer_hexs (l, r);
		Hexagon2 n = pick_neighbour_pair (ls, rs);
		l = get<0> (n);
	}
	r = get<1> (n);

	HexPoint2 p = HexPoint2 (HexPoint(l), HexPoint(r));

	return p;
}


// TODO: Refactor those two do ... while loops
list<Itinerary> get_itinerary
 (vector<Hexagon> hexs, HexPoint from, HexPoint to) {
	/* We assume that:
	 * + $from and $to are in the first and last $hexs respectively
	 * + each ajacent pair of $hexs are neighbours
	 */
	int n = hexs.size();
	vector <Endpoints> ends(n);
	ends.front().from = from;
	ends.back().to = to;

	/* Figure out the links (or neighbours) between each hex */
	for (int i = 0; i+1 < n; i++) {
		// A path always exists
		do {
			auto [t, f] = link_between(hexs[i], hexs[i+1]);
			ends[i].to = t;
			ends[i+1].from = f;
		} while (!ends[i].is_loop());
	}
	// Make sure the last itinerary isn't a loop
	if (n > 1) {
		do {
			auto [t, f] = link_between(hexs[n-2], hexs[n-1]);
			ends[n-2].to = t;
			ends[n-1].from = f;
		} while (!ends[n-1].is_loop());
	}

	list <Itinerary> l;
	for (int i = 0; i < n; i++) {
		l.push_back (Itinerary (hexs[i], ends[i]));
	}

	return l;
}


///* Rules to simplify the hexagons */
//
///* Hexagon size = n -> n - 2
// * (have the most lines on the outer to highlight the contour) */
//std::list <Hexagon> simplify_hex2
// (cr <Hexagon> hex, cr <Hexagon> left, cr <Hexagon> right) {
//	if (left.size == hex.size)
//}
//
///* Hexagon size = n -> n - 1 */


} // namespace t_fl
