#ifndef HEXAGON_OPS_HPP
#define HEXAGON_OPS_HPP

#include "hexagon.hpp"
#include "point.hpp"
#include "itinerary.hpp"
#include "utils.hpp"

namespace t_fl {

using HexPoint2 = std::pair<HexPoint, HexPoint>;
using Hexagon2 = std::pair<Hexagon, Hexagon>;
using Hexagon_v2 = std::pair<Hexagon_v, Hexagon_v>;

/* Chooses a pair of Hexagons from $left x $right that are neighbours */
Hexagon2 pick_neighbour_pair (cr <Hexagon_v> left, cr <Hexagon_v> right);

/* Finds the Hexagons in $right that are
 * the same size as $left and closest to it */
Hexagon_v closest_hexs (cr <Hexagon> left, cr <Hexagon> right);

/* Returns the Hexagons one size smaller in $left and $right
 * that can serve as bridges */
Hexagon_v2 closer_hexs (cr <Hexagon>, cr <Hexagon>);

/* Finds a pair of Hexpoints that make a bridge between $left and $right */
HexPoint2 link_between (cr <Hexagon> left, cr <Hexagon> right);

} // namespace t_fl

#endif // HEXAGON_OPS_HPP
