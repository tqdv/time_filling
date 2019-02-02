#ifndef TIME_FILLING_HPP
#define TIME_FILLING_HPP

#include <list>
#include "point.hpp"
#include "hexagon.hpp"


namespace t_fl {

struct Endpoints {
	HexPoint from;
	HexPoint to;

	bool is_loop () const;
};

struct Itinerary {
	Hexagon hex;
	Endpoints ends;

	Itinerary (Hexagon, Endpoints);
};



std::list<Itinerary> get_itinerary (Hexagon_v, HexPoint, HexPoint);

}  // namespace t_fl

#endif  // TIME_FILLING_HPP
