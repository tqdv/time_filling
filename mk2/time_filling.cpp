#include "time_filling.hpp"
#include <random>
// std::random_device et al.
#include <vector>

using std::vector;
#include <list>
using std::list;
#include <iterator>
using std::next;
#include "hexagon_ops.hpp"

namespace t_fl {

/* Endpoints */
bool Endpoints::is_loop () const {
	return from == to;
}

/* Itinerary */

Itinerary::Itinerary (Hexagon h, Endpoints e) : hex(h), ends(e) { }

/* */

// TODO: Refactor those two do ... while loops
list<Itinerary> get_itinerary
 (vector<Hexagon> hexs, HexPoint from, HexPoint to) {
	/* We assume that:
	 * + $from and $to are in the first and last $hexs respectively
	 * + two consecutive $hexs are neighbours
	 */
	int n = hexs.size();
	/*
	vector <Endpoints> ends(n);
	ends.front().from = from;
	ends.back().to = to;
	*/

using std::cout;
cout << "Before loop\n";

	list <Itinerary> l;

	HexPoint f = from;  // Used in the loop
	for (int i = 0; i+1 < n; i++) {
cout << "In first loop\n";
		Itinerary &elt = l.emplace_back (Itinerary (hexs[i]));
		elt.ends.from = f;

		// A path always exists
		do {
cout << "In dowhile loop\n";
			auto [to, from] = link_between(hexs[i], hexs[i+1]);
			elt.ends.to = to;
			f = from;
		} while (elt.is_loop ());
	}

	// Make sure the last itinerary isn't a loop
	Itinerary &elt = l.emplace_back (Itinerary (hexs.back()));
	elt.ends.to = to;
	if (n > 1) {
cout << "Checking last element\n";
		elt.ends.from = f;  // From the last loop

		do {
			auto [to, from] = link_between(hexs[n-2], hexs[n-1]);
			next (l.rbegin ())->ends.to = to;
			elt.ends.from = from;
		} while (elt.is_loop ());
	}
		



//	/* Figure out the links (or neighbours) between each hex */
//	for (int i = 0; i+1 < n; i++) {
//cout << "In loop\n";
//		// A path always exists
//		do {
//cout << "Trying to get a link\n";
//			auto [t, f] = link_between(hexs[i], hexs[i+1]);
//			ends[i].to = t;
//			ends[i+1].from = f;
//		} while (!(!ends[i].is_loop() || hexs[i].size == 0));
//	}
//	// Make sure the last itinerary isn't a loop
//	if (n > 1) {
//		do {
//cout << "Trying to solve last loop\n";
//			auto [t, f] = link_between(hexs[n-2], hexs[n-1]);
//			ends[n-2].to = t;
//			ends[n-1].from = f;
//		} while (!(!ends[n-1].is_loop() || hexs[n-1].size == 0));
//	}
//
//	list <Itinerary> l;
//	for (int i = 0; i < n; i++) {
//		l.push_back (Itinerary (hexs[i], ends[i]));
//	}

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
