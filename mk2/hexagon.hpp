#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include <vector>
#include "point.hpp"
#include "utils.hpp"

namespace t_fl {

/* List of coordinates of each $size level basis in the basis just below */
static std::vector<Coord2> bases;

/* Initializes $t_fl::bases to the default coordinates up to size $n */
/* The default is 0 is identity matrix,
 * odds have positive rotation,
 * even have negative rotation.
 * That makes it so that every other base is identical */
void init_default_base(int n);

struct Hexagon {
	Coord center;  // depends on t_fl::bases
	int size;  // 0 is a HexPoint

	Hexagon (Coord, int); 
	operator HexPoint();
};
Coord operator- (cr <Hexagon>, cr <Hexagon>);

bool are_neighbours (cr <Hexagon>, cr <Hexagon>);

}  // namespace t_fl

#endif  // HEXAGON_HPP
