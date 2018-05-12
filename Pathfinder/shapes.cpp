#include "hexagon.hpp"

#include <array>
#include <cmath>
#include <optional>
#include <random>

const struct {
	int hexagon = 6;
	int triangle = 3;
} V;

std::optional<PointPath> shape_positions (
   Shape s, int from, int to, const Point &center, float radius, float offset) {
	std::optional<Path> path = shape_path (s, from, to);
	if (!path.has_value ()) {
		return {};
	}

	std::optional<PointPath> pos
	   = path_positions (s, *path, center, radius, offset);
	return pos;
}

std::optional<Path> shape_path (Shape s, int from, int to) {
	switch (s) {
	case hexagon:
		return hexagon_path (from, to);
	case triangle:
		return triangle_path (from, to);
	default:
		return {};
	}
}

std::optional<PointPath> path_positions (
   Shape s, const Path &path, const Point &center, float radius, float offset) {
	switch (s) {
	case hexagon:
		return hexagon_positions (path, center, radius, offset);
	case triangle:
		return triangle_positions (path, center, radius, offset);
	default:
		return {};
	}
}

///* WIP */
//
//std::vector<Point> positions (std::vector<Shapes> structure, Point center,
//   float radius, float offset) {
//
//	path<structure.front()>
//	/* Get a path
//	 * Get positions
//	 * Call each next structure with the corresponding, center, from, to and
//	 *    offset
//	 * Join the vectors together
//	 */
//}
///* WIP */

/*
 *  0 1
 * 5 6 2
 *  4 3
 */
const int HEX_CENTER = 6;

std::optional<Path> hexagon_path (int from, int to) {
	if (from < 0 || from == HEX_CENTER || from >= 6 || to < 0
	    || to == HEX_CENTER || to >= 6 || from == to)
		return {};

	Path path (7);
	path[0] = from;
	path[6] = to;

	int distance, direction, oppdir;  // direction of (from -> to)
	for (int i = 1; i < V.hexagon; ++i) {
		if ((from + i) % V.hexagon == to) {
			distance = (i > 3 ? i - 3 : i);
			direction = (i > 3 ? V.hexagon - 1 : 1);
		}
	}
	oppdir = (V.hexagon - direction);  // positive so % works correctly

	if (distance == 1) {
		path[1] = (from + oppdir) % V.hexagon;
		path[2] = (path[1] + oppdir) % V.hexagon;
		path[3] = HEX_CENTER;
		path[4] = (path[2] + oppdir) % V.hexagon;
		path[5] = (path[4] + oppdir) % V.hexagon;

	} else {
		std::random_device rd;
		std::bernoulli_distribution randbool (0.5);
		bool first = randbool (rd);

		if (distance == 2) {
			/* Randomly decide whether to go
			 *         __
			 * /_/\    _ \
			 *  __/ or \\/
			 */
			if (first) {
				path[1] = (from + direction) % V.hexagon;
				path[2] = HEX_CENTER;
				path[3] = (from + oppdir) % V.hexagon;
				path[4] = (path[3] + oppdir) % V.hexagon;
				path[5] = (path[4] + oppdir) % V.hexagon;
			} else {
				path[1] = (from + oppdir) % V.hexagon;
				path[2] = (path[1] + oppdir) % V.hexagon;
				path[3] = (path[2] + oppdir) % V.hexagon;
				path[4] = HEX_CENTER;
				path[5] = (from + direction) % V.hexagon;
			}
		} else /* distance == 3 */ {
			path[3] = HEX_CENTER;

			/* Randomly decide to first go following direction, or the opposite */
			if (first) {
				path[1] = (from + direction) % V.hexagon;
				path[2] = (path[1] + direction) % V.hexagon;
				path[4] = (from + oppdir) % V.hexagon;
				path[5] = (path[4] + oppdir) % V.hexagon;
			} else {
				path[1] = (from + oppdir) % V.hexagon;
				path[2] = (path[1] + oppdir) % V.hexagon;
				path[4] = (from + direction) % V.hexagon;
				path[5] = (path[4] + direction) % V.hexagon;
			}
		}
	}

	return path;
}

std::optional<PointPath> hexagon_positions (
   const Path &path, const Point &center, float radius, float offset) {
	if (std::signbit (radius)) {
		return {};
	}

	PointPath pos (7);
	offset = fmod (offset, 2 * M_PI);

	float angle;
	for (int i = 0; i < 7; ++i) {
		if (path[i] == HEX_CENTER) {
			pos[i] = center;
		} else {
			angle = path[i] * M_PI / 3 + offset;
			pos[i].x = center.x + radius * cos (angle);
			pos[i].y = center.y + radius * sin (angle);
		}
	}

	return pos;
}

/*  0
 * 2 1
 */

std::optional<Path> triangle_path (int from, int to) {
	if (from < 0 || from >= 3 || to < 0 || to >= 3 || to == from)
		return {};

	Path p{from, (3 - from - to), to};
	return p;
}

std::optional<PointPath> triangle_positions (
   const Path &path, const Point &center, float radius, float offset) {
	if (std::signbit (radius)) {
		return {};
	}

	PointPath pos (3);
	offset = fmod (offset, 2 * M_PI);

	float angle;
	for (int i = 0; i < 7; i++) {
		if (path[i] == HEX_CENTER) {
			pos[i] = center;
		} else {
			angle = path[i] * M_PI * 2 / 3 + offset;
			pos[i].x = center.x + radius * cos (angle);
			pos[i].y = center.y + radius * sin (angle);
		}
	}

	return pos;
}
