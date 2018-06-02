#include "hexagon.hpp"

#include "shapes.hpp"

#include <tuple>
#include <iterator>
#include <random>
#include <algorithm>  // for min_element


/*
 *  0 1
 * 5 6 2
 *  4 3
 */

const int POINTS = 7;
const int OUTER = 6;
const int HEX_CENTER = 6;


bool Hexagon::valid_args (float radius, Angle offset) {
	return (radius >= 0.0);
}


Maybe<Hexagon> Hexagon::make_hexagon (float radius, Angle offset) {
	if (Shape::valid_args (POINTS) && valid_args (radius, offset)) {
		return Hexagon (radius, normalize_angle (offset));
	}

	return {};
}


Hexagon::Hexagon (float radius, Angle offset)
	: Shape (POINTS)
	, radius (radius)
	, offset (offset)
{ }


Maybe<PointPath> Hexagon::pointpath_p (constref<Flow> flow,
   constref<Point> center) const {
	Route route = flow_route (flow);
	
	Maybe<Path> path = route_path (route);
	if (!path.has_value()) { return {}; }
	
	PointPath pos = path_positions (*path, center);

	return pos;
}


Maybe<PointFlows> Hexagon::pointflows_p (constref<Flow> flow,
   constref<Point> center) const {
	Route route = flow_route (flow);
	
	Maybe<Path> path = route_path (route);
	if (!path.has_value()) { return {}; }
	
	PointPath pos = path_positions (*path, center);
	FlowPath flows = path_flows (*path, flow);

	return PointFlows {pos, flows};
}


Flow Hexagon::flow_local_flow (constref<Flow> flow) const {
	return Flow {flow.enter - offset, flow.exit - offset};
}


inline Angle Hexagon::node_angle_dist (Node i, Angle angle) {
	return fabs (fmod (i * M_PI / 3.0 - angle, 2 * M_PI));
}


std::tuple<Node, Node> Hexagon::angle_2node (Angle angle) {
	std::vector<Angle> diff (OUTER);
	for (int i = 0; i < OUTER; ++i) {
		diff[i] = node_angle_dist (i, angle);
	}

	auto it1 = std::min_element (diff.begin(), diff.end());
	*it1 = 2.0;
	auto it2 = std::min_element (diff.begin(), diff.end());
	auto b = diff.begin();
	
	return {std::distance (b, it1), std::distance (b, it2)};
}


Route Hexagon::flow_route (constref<Flow> flow) const {
	using std::get;
	Flow loc_flow = flow_local_flow (flow);

	// We're comparing to angles that go from the center to the edge
	std::tuple<Node, Node> entrances = angle_2node (loc_flow.enter + M_PI);
	std::tuple<Node, Node> exits = angle_2node (loc_flow.exit);

	Node in, out;
	in = get<0> (entrances);
	out = get<0> (exits);


	if (in == out) {
		Angle d_in = node_angle_dist (get<1> (entrances), loc_flow.enter + M_PI);
		Angle d_out = node_angle_dist (get<1> (exits), loc_flow.exit);

		if (d_in < d_out) {
			in = get<1> (entrances);
		} else {
			out = get<1> (exits);
		}
	}

	return {in, out};
}


Maybe<Path> Hexagon::route_path (constref<Route> route) {
	Node from = route.from;
	Node to = route.to;

	if (from < 0 || from == HEX_CENTER || from >= POINTS || to < 0
	    || to == HEX_CENTER || to >= POINTS || from == to)
		return {};

	Path path (POINTS);
	path[0] = from;
	path[POINTS - 1] = to;

	int distance, direction, oppdir;  // direction of (from -> to)
	for (int i = 1; i < OUTER; ++i) {
		if ((from + i) % OUTER == to) {
			distance = (i > 3 ? OUTER - i : i);
			direction = (i > 3 ? OUTER - 1 : 1);
		}
	}
	oppdir = (OUTER - direction);  // positive so % works correctly

	if (distance == 1) {
		path[1] = (from + oppdir) % OUTER;
		path[2] = (path[1] + oppdir) % OUTER;
		path[3] = HEX_CENTER;
		path[4] = (path[2] + oppdir) % OUTER;
		path[5] = (path[4] + oppdir) % OUTER;

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
				path[1] = (from + direction) % OUTER;
				path[2] = HEX_CENTER;
				path[3] = (from + oppdir) % OUTER;
				path[4] = (path[3] + oppdir) % OUTER;
				path[5] = (path[4] + oppdir) % OUTER;
			} else {
				path[1] = (from + oppdir) % OUTER;
				path[2] = (path[1] + oppdir) % OUTER;
				path[3] = (path[2] + oppdir) % OUTER;
				path[4] = HEX_CENTER;
				path[5] = (from + direction) % OUTER;
			}
		} else /* distance == 3 */ {
			path[3] = HEX_CENTER;

			/* Randomly decide to first go following direction, or the opposite */
			if (first) {
				path[1] = (from + direction) % OUTER;
				path[2] = (path[1] + direction) % OUTER;
				path[4] = (from + oppdir) % OUTER;
				path[5] = (path[4] + oppdir) % OUTER;
			} else {
				path[1] = (from + oppdir) % OUTER;
				path[2] = (path[1] + oppdir) % OUTER;
				path[4] = (from + direction) % OUTER;
				path[5] = (path[4] + direction) % OUTER;
			}
		}
	}

	return path;
}


Point Hexagon::node_position (constref<Node> node, constref<Point> center)
   const {
	if (node == HEX_CENTER) {
		return center;
	}

	float angle = node * M_PI / 3 + offset;
	Point p;
	p.x = center.x + radius * cos (angle);
	p.y = center.y + radius * sin (angle);

	return p;
}

PointPath Hexagon::path_positions (constref<Path> path,
   constref<Point> center) const {
	PointPath pos (POINTS);
	for (int i = 0; i < POINTS; ++i) {
		pos[i] = node_position (path[i], center);
	}

	return pos;
}


/*  2 1
 * 3 6 0
 *  4 5
 */
Angle Hexagon::hexagon_angle (Node from, Node to) {
	if (from == HEX_CENTER) {
		return to * M_PI / 3.0;
	}
	if (to == HEX_CENTER) {
		return hexagon_angle(to, from) + M_PI;
	}
	if ((from + 1) % OUTER == to) {
		return (from - 4) * M_PI / 3.0;
	}
	if ((to + 1) % OUTER == from) {
		return hexagon_angle (to, from) + M_PI;
	}

	/* Unhandled error */
	return 0;
}


Flow Hexagon::node_flow (constref<Path> path, constref<Flow> flow, int i)
   const {
	Angle in, out;
	if (i == 0) {
		in = flow.enter;
	} else {
		in = hexagon_angle (path[i-1], path[i]) + offset;
	}

	if (i == POINTS - 1) {
		out = flow.exit;
	} else {
		out = hexagon_angle (path[i], path[i+1]) + offset ;
	}

	return {normalize_angle (in), normalize_angle (out)};
}


FlowPath Hexagon::path_flows (constref<Path> path, constref<Flow> flow) const {
	FlowPath flowpath (POINTS);
	for (int i = 0; i < POINTS; ++i) {
		flowpath[i] = node_flow (path, flow, i);
	}

	return flowpath;
}

