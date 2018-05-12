#ifndef TFILL_HEXAGON_HPP
#define TFILL_HEXAGON_HPP

#include <optional>
#include <vector>

typedef enum shapes {
	hexagon,
	triangle,
} Shape;

typedef struct Point {
	float x;
	float y;
} Point;

typedef std::vector<int> Path;
typedef std::vector<Point> PointPath;

std::optional<PointPath> shape_positions (Shape s, int from, int to,
   const Point &center, float radius, float offset = 0.0);
/* Returns a the points forming a path in `s` with the given parameters
 * Returns None if it's not possible
 */

std::optional<Path> shape_path (Shape s, int from, int to);
/* from, to in [|0; n-1|]; from <> to;
 *    where n is the number of outer vertices
 * Returns a path from edge to edge in the shape `s`, going over all points
 * with only movements to neighbour points
 * Returns None if the assertions are false or the path doesn't exist
 */

std::optional<PointPath> path_positions (
   Shape s, const Path &p, const Point &center, float radius, float offset);
/* radius > 0; s in shapes
 * Returns the positions of the points of `path`, given the coordinates
 * of `center`, a `radius` and `offset` the trigonometric angle from the
 * horizontal in radians.
 * Returns None if the assertions are false
 */

std::optional<Path> hexagon_path (int from, int to);
std::optional<PointPath> hexagon_positions (
   const Path &path, const Point &center, float radius, float offset);
/* Hexagon: n = 6 */

std::optional<Path> triangle_path (int from, int to);
std::optional<PointPath> triangle_positions (
   const Path &path, const Point &center, float radius, float offset);

#endif  // TFILL_HEXAGON_HPP
