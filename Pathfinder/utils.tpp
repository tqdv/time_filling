#include <iostream>
#include <vector>

template <typename T>
void print_vector (const std::vector<T> &v) {
	int n = v.size ();

	std::cout << "[";
	for (int i = 0; i < n - 1; ++i) {
		std::cout << v[i] << ", ";
	}
	std::cout << v[n - 1] << "]";
}
