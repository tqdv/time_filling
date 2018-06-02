#ifndef TFILL_HEXAGON_HPP
#define TFILL_HEXAGON_HPP

#include "shapes.hpp"


class Hexagon : public Shape {
	const float radius;  // >= 0.0
	const Angle offset;

	/* from Shape */
	Maybe<PointPath> pointpath_p (constref<Flow> flow, constref<Point> center)
	   const;
	Maybe<PointFlows> pointflows_p (constref<Flow> flow,
	   constref<Point> center) const;
	
	Flow flow_local_flow (constref<Flow> flow) const;
	inline static Angle node_angle_dist (Node i, Angle angle);
	static std::tuple<Node, Node> angle_2node (Angle angle);
	Route flow_route (constref<Flow> flow) const;
	static Maybe<Path> route_path (constref<Route> route);
	Point node_position (constref<Node> node, constref<Point> center) const;
	PointPath path_positions (constref<Path> path, constref<Point> center)
	   const;
	static Angle hexagon_angle (Node from, Node to);
	Flow node_flow (constref<Path> path, constref<Flow> flow, int i) const;
	FlowPath path_flows (constref<Path> path, constref<Flow> flow) const;

protected:
	Hexagon (float radius, Angle offset);

public:
	static bool valid_args (float radius, Angle offset);
	static Maybe<Hexagon> make_hexagon (float radius, Angle offset);
};


#endif  // TFILL_HEXAGON_HPP
