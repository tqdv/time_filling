#ifndef POINT_HPP
#define POINT_HPP

#include <utility> // std::pair
#include <ostream> // friend std::ostream
#include "utils.hpp"

namespace t_fl {

using Real = float;  // Use this to set precision, maybe

struct Point {
	Real x;
	Real y;

	Point (Real, Real);
	friend std::ostream& operator<< (std::ostream&, cr<Point>);
};

/* x and y are coordinates along the following axis of a plane :
 * /-> 30° (y)
 * -->   0° (x)
 */
struct HexPoint {
	int x;
	int y;

	HexPoint ();
	HexPoint (int, int);

	operator Point ();
};
bool operator== (cr <HexPoint>, cr <HexPoint>);


/* The difference between T_Coord and HexPoint is that the former represents
 * coordinates in any 2D basis, whereas HexPoint represents them
 * in the Hexagonal 2D basis defined above */
// We templatize Coord to use both int and float types
template <class T> struct T_Coord : public std::pair<T, T> {
	using std::pair<T, T>::pair; // inherit constructors
};

template <class T> T_Coord operator+ (cr <T_Coord <T>>, cr <T_Coord <T>>);
template <class T> T_Coord operator- (cr <T_Coord <T>>, cr <T_Coord <T>>);

template <class T> T_Coord operator* (cr <T_Coord <T>>, cr <int>);
template <class T> T_Coord operator* (cr <int> a, cr <T_Coord <T>> b);


struct Coord : public T_Coord<int> {
	using T_Coord<int>::T_Coord;
	operator HexPoint ();
}

/* Calculate norm as defined as … */
int norm (cr <Coord>);
int dist (cr <Coord>, cr <Coord>);

using Coord2 = std::pair<Coord, Coord>;

struct FCoord : public T_Coord <float> {
	using T_Coord <float>::T_Coord;

	operator Coord ();
}
using FCoord2 = std::pair <FCoord, FCoord>;

} // namespace t_fl

#endif  // POINT_HPP
