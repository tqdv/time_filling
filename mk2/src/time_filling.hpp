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
Hexagon_v simplify_hex1 (cr <Itinerary> itin);

/* Breaks the hexagon down 2 levels so it can highlight
 * the *-1 hexagon outlines */
Hexagon_v simplify_hex2 (cr <Itinerary> itin);


/* Chooses simplify_hex{1,2} depending on itin.hex.size */
Hexagon_v outline2_hex (cr <Itinerary> itin);


/* Breaks down one level */
std::list <Itinerary> simple_path (cr <Itinerary>);

/* Breaks down 1 or 2 levels, while trying to outline hexagons with
 * simplify_hex2 */
std::list <Itinerary> outline2_path (cr <Itinerary> itin);


/* Helper function to work with Itinerary lists */
/* Replaces it with repl in l, which invalidates it, and adds stuff to l */
void replace_elt
(std::list <Itinerary> &l, std::list<Itinerary>::iterator &it, std::list <Itinerary> repl);

/* Solve the god damn problem */
std::list <HexPoint> rec_simple_path (Hexagon_v hexs, HexPoint from, HexPoint to);

}  // namespace t_fl

#endif  // TIME_FILLING_HPP
