#include <iostream>
#include <vector>

template <typename T>
void print_vector (constref<std::vector<T>> v) {
	const int n = v.size ();

	std::cout << "[";
	for (int i = 0; i < n - 1; ++i) {
		std::cout << v[i] << ", ";
	}
	std::cout << v[n - 1] << "]";
}
