#include "shapes.hpp"

#include <cmath>
#include <optional>
#include <random>
#include <iterator>
#include <functional>  // for bind, etc...
#include <algorithm>  // for transform, etc...
#include <cstdlib>  // for div

const struct {
	int hexagon = 6;
	int triangle = 3;
} V;  // Vertices

const struct {
	int hexagon = 7;
	int triangle = 3;
} P;  // Points

/* Needed in structure_positions */
int points (Shape s) {
	switch (s) {
	case hexagon:
		return P.hexagon;
	case triangle:
		return P.triangle;
	default:
		return 0;
	}
}


/* WIP */
std::optional<PointPath> structure_positions (
   const std::vector<Structure> &structures, const Point &center,
   const Flow &flow) {
	if (structures.size() == 0) {
		return {};
	}

	int nb_points = 1;
	for (Structure s : structures) {
		nb_points *= points (s.shape);
	}
	PointPath pos (nb_points);

	bool status = write_structure_pos (structures, 0, center, flow,
	   pos.begin(), pos.end());

	if (status) {
		return pos;
	} else {
		return {};
	}
}
/* WIP */
// I need to get from and to correctly, and make it work with the structure offset
// pass from and to as arguments (works for top level)
// and calculate for and to using the angles (the info is here)
bool write_structure_pos (const std::vector<Structure> &structures, int index,
   const Point &center, const Flow &flow, PP_it it, const PP_it end) {

	int levels = structures.size();
	if (index >= levels) {
		return false;
	}

	const Structure &st = structures[index];

	// TODO: Make it pipe?
	Flow loc_flow = flow;
	flow_add_angle (loc_flow, - st.offset);

	std::optional<Route> route = flow_route (st.shape, loc_flow);
	if (!route.has_value()) {
		return false;
	}

	std::optional<Path> path = shape_path (st.shape, route->from, route->to);
	if (!path.has_value()) {
		return false;
	}

	bool status;
	if (index == levels - 1) {
		/* Last level, actually writing */
		std::optional<Node_Point_f> pos_f = st_position (st, center);
		if (!pos_f.has_value()) {
			return false;
		}
		status = write_positions (*path, *pos_f, it, end);
		return status;
	} else {

		std::optional<PointPath> pos = path_positions (st, *path, center);
		if (!pos.has_value()) {
			return false;
		}

		int n = points (st.shape);
		std::div_t d = div(std::distance (it, end), n);
		if (d.rem != 0) {
			return false;
		}

		std::optional<Node_Index_Flow_f> nif_f;
		nif_f = node_index_flow (st.shape, *path, loc_flow, st.offset);
		if (!nif_f.has_value()) {
			return false;
		}

		auto it_pos = [&d, &it](int x) {
			PP_it _it = it;
			std::advance (_it, x * d.quot);
			return _it;
		};
		
		for (int i; i < n; ++i) {
			status = write_structure_pos
			   (structures, (index + 1), (*pos)[i], (*nif_f)(i), it_pos (i), it_pos (i+1));
			if (!status) {
				return false;
			}
		}

		return true;
	}
}


std::optional<PointPath> shape_positions (const Structure &st, Node from,
   Node to, const Point &center) {

	std::optional<Path> path = shape_path (st.shape, from, to);
	if (!path.has_value ()) {
		return {};
	}

	std::optional<PointPath> pos = path_positions (st, *path, center);
	return pos;
}


std::optional<Path> shape_path (Shape s, Node from, Node to) {
	switch (s) {
	case hexagon:
		return hexagon_path (from, to);
	case triangle:
		return triangle_path (from, to);
	default:
		return {};
	}
}


std::optional<PointPath> path_positions (const Structure &st, const Path &path,
   const Point &center) {
	int nbPoints = points (st.shape);
	if (std::signbit (st.radius) || nbPoints <= 0) {
		return {};
	}

	std::optional<Node_Point_f> pos_f = st_position (st, center);
	if (!pos_f.has_value()) {
		return {};
	}
	
	PointPath pos (nbPoints);
	bool status = write_positions (path, *pos_f, pos.begin(), pos.end()); 
	if (status) {
		return pos;
	}
	return {};
}

void flow_add_angle (Flow &flow, Angle angle) {
	flow.enter += angle;
	flow.exit += angle;
}

void flow_normalize (Flow &flow) {
	flow.enter = fmod (flow.enter, 2 * M_PI);
	flow.exit = fmod (flow.exit, 2 * M_PI);
}


std::optional<Route> flow_route (Shape shape, const Flow &flow) {
	switch (shape) {
	case hexagon:
		return hexagon_route (flow);
	case triangle:
		return triangle_route (flow);
	default:
		return {};
	}
}

std::optional<Node_Index_Flow_f> node_index_flow (Shape shape, const Path &path,
   const Flow &flow, Angle offset) {
	switch (shape) {
	case hexagon:
		return hexagon_nif (path, flow, offset);
	case triangle:
		return triangle_nif (path, flow, offset);
	default:
		return {};
	}
}



std::optional<Node_Point_f> st_position (const Structure &st, const Point &center) {
	using namespace std::placeholders;
	switch (st.shape) {
	case hexagon:
		return std::function<Point(Node)> (std::bind
		   (hexagon_position, _1, center, st.radius, st.offset)
		);
	case triangle:
		return std::function<Point(Node)>  (std::bind
		   (triangle_position, _1, center, st.radius, st.offset)
		);
	default:
		return {};
	}
}

bool write_positions (const Path &path, Node_Point_f position,
   PP_it it, const PP_it end) {
	if (std::distance (it, end) != path.size()) {
		return false;
	}

	for (Node node : path) {
		*it = position (node);
		++it;
	}

	return true;
}


/* HEXAGON FUNCTIONS */
/*
 *  0 1
 * 5 6 2
 *  4 3
 */
const int HEX_CENTER = 6;

std::optional<Path> hexagon_path (int from, int to) {
	if (from < 0 || from == HEX_CENTER || from >= V.hexagon || to < 0
	    || to == HEX_CENTER || to >= V.hexagon || from == to)
		return {};

	Path path (P.hexagon);
	path[0] = from;
	path[P.hexagon - 1] = to;

	int distance, direction, oppdir;  // direction of (from -> to)
	for (int i = 1; i < V.hexagon; ++i) {
		if ((from + i) % V.hexagon == to) {
			distance = (i > 3 ? V.hexagon - i : i);
			direction = (i > 3 ? V.hexagon - 1 : 1);
		}
	}
	oppdir = (V.hexagon - direction);  // positive so % works correctly

	if (distance == 1) {
		path[1] = (from + oppdir) % V.hexagon;
		path[2] = (path[1] + oppdir) % V.hexagon;
		path[3] = HEX_CENTER;
		path[4] = (path[2] + oppdir) % V.hexagon;
		path[5] = (path[4] + oppdir) % V.hexagon;

	} else {
		std::random_device rd;
		std::bernoulli_distribution randbool (0.5);
		bool first = randbool (rd);

		if (distance == 2) {
			/* Randomly decide whether to go
			 *         __
			 * /_/\    _ \
			 *  __/ or \\/
			 */
			if (first) {
				path[1] = (from + direction) % V.hexagon;
				path[2] = HEX_CENTER;
				path[3] = (from + oppdir) % V.hexagon;
				path[4] = (path[3] + oppdir) % V.hexagon;
				path[5] = (path[4] + oppdir) % V.hexagon;
			} else {
				path[1] = (from + oppdir) % V.hexagon;
				path[2] = (path[1] + oppdir) % V.hexagon;
				path[3] = (path[2] + oppdir) % V.hexagon;
				path[4] = HEX_CENTER;
				path[5] = (from + direction) % V.hexagon;
			}
		} else /* distance == 3 */ {
			path[3] = HEX_CENTER;

			/* Randomly decide to first go following direction, or the opposite */
			if (first) {
				path[1] = (from + direction) % V.hexagon;
				path[2] = (path[1] + direction) % V.hexagon;
				path[4] = (from + oppdir) % V.hexagon;
				path[5] = (path[4] + oppdir) % V.hexagon;
			} else {
				path[1] = (from + oppdir) % V.hexagon;
				path[2] = (path[1] + oppdir) % V.hexagon;
				path[4] = (from + direction) % V.hexagon;
				path[5] = (path[4] + direction) % V.hexagon;
			}
		}
	}

	return path;
}


Point hexagon_position (const Node node, const Point &center,
   float radius, Angle offset) {
	if (node == HEX_CENTER) {
		return center;
	}

	float angle = node * M_PI / 3 + offset;
	Point p;
	p.x = center.x + radius * cos (angle);
	p.y = center.y + radius * sin (angle);

	return p;
}


Route hexagon_route (const Flow &flow) {
	/* Find the two closest nodes for each angle, and try to make it work */
	std::tuple<Node, Node> entrances = hexagon_angle_2node (flow.enter);
	std::tuple<Node, Node> exits = hexagon_angle_2node (flow.exit);

	Node in, out;
	in = std::get<0>(entrances);
	out = std::get<0>(exits);

	if (in == out) {
		std::random_device rd;
		std::bernoulli_distribution randbool (0.5);
		bool first = randbool (rd);
		if (first) {
			in = std::get<1>(entrances);
		} else {
			out = std::get<1>(exits);
		}
	}

	return {in, out};
}

std::tuple<Node, Node> hexagon_angle_2node (Angle angle) {
	std::vector<Angle> diff (V.hexagon);
	for (int i = 0; i < V.hexagon; ++i) {
		diff[i] = abs (fmod ((i / 3.0) - (angle / M_PI), 2));
	}
	auto it1 = std::min_element (diff.begin(), diff.end());
	*it1 = 2.0;
	auto it2 = std::min_element (diff.begin(), diff.end());
	auto b = diff.begin();
	
	return {std::distance (b, it1), std::distance (b, it2)};
}

std::optional<Node_Index_Flow_f> hexagon_nif (const Path &path,
   const Flow &flow, Angle offset) {
	return [&path, &flow, &offset](int i) {
		Angle in, out;
		if (i == 0) {
			in = flow.enter;
		} else {
			in = hexagon_angle (path[i-1], path[i]);
		}

		if (i == P.hexagon - 1) {
			out = flow.exit;
		} else {
			out = hexagon_angle (path[i], path[i+1]);
		}
		return Flow {in + offset, out + offset};
	};
}

Angle hexagon_angle (Node from, Node to) {
	if (from == HEX_CENTER) {
		return to * M_PI / 3.0;
	}
	if (to == HEX_CENTER) {
		return - hexagon_angle(to, from);
	}
	if ((from + 1) % V.hexagon == to) {
		return - (from - 2) * M_PI / 3.0;
	}
	if ((to + 1) % V.hexagon == from) {
		return - hexagon_angle (to, from);
	}

	/* Unhandled error */
	return 0;
}


/* TRIANGLE FUNCTIONS */
/*  0
 * 2 1
 */

std::optional<Path> triangle_path (Node from, Node to) {
	if (from < 0 || from >= P.triangle || to < 0 || to >= P.triangle || to == from)
		return {};

	return Path {from, (3 - from - to), to};
}

Point triangle_position (const Node node, const Point &center, float radius,
   Angle offset) {
	
	float angle = node * M_PI * 2 / 3 + offset;
	Point p;
	p.x = center.x + radius * cos (angle);
	p.y = center.y + radius * sin (angle);

	return p;
}


std::optional<Node_Index_Flow_f> triangle_nif (const  Path &path,
   const Flow &flow, Angle offset) {
	return [&path, &flow, &offset](int i) {
		Angle in, out;
		if (i == 0) {
			in = flow.enter;
		} else {
			in = triangle_angle (path[i-1], path[i]);
		}

		if (i == P.triangle - 1) {
			out = flow.exit;
		} else {
			out = triangle_angle (path[i], path[i+1]);
		}
		return Flow {in + offset, out + offset};
	};
}

Route triangle_route (const Flow &flow) {
	/* Find the two closest nodes for each angle, and try to make it work */
	std::tuple<Node, Node> entrances = triangle_angle_2node (flow.enter);
	std::tuple<Node, Node> exits = triangle_angle_2node (flow.exit);

	Node in, out;
	in = std::get<0>(entrances);
	out = std::get<0>(exits);

	if (in == out) {
		std::random_device rd;
		std::bernoulli_distribution randbool (0.5);
		bool first = randbool (rd);
		if (first) {
			in = std::get<1>(entrances);
		} else {
			out = std::get<1>(exits);
		}
	}

	return {in, out};
}

std::tuple<Node, Node> triangle_angle_2node (Angle angle) {
	std::vector<Angle> diff (V.triangle);
	for (int i = 0; i < V.triangle; ++i) {
		diff[i] = abs (fmod ((i * 2.0 / 3.0) - (angle / M_PI), 2));
	}
	auto it1 = std::max_element (diff.begin(), diff.end());
	*it1 = 2.0;
	auto it2 = std::max_element (diff.begin(), diff.end());
	auto b = diff.begin();
	
	return {std::distance (b, it1), std::distance (b, it2)};
}
	

Angle triangle_angle (Node from, Node to) {
	if ((from + 1) % P.triangle == to) {
		return (2 * from + 5) / 6.0 * M_PI; 
	} else {
		return - triangle_angle (to, from);
	}
}
