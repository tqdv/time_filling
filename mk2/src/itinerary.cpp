#include "itinerary.hpp"

namespace t_fl {

/* Endpoints */
bool Endpoints::is_loop () const {
	return from == to;
}

/* Itinerary */

Itinerary::Itinerary (Hexagon h, Endpoints e) : hex(h), ends(e) { }

Itinerary::Itinerary (Hexagon h) : hex(h) { }

bool Itinerary::is_loop () const {
	return hex.size != 0 && ends.is_loop ();
}

} // namespace t_fl
