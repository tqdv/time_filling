#ifndef TIME_FILLING_HPP
#define TIME_FILLING_HPP

#include <list>
#include "point.hpp"
#include "hexagon.hpp"
#include "itinerary.hpp"
#include "utils.hpp"


namespace t_fl {

/* Helper function for the next one */
HexPoint assign_next_bridge (cr <Hexagon_v> hexs, std::list <Itinerary> &l);

std::list<Itinerary> get_itinerary (Hexagon_v, HexPoint, HexPoint);


/* Rules on how to break down the itineraries into smaller pieces */
std::list <Hexagon> simplify_hex (cr <Itinerary> itin);
std::list <Hexagon> simplify_hex1 (cr <Itinerary> itin);
std::list <Hexagon> simplify_hex2 (cr <Itinerary> itin);

}  // namespace t_fl

#endif  // TIME_FILLING_HPP
