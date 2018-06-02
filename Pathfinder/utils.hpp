#ifndef TFILL_UTILS_HPP
#define TFILL_UTILS_HPP

#include <vector>
#include <optional>


template <typename T>
using Maybe = std::optional<T>;
template <typename T>
using constref = const T&;


template <typename T>
void print_vector (const std::vector<T> &v);
/* Pretty prints a vector */

#include "utils.ipp"

#endif  // TFILL_UTILS_HPP
