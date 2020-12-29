/*! Time filling, the library

## Useful ressources

<https://www.redblobgames.com/grids/hexagons/>

*/
use std::ops::{Add, Sub, Mul};
use std::ops::{Deref, DerefMut};
use std::fmt::{self, Debug};
use rand::prelude::*;
use arrayvec::ArrayVec;

// === Hex2 and HexBlock ===

/** Axial coordinates of a hexagon in a grid

X being horizontal, and Y slanted at a 60° angle.

```text
                             |+Y
    (-1, 1)   (0, 1)         | 
(-1, 0)  (0, 0)  (1, 0)     / \
    (0, -1)   (1, -1)   +Z /   \ +X
```

Actually, if we use cubic coordinates, the X axis points 120° to the right,
the Y axis is straight up and the Z axis points 120° to the left.

See <https://www.redblobgames.com/grids/hexagons/#coordinates>
*/
#[derive(PartialEq, Eq, Clone, Copy)]
pub struct Hex2 {
	pub x: i8,
	pub y: i8,
}

/** A hexagon-shaped group of hexagons

The block is defined by the coordinates of its center, and its size.
A size of 0 is a single Hexagon, a size of 1 is a group of 7 hexagons,
a size of 2 is a group of 7 size 1 hexagons, etc…
*/
#[derive(Clone, PartialEq, Eq)]
pub struct HexBlock {
	center: Hex2,
	size: i8,
}

impl Hex2 {
	/// Create a Hex2 from its coordinates
	pub fn new(x: i8, y:i8) -> Self {
		Hex2 { x, y }
	}

	/// The z coordinate in cubic coordinates
	pub fn z(&self) -> i8 {
		- self.x - self.y
	}

	/// Rotate by 60° to the left
	pub fn rot60(&self) -> Hex2 {
		Hex2 {
			x: - self.y,
			y: - self.z(),
		}
	}

	/// Rotate by 60° to the right (or -60° to the left)
	pub fn rotn60(&self) -> Hex2 {
		Hex2 {
			x: - self.z(),
			y: - self.x,
		}
	}

	/// The usual norm of a vector
	pub fn norm(&self) -> i8 {
		use std::cmp::max;
		max(self.x.abs(), max(self.y.abs(), self.z().abs()))
	}
}

impl Mul<Hex2> for i8 {
	type Output = Hex2;

	fn mul(self, mut rhs: Hex2) -> Self::Output {
		rhs.x *= self;
		rhs.y *= self;
		rhs
	}
}

impl Add for Hex2 {
	type Output = Self;

	fn add(mut self, other: Self) -> Self {
		self.x += other.x;
		self.y += other.y;
		self
	}
}

impl Sub for Hex2 {
	type Output = Hex2;

	fn sub(mut self, other: Self) -> Self::Output {
		self.x -= other.x;
		self.y -= other.y;
		self
	}
}

impl Debug for Hex2 {
	fn fmt(&self, f: &mut fmt::Formatter<'_>) -> Result<(), fmt::Error> {
		write!(f, "Hex2({}, {})", self.x, self.y)
	}
}

impl HexBlock {
	/// Create a new HexBlock from its center and size
	pub fn new(center: Hex2, size: i8) -> Self {
		HexBlock { center, size }
	}

	/// Create a new HexBlock of size 0 from its center
	pub fn from_hex2(center: Hex2) -> Self {
		HexBlock { center, size: 0 }
	}

	/// Returns if the HexBlock is of size 0
	pub fn is_atom (&self) -> bool { self.size == 0 }

	/** Return the 6 child HexBlocks that form the outer ring
	
	Returns None if there are no children.
	*/
	fn ring_children(&self) -> Option<[HexBlock; 6]> {
		use std::mem::{MaybeUninit, transmute};

		if self.is_atom() {
			return None;
		}

		let mut result: [MaybeUninit<HexBlock>; 6] = unsafe { MaybeUninit::uninit().assume_init() };
		for (i, vector) in base_directions(self.size - 1).iter().enumerate() {
			result[i] = MaybeUninit::new(HexBlock {
				center: self.center + *vector,
				size: self.size - 1,
			});
		}
		let result = unsafe { transmute(result) };
		Some(result)
	}
}

impl Debug for HexBlock {
	fn fmt(&self, f: &mut fmt::Formatter<'_>) -> Result<(), fmt::Error> {
		write!(f, "HexBlock{{ ({}, {}), size={} }}", self.center.x, self.center.y, self.size)
	}
}

// === Distance ===

/// Trait to calculate a distance with `dist`
trait Distance {
	type Output;
	fn dist (self, other: Self) -> Self::Output;
}

impl Distance for &Hex2 {
	type Output = i8;
	fn dist (self, other: Self) -> Self::Output {
		(*self - *other).norm()
	}
}

impl<'a> Distance for &'a HexBlock {
	type Output = <&'a Hex2 as Distance>::Output;
	fn dist (self, other: Self) -> Self::Output {
		self.center.dist(&other.center)
	}
}

/// Calculate the distance between two values
fn dist<D: Distance> (a: D, b: D) -> D::Output {
	a.dist(b)
}

// === Grid vectors ===

/// Hexagon grid related functions
mod grid {
	use super::*;

	/// The direction of a positive angle
	enum RotDir {
		/// To the left, as in trigonometry
		Trigonometric,
		/// To the right, as on clocks
		Clockwise,
	}

	/** The slant of the vector between HexBlocks of size `size+1` as seen from the base vectors of size `size`

	This defines how the hexagons are grouped together as there are two possibilities for each size level.
	*/
	fn base_slant(size: i8) -> RotDir {
		if size % 2 == 0 { RotDir::Trigonometric } else { RotDir::Clockwise }
	}

	/** The base vector for a `size` grid derived from the (1, 0)

	See [`base_directions`] for what a base vector is.
	*/
	// TODO memoize
	fn base_vector(size: i8) -> Hex2 {
		let mut v = Hex2::new(1, 0);
		for i in 0..size {
			v = match base_slant(i) {
				RotDir::Trigonometric => 2*v + v.rot60(),
				RotDir::Clockwise => 2*v + v.rotn60(),
			}
		}
		v
	}

	// TODO memoize
	/// Returns the 6 directions to move around a grid of size `size` HexBlocks
	pub fn base_directions(size: i8) -> [Hex2; 6] {
		let mut v = base_vector(size);

		let mut result = [Hex2{ x: 0, y: 0 }; 6];
		result[0] = v;
		for elt in result.iter_mut().skip(1) {
			v = v.rot60();
			*elt = v;
		}
		result
	}

	/** Decompose the vector between adjacent HexBlocks `left` to `right`
	
	Because we know how the base vectors are constructed, we can find out which 2 smaller vectors created it.
	See [`base_vector`]'s code for how they are built.
	*/
	pub fn decompose_base_vector(left: &HexBlock, right: &HexBlock) -> (Hex2, Hex2) {
		// We assume $left and $right have the same size and are adjacent
		let size = left.size;

		let difference = right.center - left.center;

		let rotation_count = base_directions(size).iter()
			.position(|&x| x == difference)
			.expect("Adjacent HexBlocks are offset by a base vector");
		
		let main_vector = base_directions(size - 1)[rotation_count];
		let side_vector = difference - 2*main_vector; // v == 2 * main_vector + side_vector
		(main_vector, side_vector)
	}

	// TODO memoize
	/// The distance between HexBlocks of size `size` in a grid
	pub fn grid_distance(size: i8) -> i8 {
		base_vector(size).norm()
	}
}
use grid::{grid_distance, decompose_base_vector};
pub use grid::base_directions;

// === Types to solve the problem ===

/** Newtype for chains of parent-child HexBlocks

This means that every element is the direct parent of the next one
*/
#[derive(Clone)]
struct HexChain(Vec<HexBlock>);

/** A HexBlock connected to its neighbours

A HexNode is usually part of a list of HexNodes.
In that context, `left` describes how the `block` is connected to the previous `HexNode`,
and `right` to the next one.

Visually:

```text
level block.size:  block
                  /     \
block.size-1:   left[0] right[0]
                /         \
block.size-2: left[1]     right[1]
              /             \ 
            ...             ...
            /                \
level 1:  left[*-2]          right[*-2]        etc... 
          /                    \                /
level 0: left[*-1]             right[*-1] --- next_block.left[*-1]
```
*/
#[derive(Debug, Clone)]
struct HexNode {
	block: HexBlock,
	left: HexChain,
	right: HexChain,
}

/** The counterpart to HexNodes: bridges between HexNodes

If A and B are HexNodes, and A is to the left of B,
then the HexBridge between A and B is (A.right, B.left)
*/
#[derive(Debug)]
struct HexBridge {
	left: HexChain,
	right: HexChain
}

/// A graph of HexBlocks, including their children
#[derive(Clone)]
pub struct HexGraph {
	block: HexBlock,
	children: Option<Box<[HexGraph; 7]>>,
}

impl HexChain {
	/// Create a new empty HexChain
	fn new() -> Self {
		HexChain(Vec::new())
	}
}

impl Debug for HexChain {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "HexChain ")
		.and_then(|_| {
			f.debug_list().entries(self.0.iter()).finish()
		})
	}
}

impl Deref for HexChain {
	type Target = Vec<HexBlock>;
	fn deref(&self) -> &Self::Target {
		&self.0
	}
}

impl DerefMut for HexChain {
	fn deref_mut(&mut self) -> &mut Self::Target {
		&mut self.0
	}
}

impl HexNode {
	/// Create a new unsolved node
	pub fn from_block (block: HexBlock) -> Self {
		HexNode {
			block,
			left: HexChain::new(),
			right: HexChain::new(),
		}
	}

	/// A node is solved if both left and right chains reach down to level 0
	fn is_solved(&self) -> bool {
		if self.block.is_atom() {
			return true;
		} else {
			self.left.last().map(HexBlock::is_atom).unwrap_or(false)
			&& self.right.last().map(HexBlock::is_atom).unwrap_or(false)
		}
	}
}

impl HexBridge {
	/// Create a new bridge with left and right
	fn new(left: HexChain, right: HexChain) -> Self {
		HexBridge { left, right }
	}

	/// Convert the HexBridge into a pair of HexChain
	fn into_chains(self) -> (HexChain, HexChain) {
		(self.left, self.right)
	}
}

impl HexGraph {
	/// Create a HexGraph from a block of size 0
	fn leaf_block(block: HexBlock) -> Option<Self> {
		if block.is_atom() {
			Some(HexGraph { block, children: None })
		} else {
			None
		}
	}

	/// Return an iterator over the graph leaves
	pub fn into_leaves(self) -> impl Iterator<Item = Hex2> {
		struct HexGraphLeaves {
			roots: Vec<HexGraph>,
		}

		impl Iterator for HexGraphLeaves {
			type Item = Hex2;

			fn next(&mut self) -> Option<Self::Item> {
				loop {
					let elt = self.roots.pop()?;
					if elt.block.is_atom() {
						break Some(elt.block.center);
					} else if let Some(children) = elt.children {
						self.roots.extend(children.to_vec().into_iter().rev());
					} else {
						unreachable!()
					}
				}
			}
		}

		HexGraphLeaves { roots: vec![ self ] }
	}
}

impl Debug for HexGraph {
	fn fmt(&self, f: &mut fmt::Formatter<'_>) -> Result<(), fmt::Error> {
		if let Some(children) = &self.children {
			f.debug_struct("HexGraph")
			.field("block", &self.block)
			.field("children", &children)
			.finish()
		} else {
			write!(f, "HexGraph{{ {:?} }}", &self.block)
		}
	}
}

// === Solving links ===

/** Finds a "link" between two HexBlocks

We assume $left and $right are adjacent.

If $left and $right **have different sizes**, we look at the larger HexBlock's children
and find a HexBlock of the same size as the smaller HexBlock that connects to it.
For example, if `$left.size = 3` and `$right.size = 1`, we find a HexBlock that is
of size 1, child of $left, and connected to $right.

We can't easily determine if two HexBlocks are adjacent, however if they are adjacent, their
distance is less than the grid distance of the larger HexBlock. _(Probably, to verify)_

We then return the HexBlock we found, as well as its parents (up to,
but excluding the starting point ie. $left or $right) as a HexNode.

Since there may be multiple solutions, we actually return a Vec<HexBridge>.

If $left and $right **are the same size**, there are 3 ways to make a link involving 4 HexBlocks.
Say we have 4 HexBlocks (A, B, C, D), the possible links are A-B, B-C and C-D.
B and D are from $left, A and C are from $right.
This is what we return as a Vec<HexBridge>.

The way to find those 4 HexBlocks is to decompose the base vector ($right.center - $left.center)
into its two component vectors, and calculate their positions.

Finally, if both $left and $right **are of size 0**, then we return an empty vector.

*/
fn find_link(left: &HexBlock, right: &HexBlock) -> Vec<HexBridge> {
	use std::cmp::Ordering::*;

	/** Find a chain of HexBlocks from $large until one of the same size as $small and adjacent to it */
	fn find_chains(small: &HexBlock, large: &HexBlock) -> Vec<HexChain> {
		let mut parent_chains = vec![ HexChain(vec![large.clone()]) ];

		for gridsize in (small.size .. large.size).rev() {
			let mut next_parent_chains = Vec::with_capacity(parent_chains.len());
			for chain in parent_chains {
				let chain_head = chain.last().unwrap();
				for child in chain_head.ring_children().unwrap().iter() {
					// gridsize is the same as the size of the children
					if dist(small, child) <= grid_distance(gridsize) {
						let mut new_chain = chain.clone();
						new_chain.push(child.clone());
						next_parent_chains.push(new_chain);
					}
				}
			}
			parent_chains = next_parent_chains;
		}

		for chain in &mut parent_chains {
			chain.remove(0);
		}

		parent_chains
	}

	match left.size.cmp(&right.size) {
		Less => find_chains(left, right).into_iter()
			.map(|chain| HexBridge::new(HexChain::new(), chain))
			.collect(),
		Greater => find_chains(right, left).into_iter()
			.map(|chain| HexBridge::new(chain, HexChain::new()))
			.collect(),
		Equal => {
			if left.is_atom() {
				return Vec::new();
			}

			let (main_v, side_v) = decompose_base_vector(left, right);
			let blocksize = left.size - 1;
			let (a, b, c, d) = (
				HexBlock::new(right.center - side_v , blocksize),
				HexBlock::new(left.center + main_v , blocksize),
				HexBlock::new(right.center - main_v , blocksize),
				HexBlock::new(left.center + side_v , blocksize),
			);
			vec![
				HexBridge::new(HexChain(vec![b.clone()]), HexChain(vec![a])),
				HexBridge::new(HexChain(vec![b]), HexChain(vec![c.clone()])),
				HexBridge::new(HexChain(vec![d]), HexChain(vec![c])),
			]
		},
	}
}

/** Returns whether the two chains form a loop ie. they share a common element

Due to how nesting works, if the two chains share a common element then
the biggest pair of nodes of the same size are equal
*/
fn chains_form_loop(left: &HexChain, right: &HexChain) -> bool {
	if let (Some(left_head), Some(right_head)) = (left.first(), right.first()) {
		match left_head.size - right_head.size {
			x if x < 0 => {
				right.get(-x as usize)
					.map(|right_elt| left_head == right_elt)
					.unwrap_or( false )
			},
			0 => left_head == right_head,
			x if x > 0 => {
				left.get(x as usize)
					.map(|left_elt| left_elt == right_head)
					.unwrap_or( false )
			},
			_ => unreachable!(),
		}
	} else {
		false
	}
}

/** Solve the connections between HexBlocks in a list, given boundary conditions

We solve from the left, to the right. For each node, we look at what possible
bridges exist between the current node and the next one. We remove those
that would form a loop with the node's left chain.

The bridges are solved level by level until we have solved it down to size 0.
*/
fn solve_links(path: Vec<HexBlock>, leftmost: HexChain, rightmost: HexChain) -> Vec<HexNode> {
	let mut rng = thread_rng();

	// Convert $path to a chain of HexNodes
	let mut chain: Vec<HexNode> = path.into_iter().map(HexNode::from_block).collect();

	// Try until we find a chain that doesn't form a loop at the end
	'found: loop {
		// Expand the sides of each HexNode
		let mut left = leftmost.clone();
		let mut chain_iter = chain.iter_mut().peekable();
		while let Some(node) = chain_iter.next() {
			if node.block.is_atom() {
				continue;
			}

			let mut next_left = HexChain::new();
			let mut right = HexChain::new();

			if let Some(next_node) = chain_iter.peek() {
				// Given the left side find the right side: loop until we solved the node down to size 0
				loop {
					if right.last().map(HexBlock::is_atom).unwrap_or(false) {
						break;
					}

					let right_point = right.last().unwrap_or_else(|| &node.block);
					let next_left_point = next_left.last().unwrap_or_else(|| &next_node.block);

					let (mut bridge_left, mut bridge_right) = find_link(right_point, next_left_point).into_iter()
						.filter(|bridge| !chains_form_loop(&left, &bridge.left))
						.choose(&mut rng).expect("There is always a way to bridge across adjacent HexBlocks")
						.into_chains();

					right.append(&mut bridge_left);
					next_left.append(&mut bridge_right);
				}

			} else {
				// This is the last node
				right = rightmost.clone();
				if !chains_form_loop(&left, &right) {
					/* Copied from the loop tail, because we break the loop to prove
					that `right = rightmost` happens only once */
					node.left = left;
					node.right = right;
					break 'found;
				} else {
					// Retry to find one without a loop
					continue 'found;
				}
			}

			node.left = left;
			node.right = right;
			left = next_left;
		}

		break;
	}

	chain
}

// === Solving paths ===

/** Finds a path between `hexagon`'s direct children from `start` to `end`

Panics if it can't compute it.
*/
fn find_hexagon_path(hexagon: HexBlock, start: HexBlock, end:HexBlock) -> [HexBlock; 7] {
	use std::mem::{self, MaybeUninit};

	debug_assert!(start != end);
	debug_assert!(start.size == end.size);
	debug_assert!(hexagon.size == start.size + 1);
	// Assert $start and $end are children of hexagon (this does not prove it, but should be good enough)
	debug_assert!(dist(&hexagon.center, &start.center) == grid_distance(start.size));
	debug_assert!(dist(&hexagon.center, &end.center) == grid_distance(end.size));

	let mut path: [MaybeUninit<HexBlock>; 7] = unsafe { MaybeUninit::uninit().assume_init() };
	let mut rng = thread_rng();
	let element = |center: Hex2| { MaybeUninit::new(HexBlock::new(center, start.size)) };

	if dist(&hexagon.center, &start.center) == dist(&start.center, &end.center) {
		// The ends are adjacent: 5 solutions
		let (center, order) = match rng.gen_range(0..5) {
			0 => (1, [2, 3, 4, 5]),
			1 => (2, [1, 3, 4, 5]),
			2 => (3, [1, 2, 4, 5]),
			3 => (4, [1, 2, 3, 5]),
			4 => (5, [1, 2, 3, 4]),
			_ => unreachable!(),
		};

		let straight = hexagon.center - start.center;
		let edge = end.center - start.center;
		let third = end.center - hexagon.center;
		/* From the bottom-left (start) to the bottom-right (end), with straight from
		bottom-left to top-right (/), edge from left to right (_) and third from
		top-left to bottom-right (\).
		  /¯\  _\¯\  /\/\  /¯/_  /¯\
		  ¯//  \  /  \  /  \  /  \\¯
		We generate each by choosing which one goes in the center.
		*/
		path[order[0]] = element(hexagon.center - edge);
		path[order[1]] = element(hexagon.center - third);
		path[order[2]] = element(hexagon.center + straight);
		path[order[3]] = element(hexagon.center + edge);

		path[center] = element(hexagon.center);

	} else if end.center - start.center == 2 * (hexagon.center - start.center) {
		// The ends are opposite: 2 solutions

		let straight = hexagon.center - start.center;
		let side = if rng.gen() { straight.rot60() } else { straight.rotn60() };
		/* From the left (start) to the right (end), with side from
		bottom-left to top-right (/) or top-left to bottom-right (\).
		 /‾/      \‾\
		  /_/ or \_\
		We generate each by choosing which side to go first.
		*/
		path[1] = element(start.center + side);
		path[2] = element(hexagon.center + side);
		path[3] = element(hexagon.center);
		path[4] = element(hexagon.center - side);
		path[5] = element(end.center - side);

	} else {
		// The ends are... 120° degrees apart: 2 solutions
		let (a, b, order) = if rng.gen() {
			(start.center, end.center, [1, 2, 3, 4, 5])
		} else {
			(end.center, start.center, [5, 4, 3, 2, 1])
		};

		let side = b - hexagon.center;
		let straight = hexagon.center - a;
		/* From the top-left (start) to the bottom-left (end), with side
		from top-right to bottom-left (/) and straight from top-left to bottom-right (\).
		 /_/\    _¯¯\
		  __/ or \\./
		The second is generated by swapping start and end, and by reversing the assignment order.
		*/
		path[order[0]] = element(a + side);
		path[order[1]] = element(hexagon.center);
		path[order[2]] = element(hexagon.center - side);
		path[order[3]] = element(hexagon.center - side + straight);
		path[order[4]] = element(hexagon.center + straight);
	}

	path[0] = MaybeUninit::new(start);
	path[6] = MaybeUninit::new(end);

	unsafe { mem::transmute(path) }
}

/// Given a HexNode, recursively solve it into a HexGraph
fn solve_nodepath(node: HexNode) -> HexGraph {
	// We assume that the HexNode has both chains down to size 0
	debug_assert!(node.is_solved());

	let HexNode { block, mut left, mut right } = node;

	if block.is_atom() {
		return HexGraph::leaf_block(block).unwrap();
	}

	debug_assert!(!left.is_empty());
	debug_assert!(!right.is_empty());
	let start = left.remove(0);
	let end = right.remove(0);

	debug_assert!(start.size == end.size);

	// Solve n-1 path
	let path = find_hexagon_path(block.clone(), start, end).to_vec();

	// Solve n-1 links
	let child_nodes = solve_links(path, left, right);

	// Recursively solve n-1 nodepaths
	let child_graphs = child_nodes.into_iter()
		.map(solve_nodepath)
		.collect::<ArrayVec<_>>()
		.into_inner()
		.ok().unwrap();

	HexGraph {
		block,
		children: Some(Box::new(child_graphs)),
	}
}

// === Solving the problem ===

/** Find the parent chain between a parent and a child (inclusive)

We keep track of the HexBlocks of size `$size` within a `grid_distance($size)` radius of $child,
until we read `$size == $child.size + 1` for which there is only a single solution
if `$parent` and `$child` are indeed related.

Returns None if the sizes are not right.
Panics if they are not parent and child.
*/
fn find_parents(small_child: HexBlock, parent: HexBlock) -> Option<HexChain> {
	if parent.size - small_child.size < 1 {
		return None;
	}

	let parent_size = parent.size;
	let mut parent_chains: Vec<HexChain> = vec![ HexChain(vec![parent]) ];
	for gridsize in (small_child.size + 1 .. parent_size).rev() {
		let mut next_parent_chains = Vec::with_capacity(parent_chains.len());
		for chain in parent_chains {
			let chain_head = chain.last().unwrap();
			for child in chain_head.ring_children().unwrap().iter() {
				debug_assert!(gridsize == child.size);
				
				if dist(&small_child, child) <= grid_distance(gridsize) {
					let mut new_chain = chain.clone();
					new_chain.push(child.clone());
					next_parent_chains.push(new_chain);
				}
			}
		}
		parent_chains = next_parent_chains;
	}

	// We should have gridsize == small_child.size + 1

	/* A HexBlock of size n+1 is a (hex) circle of diameter 1 of HexBlocks of size n,
	which means we can use the distance equality */
	let mut parents = parent_chains.into_iter()
		.find(|e| dist(&small_child, e.last().unwrap()) == grid_distance(small_child.size))
		.expect("parent and child should be related");

	parents.push(small_child);

	Some(parents)
}

/** The problem: find a path through HexBlocks

We assume `through` is a list of connected HexBlocks and `from` and `to` belong to first and last blocks.
*/
pub fn hexpath (from: Hex2, to: Hex2, through: Vec<HexBlock>) -> Option<Vec<HexGraph>> {
	if through.is_empty() {
		return None;
	}

	// Solve boundary conditions
	let (leftmost, rightmost) = {
		let first_block = through.first().unwrap().clone();
		let last_block = through.last().unwrap().clone();
		let mut leftmost = find_parents(HexBlock::from_hex2(from), first_block).unwrap();
		let mut rightmost = find_parents(HexBlock::from_hex2(to), last_block).unwrap();
		leftmost.remove(0);
		rightmost.remove(0);
		(leftmost, rightmost)
	};

	// Solve the links between nodes
	let chain = solve_links(through, leftmost, rightmost);
	// dbg!(&chain);

	// Solve each node
	let result = chain.into_iter().map(solve_nodepath).collect();

	Some(result)
}