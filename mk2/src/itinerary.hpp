#ifndef ITINERARY_HPP
#define ITINERARY_HPP

#include "hexagon.hpp"

namespace t_fl {

/* Endpoints is a pair of HexPoints that define the ends of a path */
struct Endpoints {
	HexPoint from;
	HexPoint to;

	Endpoints ();
	Endpoints (HexPoint, HexPoint);

	bool is_loop () const;
};

/* An Itinerary is a path through a hexagon, defined by the said hexagon
 * and endpoints */
struct Itinerary {
	Hexagon hex;
	Endpoints ends;

	Itinerary (Hexagon, Endpoints);
	Itinerary (Hexagon);

	/* Check if the itinerary makes you return to your starting point */
	bool is_loop() const;
};

} // namespace t_fl

#endif  // ITINERARY_HPP
