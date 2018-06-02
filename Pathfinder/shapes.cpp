#include "shapes.hpp"

#include <cmath>
#include <optional>
#include <random>
#include <iterator>
#include <functional>  // for bind, etc...?
#include <algorithm>  // for copy
#include <tuple>
#include <iostream>

using std::ostream;


ostream& operator<< (ostream& os, constref<Point> p) {
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}

ostream& operator<< (ostream& os, constref<Flow> f) {
	os << "(" << f.enter / M_PI << ", " << f.exit / M_PI << ")";
	return os;
}

Shape::Shape (int points)
	: points(points)
{ }

bool Shape::valid_args (int points) {
	return (points >= 2);
}


Maybe<PointPath> shapes_positions (constref<ShapeList> shapes,
   constref<Point> center, constref<Flow> flow) {
	const int n = shapes.size();
	if (n == 0) { return {}; }

	int nb_points = 1;
	std::vector<int> points (n);
	for (int i = (n - 1); i >= 0; --i) {
		nb_points *= shapes[i]->points;
		points[i] = nb_points;
	}
	PointPath pos (nb_points);


	bool status;
	status = write_structure_pos (shapes, points, 0, center, flow,
	   pos.begin());

	return (status ? pos : Maybe<PointPath> {});
}


bool write_structure_pos (constref<ShapeList> shapes, constref<Nums> nums,
   int index, constref<Point> center, constref<Flow> flow, PP_it it) {

	const int levels = shapes.size();
	if (!(index < levels)) { return false; }

	constref<Shape> shape = *shapes[index];

	if (index == levels - 1) {
		/* Last level, actually writing */
		Maybe<PointPath> pos = shape.pointpath (flow, center);
		if (!pos.has_value()) { return false; }

		std::copy (pos->begin(), pos->end(), it);

		return true;
	}

	constref<int> num = nums[index + 1];  // Because we want the next one's
	const Maybe<PointFlows> pf = shape.pointflows (flow, center);
	if (!pf.has_value()) { return false; }

	const auto [points, flows] = *pf;

	auto it_pos = [&num, &it](int x) {
		PP_it _it (it);
		std::advance (_it, x * num);
		return _it;
	};
	
	bool status;
	for (int i = 0; i < shape.points; ++i) {
		status = write_structure_pos
		   (shapes, nums, (index + 1), points[i], flows[i], it_pos (i));
		if (!status) {
			return false;
		}
	}

	return true;
}












//
//void flow_add_angle (Flow &flow, Angle angle) {
//	flow.enter += angle;
//	flow.exit += angle;
//}
//
//void flow_normalize (Flow &flow) {
//	flow.enter = fmod (flow.enter, 2 * M_PI);
//	flow.exit = fmod (flow.exit, 2 * M_PI);
//}
//
//
///* TRIANGLE FUNCTIONS */
///*  0
// * 2 1
// */
//
//std::optional<Path> triangle_path (Node from, Node to) {
//	if (from < 0 || from >= P.triangle || to < 0 || to >= P.triangle || to == from)
//		return {};
//
//	return Path {from, (3 - from - to), to};
//}
//
//Point triangle_position (const Node node, const Point &center, float radius,
//   Angle offset) {
//	
//	float angle = node * M_PI * 2 / 3 + offset;
//	Point p;
//	p.x = center.x + radius * cos (angle);
//	p.y = center.y + radius * sin (angle);
//
//	return p;
//}
//
//
//std::optional<Node_Index_Flow_f> triangle_nif (const  Path &path,
//   const Flow &flow, Angle offset) {
//	return [&path, &flow, &offset](int i) {
//		Angle in, out;
//		if (i == 0) {
//			in = flow.enter;
//		} else {
//			in = triangle_angle (path[i-1], path[i]);
//		}
//
//		if (i == P.triangle - 1) {
//			out = flow.exit;
//		} else {
//			out = triangle_angle (path[i], path[i+1]);
//		}
//		return Flow {in + offset, out + offset};
//	};
//}
//
//Route triangle_route (const Flow &flow) {
//	/* Find the two closest nodes for each angle, and try to make it work */
//	std::tuple<Node, Node> entrances = triangle_angle_2node (flow.enter);
//	std::tuple<Node, Node> exits = triangle_angle_2node (flow.exit);
//
//	Node in, out;
//	in = std::get<0>(entrances);
//	out = std::get<0>(exits);
//
//	if (in == out) {
//		std::random_device rd;
//		std::bernoulli_distribution randbool (0.5);
//		bool first = randbool (rd);
//		if (first) {
//			in = std::get<1>(entrances);
//		} else {
//			out = std::get<1>(exits);
//		}
//	}
//
//	return {in, out};
//}
//
//std::tuple<Node, Node> triangle_angle_2node (Angle angle) {
//	std::vector<Angle> diff (V.triangle);
//	for (int i = 0; i < V.triangle; ++i) {
//		diff[i] = abs (fmod ((i * 2.0 / 3.0) - (angle / M_PI), 2));
//	}
//	auto it1 = std::max_element (diff.begin(), diff.end());
//	*it1 = 2.0;
//	auto it2 = std::max_element (diff.begin(), diff.end());
//	auto b = diff.begin();
//	
//	return {std::distance (b, it1), std::distance (b, it2)};
//}
//	
//
//Angle triangle_angle (Node from, Node to) {
//	if ((from + 1) % P.triangle == to) {
//		return (2 * from + 5) / 6.0 * M_PI; 
//	} else {
//		return - triangle_angle (to, from);
//	}
//}





