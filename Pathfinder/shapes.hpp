#ifndef TFILL_SHAPES_HPP
#define TFILL_SHAPES_HPP

#include "utils.hpp"

#include <optional>
#include <iterator>
#include <vector>
#include <cmath>
#include <tuple>
#include <vector>
#include <iostream>

using std::ostream;


/* angle(parent) = angle(child) + offset */
/* offset is absolute offset from the horizontal line, using trigonometric angles */
/* the points are ordered in triginometric order. But the output on the screen
 * is inverted because the y axis is inverted */


using Node = int;
using Angle = float;

struct Point {
	float x;
	float y;

	friend ostream& operator<< (ostream& os, constref<Point> p);
};

struct Route {
	Node from;
	Node to;
};

struct Flow {
	Angle enter = M_PI / 2;
	Angle exit = M_PI / 2;

	friend ostream& operator<< (ostream& os, constref<Flow> f);
};

using Path = std::vector<Node>;
using PointPath = std::vector<Point>;

/* Convenience aliases */
using FlowPath = std::vector<Flow>;
using PointFlows = std::tuple<PointPath, FlowPath>;
using PP_it = PointPath::iterator;


/* A shape is a disposition of 2 or more points */
class Shape {

	virtual Maybe<PointPath> pointpath_p (constref<Flow> flow,
	   constref<Point> center) const =0;
	virtual Maybe<PointFlows> pointflows_p (constref<Flow> flow,
	   constref<Point> center) const =0;

protected:
	Shape (int points);

public:
	const int points;  // >= 2

	static bool valid_args (int points);
	/* Checks if the arguments for the constructor are valid */

	Maybe<PointPath> pointpath (constref<Flow> flow, constref<Point> center)
	   const {
		return pointpath_p (flow, center);
	}
	Maybe<PointFlows> pointflows (constref<Flow> flow, constref<Point> center)
	   const {
		return pointflows_p (flow, center);
	}
};


using ShapeList = std::vector<Shape*>;
using Nums = std::vector<int>;

Maybe<PointPath> shapes_positions (constref<ShapeList> shapes,
   constref<Point> center, constref<Flow> flow);
/* Maybe returns a PointPath for a list of shapes with a center and a flow */

bool write_structure_pos (constref<ShapeList> shapes, constref<Nums> nums,
   int index, constref<Point> center, constref<Flow> flow, PP_it it);
/* Writes using an iterator the point positions for the given shapes
 * starting from index, using the center and flow */
/* We trust the programmer to give us a correct iterator */


inline Angle normalize_angle (Angle angle);

//void flow_add_angle (Flow &flow, Angle angle);
///* Adds an angle to a Flow (Angle x Angle) */
//
//void flow_normalize (Flow &flow);
///* Normalizes the Angles to [-2π; 2π] */
//
//
//std::optional<Path> triangle_path (Node from, Node to);
///* from, to are valid edge nodes; from <> to */
//Point triangle_position (const Node node, const Point &center, float radius,
//   Angle offset);
///* Assumes everything is valid */
//std::optional<Node_Index_Flow_f> triangle_nif (const  Path &path,
//   const Flow &flow, Angle offset);
///* Return a function that associates an index of a path to its flow */
//Route triangle_route (const Flow &flow);
//std::tuple<Node, Node> triangle_angle_2node (Angle angle);
//Angle triangle_angle (Node from, Node to);
///* Return the angle formed by from -> to */


#include "shapes.ipp"

#endif  // TFILL_SHAPES_HPP
