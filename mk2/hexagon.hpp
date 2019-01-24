#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include <vector>
#include "point.hpp"
#include "utils.hpp"

namespace t_fl {

struct Hexagon {
	HexPoint center;
	int size;
	std::vector<cr <Coord>> bases;

	Hexagon (HexPoint, int, std::vector<cr <Coord>>); 
};

}  // namespace t_fl

#endif  // HEXAGON_HPP
