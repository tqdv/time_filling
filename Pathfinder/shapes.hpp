#ifndef TFILL_HEXAGON_HPP
#define TFILL_HEXAGON_HPP

#include <optional>
#include <vector>
#include <functional>


/* offset is absolute offset from the horizontal line, using trigonometric angles */
/* the points are ordered in triginometric order. But the output on the screen
 * is inverted because the y axis is inverted */


typedef int Node;
typedef struct point {
	float x;
	float y;
} Point;

typedef struct route {
	Node from;
	Node to;
} Route;
typedef std::vector<Node> Path;
typedef std::vector<Point> PointPath;

typedef enum shapes {
	hexagon,
	triangle,
} Shape;
typedef float Angle;

typedef struct flow {
	Angle enter;
	Angle exit;
} Flow;
typedef struct structure {
	const Shape shape;
	const float radius;
	const Angle offset;
} Structure;

typedef std::function<Point(Node)> Node_Point_f;
typedef std::function<Flow(int)> Node_Index_Flow_f;

typedef PointPath::iterator PP_it;


std::optional<PointPath> structure_positions (std::vector<Structure> structure,
  const Point &center, const Flow &flow);
/* Returns the positions of all the points that create `structure` */

bool write_structure_pos (const std::vector<Structure> &structures, int index,
   const Point &center, const Flow &flow, PointPath::iterator it, const PointPath::iterator end);
/* Recursive function for `structure_positions` */


std::optional<PointPath> shape_positions (const Structure &st, Node from,
   Node to, const Point &center);
/* Returns a the points forming a path in `s` with the given parameters
 * Returns None if it's not possible
 */

std::optional<Path> shape_path (Shape s, Node from, Node to);
/* from, to in [|0; n-1|]; from <> to;
 *    where n is the number of outer vertices
 * Returns a path from edge to edge in the shape `s`, going over all points
 * with only movements to neighbour points
 * Returns None if the assertions are false or the path doesn't exist
 */

std::optional<PointPath> path_positions (const Structure &st, const Path &path,
   const Point &center);
/* structure is valid and compatible with path;
 * Returns the positions of the points of `path`, given a structure `st`
 * Returns None if the assertions are false
 */

std::optional<Route> flow_route (Shape shape, const Flow &flow);
/* Returns a route for a `shape` under `flow` */

std::optional<Node_Index_Flow_f> node_index_flow (Shape shape, const Path &path,
   const Flow &flow, Angle offset);
/* Returns a function that associates an index of path to its absolute flow
 * using the local flow and offset */

std::optional<Node_Point_f> st_position (const Structure &st, const Point &center);
/* Returns a function that assicates a point to each node of structure */

bool write_positions (const Path &path, Node_Point_f position,
   PointPath::iterator it, const PointPath::iterator end);
/* path and iterators are compatible
 * Writes the positions of the nodes given by `path` using `position`, to memory
 * addressed by the iterator
 * Return false if the assertions are false
 */

void flow_add_angle (Flow &flow, Angle angle);
/* Adds an angle to a Flow (Angle x Angle) */

void flow_normalize (Flow &flow);
/* Normalizes the Angles to [-2π; 2π] */


std::optional<Path> hexagon_path (Node from, Node to);
/* from, to are valid edge nodes; from <> to */
Point hexagon_position (const Node node, const Point &center,
   float radius, Angle offset);
/* Assumes everything is valid */
Route hexagon_route (const Flow &flow);
/* Returns a **probably** correct route */
std::tuple<Node, Node> hexagon_angle_2node (Angle angle);
/* Return the two closest nodes for a certain `angle` */
std::optional<Node_Index_Flow_f> hexagon_nif (const Path &path,
   const Flow &flow, Angle offset);
/* Returns a function that associates an index of a path to its flow */
Angle hexagon_angle (Node from, Node to);
/* Return the angle formed by from -> to
 * Only handles the case when they're adjacent
 */


std::optional<Path> triangle_path (Node from, Node to);
/* from, to are valid edge nodes; from <> to */
Point triangle_position (const Node node, const Point &center, float radius,
   Angle offset);
/* Assumes everything is valid */
std::optional<Node_Index_Flow_f> triangle_nif (const  Path &path,
   const Flow &flow, Angle offset);
/* Return a function that associates an index of a path to its flow */
Route triangle_route (const Flow &flow);
std::tuple<Node, Node> triangle_angle_2node (Angle angle);
Angle triangle_angle (Node from, Node to);
/* Return the angle formed by from -> to */


#endif  // TFILL_HEXAGON_HPP
