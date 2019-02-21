#include "itinerary.hpp"

namespace t_fl {

/* Endpoints */
Endpoints::Endpoints () { }

Endpoints::Endpoints (HexPoint f, HexPoint t) : from (f), to (t) { }


bool Endpoints::is_loop () const {
	return from == to;
}

/* Itinerary */

Itinerary::Itinerary (Hexagon h, Endpoints e) : hex(h), ends(e) { }

Itinerary::Itinerary (Hexagon h) : hex(h) { }

Itinerary::operator Hexagon () {
	return hex;
}

bool Itinerary::is_loop () const {
	if (hex.size == 0) { return false; }

	bool r = false;

	Hexagon a = Hexagon (ends.from);
	Hexagon b = Hexagon (ends.to);
	// Deal with loops on all levels beneath the hexagon
	for (int i = 0; i <= hex.size -1; i++) {
		if (a == b) {
			r = true;
		}
		a = a.bigger();
		b = b.bigger();
	}

	return r;
}

} // namespace t_fl
