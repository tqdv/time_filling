namespace t_fl {

/* T_Coord */

template <class T>
T_Coord <T> operator+ (cr <T_Coord <T>> a, cr <T_Coord <T>> b) {
	const auto &[ax, ay] = a;
	const auto &[bx, by] = b;
	return T_Coord <T> (ax + bx, ay + by);
}

template <class T>
T_Coord <T> operator- (cr <T_Coord <T>> l, cr <T_Coord <T>> r) {
	const auto &[lx, ly] = l;
	const auto &[rx, ry] = r;
	return T_Coord <T> (lx - rx, ly - ry);
}

template <class T>
T_Coord <T> operator* (cr <T_Coord <T>> a, cr <int> b) {
	const auto &[x, y] = a;
	return T_Coord <T> (b * x, b * y);
}
template <class T>
T_Coord <T> operator* (cr <int> a, cr <T_Coord <T>> b) { return b * a; }

} // namespace t_fl
