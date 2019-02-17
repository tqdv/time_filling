#include "time_filling.hpp"
#include "point.hpp"

using t_fl::Point;

typedef HexPath array <int, 7>; 


/* level 0 is a hexagon laid on its side */
/*  _
 * / \
 * \_/
 */


/* level 1 is  a grouping of 7 hexagons */

/* level 2 is a grouping of 7 level 1, with 49 hexagons in total */
 /* it is offset by an angle of asin(sqrt(3/28)) ≃ 19°
 * compared to level 1 (or the chosen level 3 / disposition)
 */


/* Disposition of the 8 level 2 considered : */
/*     0
 *  1     2
 *     3     4
 *  5     6
 *     7
 */
const int NB_L2 = 8;
/* Coordinates of the centers of L2 structures with the unit being 7 */
const array <HexPoint, NB_L2> l2 = {
	( 1, -2), ( 0, -1), ( 1, -1), ( 0,  0),
	( 1,  0), (-1,  1), ( 0,  1), (-1,  2),
};


/* Possible paths for level 2 */
typedef Path array <int, NB_L2>;

/* We want it to start from 0 or 1,
 * and end on 4, with the last two being 6 and 2
 */
const array <Path, 5> paths = {
	{0, 1, 5, 7, 3, 2, 6, 4},  // 0 -> 2
	{0, 1, 3, 5, 7, 6, 2, 4},  // 0 -> 6 (VAR_PATH)
	{1, 5, 7, 3, 0, 2, 6, 4},  // 1 -> 2
	{1, 0, 3, 5, 7, 6, 2, 4},  // 1 -> 6 (NB_PATHS)
	{0, 1, 5, 3, 7, 6, 2, 4},  // 0 -> 6 (ALT_PATH)
}
const NB_PATHS = 4;
const VAR_PATH = 1;  // Path with a possible variant
const ALT_PATH = 4;  // The alternative path


/* Finding paths inside the level 2s */
typedef Path1 array <HexPath &, NB_L2>;

/* Uses the the level 2 path just before the index
 * or the neighbour level 2 when it's first or last
 * to decide what path to take inside the level 2.
 */
HexPath & level1_path (cr <Path>, cr <Path1>, int i); 
