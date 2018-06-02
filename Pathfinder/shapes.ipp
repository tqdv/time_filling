#ifndef TFILL_SHAPES_IPP
#define TFILL_SHAPES_IPP

#include <cmath>

Angle normalize_angle (Angle angle) {
	return fmod (angle, 2 * M_PI);
}

#endif  // TFILL_SHAPES_IPP
