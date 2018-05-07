#ifndef HEXAGON_H
#define HEXAGON_H

// v to move somewhere
#include <array>
#include <iostream>

typedef struct Point {
	float x;
	float y;
} Point;

typedef std::array<int, 7> HexagonPath;
typedef std::array<Point, 7> PointPath;

	

bool hexagon_path(int from, int to, HexagonPath &path);
/* from in 0..5; to in 0..5
 * Fills `path` with a path from an external side of the hexagon to another,
 * returns false if path doesn't exist
 */
template<std::size_t N>
// v to move to a .tpp
void print_array(const std::array<int, N> &a) {
	std::cout << "[";
	for (int i = 0; i < N - 1; i++) {
		std::cout << a[i] << ", " ;
	}
	std::cout << a[N - 1] <<  "]";
}
/* Pretty prints an int array */
bool hexagon_positions(HexagonPath &path, const Point &center, float radius, float offset, PointPath &pos);
/* radius > 0
 * Fills `pos` with the positions of points of `path`, given the coordinates
 * of `center` and a `radius`
 */

#endif
