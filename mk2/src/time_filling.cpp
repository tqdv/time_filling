#include "time_filling.hpp"
#include <vector>
using std::vector;
#include <list>
using std::list;
#include <iterator>
using std::next;
#include <algorithm>
using std::transform;
using std::min;
#include <cmath>
using std::abs;
#include "hexagon_ops.hpp"
// link_betweet …
#include "rng.hpp"
// randbool
#include "utils.hpp"

namespace t_fl {

/* Assign the to be connected ends of the end of the list, given $hexs */
/* Returns the start of the next itinerary */
HexPoint assign_next_bridge (cr <Hexagon_v> hexs, list <Itinerary> &l) {
	// We assume there is an element after this one
	auto rbegin = l.rbegin ();
	int n = l.size ();

	HexPoint f;
	do {
		auto [to, from] = link_between (hexs[n-1], hexs[n]);
		rbegin->ends.to = to;
		f = from; // Just in case because of scoping
	} while (rbegin->is_loop ());

	return f;
}

list<Itinerary> get_itinerary
 (vector<Hexagon> hexs, HexPoint from, HexPoint to) {
	/* We assume that:
	 * + $from and $to are in the first and last $hexs respectively
	 * + two consecutive $hexs are neighbours
	 */
	int n = hexs.size();
	list <Itinerary> l;
	bool valid = false; // Validity of the itinerary (does it have loops ?)
	// A valid itinerary always exists… probably
	do {
		l.clear();

		HexPoint f = from;  // Used in the loop
		for (int i = 0; i+1 < n; i++) {
			Itinerary &elt = l.emplace_back (Itinerary (hexs[i]));
			elt.ends.from = f;
			f = assign_next_bridge (hexs, l);
		}

		Itinerary &elt = l.emplace_back (Itinerary (hexs.back()));
		elt.ends.from = f;
		elt.ends.to = to;

	valid = !elt.is_loop(); // Make sure the last itinerary isn't a loop
	} while (!valid);

	return l;
}


Node_v node_path (Node from, Node to) {
	/* We assume from != to and neither are the middle one */
	Node_v path (7);
	path.front() = from;
	path.back() = to;

	// Hardcoded solution
	int n = 6; // modulo n

	/* In mod, abs (x) = y has two solutions: x = y and x = n - y */
	int n_dist = abs (to - from) % n; // "normal" distance
	int distance = min (n_dist, n - n_dist);
	// direction of (from -> to)
	int direction = ((from + distance) % n == to ? 1 : n - 1);
	int oppdir = (n - direction);  // positive so % works correctly
	static const int HEX_CENTER = 6; // cf. node_coord defined in hexagon.hpp


	switch (distance) {
	case 1:
		/* /\/\
		 * \  /
		 */
		path[1] = (from + oppdir) % n;
		path[2] = (path[1] + oppdir) % n;
		path[3] = HEX_CENTER;
		path[4] = (path[2] + oppdir) % n;
		path[5] = (path[4] + oppdir) % n;

		break;

	case 2:
		/* Randomly decide whether to go
		 *         __
		 * /_/\    _ \
		 *  __/ or \\/
		 */
		if (randbool ()) {
			path[1] = (from + direction) % n;
			path[2] = HEX_CENTER;
			path[3] = (from + oppdir) % n;
			path[4] = (path[3] + oppdir) % n;
			path[5] = (path[4] + oppdir) % n;
		} else {
			path[1] = (from + oppdir) % n;
			path[2] = (path[1] + oppdir) % n;
			path[3] = (path[2] + oppdir) % n;
			path[4] = HEX_CENTER;
			path[5] = (from + direction) % n;
		}
		break;

	case 3:
		/* Randomly decide to first go following direction, or the opposite */
		/* /‾/    \‾\
		 *  /_/  \_\
		 */
		if (randbool ()) {
			path[1] = (from + direction) % n;
			path[2] = (path[1] + direction) % n;
			path[3] = HEX_CENTER;
			path[4] = (from + oppdir) % n;
			path[5] = (path[4] + oppdir) % n;
		} else {
			path[1] = (from + oppdir) % n;
			path[2] = (path[1] + oppdir) % n;
			path[3] = HEX_CENTER;
			path[4] = (from + direction) % n;
			path[5] = (path[4] + direction) % n;
		}
		break;
	} // switch

	return path;
}

/* Rules to simplify the hexagons */

Hexagon_v simplify_hex1 (cr <Itinerary> itin) {
	Hexagon center = itin.hex.smaller ();
	int size = center.size;
	Hexagon start = Hexagon (itin.ends.from, size);
	Hexagon end = Hexagon (itin.ends.to, size);
	Node from = node_coord (start - center);
	Node to = node_coord (end - center);

	Hexagon_v hexs = hex_coord (center, coord_node (node_path (from, to)));

	return hexs;
}

Hexagon_v simplify_hex2 (cr <Itinerary> itin) {
	// TODO
}

Hexagon_v outline2_hex (cr <Itinerary> itin) {
	int n = itin.hex.size;

	/* Hexagon size = n -> n - 2
	 * (have the most lines on the outer to highlight the contour) */
	if (n >= 2) {
		return simplify_hex2 (itin);
	}

	/* Hexagon size = n -> n - 1 */
	return simplify_hex1 (itin);
}

/* Path breakers */

list <Itinerary> simple_path (cr <Itinerary> itin) {
	Hexagon_v hexs = simplify_hex1 (itin);

	return get_itinerary (hexs, itin.ends.from, itin.ends.to);
}

list <Itinerary> outline2_path (cr <Itinerary> itin) {
	Hexagon_v hexs = outline2_hex (itin);

	return get_itinerary (hexs, itin.ends.from, itin.ends.to);

}

void replace_elt
(list <Itinerary> &l, list <Itinerary>::iterator &it, list <Itinerary> repl) {
	l.insert (it, repl.begin(), repl.end());
	l.erase (it);
}

list <HexPoint> rec_simple_path (Hexagon_v hexs, HexPoint from, HexPoint to) {
	list <Itinerary> l = get_itinerary (hexs, from, to);
	bool are_all_hex = false;
	while (!are_all_hex) {
		are_all_hex = true;
		list <Itinerary>::iterator elt = l.begin();
		list <Itinerary>::iterator nelt; // next elt

		while (elt != l.end()) {
			nelt = next (elt); // Needed because we invalidate elt
			if (elt->hex.size != 0) {
				are_all_hex = false;
				replace_elt (l, elt, simple_path (*elt));
			}
			elt = nelt;
		}
	}

	list <HexPoint> p (l.size ());
	transform (l.begin(), l.end(), p.begin(),
		[] (Itinerary i) { return HexPoint (Hexagon (i)); });

	return p;
}



} // namespace t_fl
