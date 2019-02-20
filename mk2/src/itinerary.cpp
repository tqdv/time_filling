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
	return hex.size != 0 && ends.is_loop ();
}

} // namespace t_fl
