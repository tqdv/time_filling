#include <array>
#include <iostream>

template <std::size_t N>
void print_array (const std::array<int, N> &a) {
	std::cout << "[";
	for (int i = 0; i < N - 1; i++) {
		std::cout << a[i] << ", ";
	}
	std::cout << a[N - 1] << "]";
}
