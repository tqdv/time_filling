#include "rng.hpp"
#include <random>

namespace t_fl {

RNG init_rng() {
	RNG rng;
	std::random_device rd;
	rng.seed(rd());
	return rng;
}

int randint (int a, int b) {
	std::uniform_int_distribution<> dis(a, b);
	return dis(rng);
}

} // namespace t_fl
