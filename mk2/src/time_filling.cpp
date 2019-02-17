#include "time_filling.hpp"
#include <vector>
using std::vector;
#include <list>
using std::list;
#include <iterator>
using std::next;
#include "hexagon_ops.hpp"
// link_betweet …
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

using std::cout;
cout << "Before loop\n";

	list <Itinerary> l;
	

	HexPoint f = from;  // Used in the loop
	for (int i = 0; i+1 < n; i++) {
cout << "Filling itineraries\n";
		Itinerary &elt = l.emplace_back (Itinerary (hexs[i]));
		elt.ends.from = f;
		f = assign_next_bridge (hexs, l);
	}

	Itinerary &elt = l.emplace_back (Itinerary (hexs.back()));
	elt.ends.from = f;
	elt.ends.to = to;

	/* Previous comment:
	// Make sure the last itinerary isn't a loop
	 * Actually, scrap that, too much of a hassle because if it works, but
	 * turns the one before it into a loop, you have to throw everything away
	 * and start again.
	 * Deterministic algorithms, yay
	 */

	return l;
}


/* Rules to simplify the hexagons */

list <Hexagon> simplify_hex (cr <Itinerary> itin) {
	int n = itin.hex.size;

	/* Hexagon size = n -> n - 2
	 * (have the most lines on the outer to highlight the contour) */
	if (n >= 2) {
		return simplify_hex2 (itin);
	}

	/* Hexagon size = n -> n - 1 */
	return simplify_hex1 (itin);
}

std::list <Hexagon> simplify_hex1 (cr <Itinerary> itin) {
	// WIP

}

} // namespace t_fl