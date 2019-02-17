#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include <vector>
#include "point.hpp"
#include "utils.hpp"

namespace t_fl {

/* List of coordinates of each $size level basis in the basis just below */
/* This allows for conversion between different hexagon sizes */
static std::vector<Coord2> bases;

/* Initializes $t_fl::bases to the default conversion bases
 * up to Hexagon size $n */
/* The default is:
 * size 0 -> size 0 is the identity matrix,
 * odd bases have positive rotation compared to the previous one,
 * and even ones have negative rotation.
 * That makes it so that every other base is aligned */
void init_default_base(int n);

/* Get coordinates of a Coord, in the basis below */
Coord lower (cr <Coord>, int);

struct Hexagon {
	Coord center;  // meaning depends on t_fl::bases and $size
	int size;  // 0 is a HexPoint

	Hexagon ();
	Hexagon (Coord, int); 
	Hexagon (HexPoint, int);

	using Hexagon_v = std::vector<Hexagon>;  // Needed because it's recursive
	/* Get children */
	Hexagon_v explode() const;
	/* Get a hexagon one size smaller with the same center */
	Hexagon smaller() const;

	/* Converts the center to a HexPoint */
	operator HexPoint();
};

using Hexagon_v = std::vector<Hexagon>;

/* Distance between the two hexagon centers, assuming they are the same size */
int dist (cr <Hexagon>, cr <Hexagon>);

/* Whether the hexagons are neighbours, assuming they are the same size */
bool are_neighbours (cr <Hexagon>, cr <Hexagon>);

}  // namespace t_fl

#endif  // HEXAGON_HPP
