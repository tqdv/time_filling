/*! TODO */
#![warn(missing_docs)]

mod tifl;
use tifl::*;

fn main() {

	if cfg!(debug_assertions) {
		for i in 0..=2 {
			let dirs = base_directions(i);
			println!("level {}: {:?}, {:?}", i, dirs[0], dirs[1]);
		}
	}

	let from = Hex2::new(-10, -1);
	let to = Hex2::new(18, -2);
	let through = vec![
		HexBlock::new(Hex2::new(0, 0), 3),
		HexBlock::new(Hex2::new(12, -1), 1),

		HexBlock::new(Hex2::new(14, 0), 1),
		HexBlock::new(Hex2::new(15, -3), 1),

		HexBlock::new(Hex2::new(17, -2), 1),
	];

	let graph = hexpath(from, to, through).unwrap();

	for g in graph {
		for point in g.into_leaves() {
			print!("[{},{}],", point.x, point.y);
		}
	}

	// println!("{:?}", graph);
}
