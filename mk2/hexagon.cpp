#include "hexagon.hpp"

#include <vector>
#include "point.hpp"

namespace t_fl {

Hexagon::Hexagon (HexPoint c, int s, std::vector<cr <Coord>> b) 
: center (c), size (s), bases (b) {
}

}  // namespace t_fl
