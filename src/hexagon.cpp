#include <optional>
#include <array>
#include <random>
#include <iostream>
#include <cmath>
#include "hexagon.hpp"

/*
 *  0 1
 * 5 6 2
 *  4 3
 */

const int CENTER = 6; 


bool hexagon_path(int from, int to, HexagonPath &path) {
	if (from < 0 || from == CENTER || from >= 6 
	    || to < 0 || to == CENTER || to >= 6
	    || from == to)
		return false;

	path[0] = from;
	path[6] = to;

	int distance, direction, oppdir; // direction of (from -> to)
	for (int i = 1; i <= 3; i++) {
		if ((from + i) % 6 == to) {
			distance = i;
			direction = 1;
		} else if ((to + i) % 6 == from) {
			distance = i;
			direction = (6 - 1);
		}
	}
	oppdir = (6 - direction); // positive so % works correctly

	if (distance == 1) {
		path[1] = (from + oppdir) % 6;
		path[2] = (path[1] + oppdir) % 6;
		path[3] = CENTER;
		path[4] = (path[2] + oppdir) % 6;
		path[5] = (path[4] + oppdir) % 6;
		
	} else {
		std::random_device rd;
		std::minstd_rand gen;
		gen.seed(rd());
		std::bernoulli_distribution randbool(0.5);
		bool first = randbool(gen);

		if(distance == 2) { 
			/* Randomly decide whether to go
			 *         __
			 * /_/\    _ \
			 *  __/ or \\/   
			 */
			if (first) {
				path[1] = (from + direction) % 6;
				path[2] = CENTER;
				path[3] = (from + oppdir) % 6;
				path[4] = (path[3] + oppdir) % 6;
				path[5] = (path[4] + oppdir) % 6;
			} else {
				path[1] = (from + oppdir) % 6;
				path[2] = (path[1] + oppdir) % 6;
				path[3] = (path[2] + oppdir) % 6;
				path[4] = CENTER;
				path[5] = (from + direction) % 6;
			}
		} else /* distance == 3 */ {
			path[3] = CENTER;
			
			/* Randomly decide to first go following direction, or the opposite */
			if (first) {
				path[1] = (from + direction) % 6;
				path[2] = (path[1] + direction)  % 6;
				path[4] = (from + oppdir) % 6;
				path[5] = (path[4] + oppdir) % 6;
			} else {
				path[1] = (from + oppdir) % 6;
				path[2] = (path[4] + oppdir) % 6;
				path[4] = (from + direction) % 6;
				path[5] = (path[1] + direction)  % 6;
			}
		}
	}
			
	return true;
}

bool hexagon_positions(HexagonPath &path, const Point &center, float radius, float offset, PointPath &pos) {
	if (std::signbit(radius)) {
		return false;
	}

	float angle;
	for(int i = 0; i < 7; i++) {
		if (path[i] == CENTER) {
			pos[i] = center;
		} else {
			angle = path[i] * M_PI / 3 + offset;
			pos[i].x = radius * cos(angle);
			pos[i].y = radius * sin(angle);
		}
	}

	return true;
}

