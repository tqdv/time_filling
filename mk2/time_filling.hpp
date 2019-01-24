#ifndef TIME_FILLING_HPP
#define TIME_FILLING_HPP

#include <vector>
#include "point.hpp"
#include "hexagon.hpp"

namespace t_fl {

std::vector<t_fl::HexPoint> path_random (std::vector<t_fl::Hexagon>, t_fl::HexPoint, t_fl::HexPoint);

}  // namespace t_fl

#endif  // TIME_FILLING_HPP
