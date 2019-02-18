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

/* Takes a vector of Hexagons and start and finish points, and turns it into
 * and itinerary for each hexagon */
std::list<Itinerary> get_itinerary (Hexagon_v, HexPoint, HexPoint);

/* Finds a path of nodes in a hexagon */
Node_v node_path (Node, Node);

/* Finds a simple (hardcoded) path through a hexagon */
std::list <Itinerary> simple_path (cr <Itinerary>);

/* Rules on how to break down the itineraries into smaller pieces */
std::list <Hexagon> simplify_hex (cr <Itinerary> itin);
std::list <Hexagon> simplify_hex1 (cr <Itinerary> itin);
std::list <Hexagon> simplify_hex2 (cr <Itinerary> itin);

}  // namespace t_fl

#endif  // TIME_FILLING_HPP
