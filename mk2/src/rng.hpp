#ifndef RNG_HPP
#define RNG_HPP

#include <random>


namespace t_fl {

using RNG = std::mt19937;
RNG init_rng();
static RNG rng = init_rng();

/* Random integer in [a, b] */
int randint (int a, int b);

} // namespace t_fl

#endif  // RNG_HPP
