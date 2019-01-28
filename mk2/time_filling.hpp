#ifndef TIME_FILLING_HPP
#define TIME_FILLING_HPP

#include <list>
#include <vector>
#include <utility>
#include <random>
#include "point.hpp"
#include "hexagon.hpp"


namespace t_fl {

using RNG = std::mt19937;
RNG init_rng();
static RNG rng = init_rng();

/* Random integer in [a, b] */
int randint (int a, int b);

using HexPoint2 = std::pair<HexPoint, HexPoint>;
using Hexagon2 = std::pair<Hexagon, Hexagon>;
using Hexagon_v2 = std::pair<Hexagon_v, Hexagon_v>;

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

std::list<Itinerary> get_itinerary (Hexagon_v, HexPoint, HexPoint);

}  // namespace t_fl

#endif  // TIME_FILLING_HPP
