#ifndef TIME_FILLING_HPP
#define TIME_FILLING_HPP

#include <list>
#include "point.hpp"
#include "hexagon.hpp"
#include "utils.hpp"


namespace t_fl {

/* Endpoints is a pair of HexPoints that define the ends of a path */
struct Endpoints {
	HexPoint from;
	HexPoint to;

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



/* Helper function for the next one */
HexPoint assign_next_bridge (cr <vector <Hexagon>> hexs, std::list <Itinerary> &l);
std::list<Itinerary> get_itinerary (Hexagon_v, HexPoint, HexPoint);

}  // namespace t_fl

#endif  // TIME_FILLING_HPP
