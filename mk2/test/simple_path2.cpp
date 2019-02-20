#include <iostream>
#include "time_filling.hpp"
#include "utils.hpp"

using std::cout;

int main () {
	t_fl::init_default_base (1);
	t_fl::Coord c (0, 0);
	t_fl::Coord a (0, -1);
	t_fl::Coord b (1, -1);
	t_fl::Hexagon h (c, 1);
	t_fl::Endpoints e (a, b);
	t_fl::Itinerary itin (h, e);

	t_fl::Hexagon_v out = simplify_hex1 (itin);

	cout << "Simple test to see if simple_path works\n";
	cout << "This is for debugging a weird case where only the distance == 1\n";
	cout << "case in simplify_hex1 gives the same values for all hexs from [1]\n";
	cout << "to [5]\n";
	for (auto h : out) {
		cout << "(";
		{
		const auto &[x, y] = h.center;
		cout << "(" << x << ", " << y << ")";
		}
		cout << ", ";
		cout << h.size << ")\n";
	}
	/* Sample wrong output:
	 *
	 * Simple test to see if simple_path works
	 * This is for debugging a weird case where only the distance == 1
	 * case in simplify_hex1 gives the same values for all hexs from [1]
	 * to [5]
	 * ((0, -1), 0)
	 * ((1, 0), 0)
	 * ((1, 0), 0)
	 * ((1, 0), 0)
	 * ((1, 0), 0)
	 * ((1, 0), 0)
	 * ((1, -1), 0)
	 */

	/* The bug was that in node_path, the distance was calculated incorrectly,
	 * giving 5 instead of 1 because of modular arithmetic and negative numbers.
	 * Consequently, the switch statement was never run.
	 *
	 * Also, the direction was badly calculated too, but it didn't "break" the
	 * code, just the correctness of it.
	 */

	return 0;
}
