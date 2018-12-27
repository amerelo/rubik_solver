// #[macro_use]
// extern crate serde_derive;
// extern crate fnv;
// extern crate serde;
// extern crate bincode;
// extern crate colored;
// extern crate rand;

// mod cube;
// mod algorithmes;

// use cube::cube_3::*;
// use cube::moves::*;
// use cube::heuristic_3::*;
// use algorithmes::astar::*;
// use algorithmes::korf::*;
// use algorithmes::thistlethwaite::*;

// use cube::print_3::{print_debug_cube};

// use std::alloc::System;

// #[global_allocator]
// static GLOBAL: System = System;

// #[derive(Serialize, Deserialize, Debug)]
// pub struct Info {
// 	pub corner_moves: Vec<Moves>,
// 	pub edges_moves: Vec<Moves>,
// 	pub edges2_moves: Vec<Moves>,
// 	pub lists: Cube3,
// 	pub steps: u8,
// 	pub fix_depth: Vec<u8>,
// }

// #[derive(Serialize, Deserialize, Debug)]
// pub struct Data {
// 	pub lists: CubeKorf,
// }

// static F_MOVE: &[fn(&mut Vec<u8>)] = &[apply_u, apply_uprime, apply_f, apply_fprime,
// 				apply_r, apply_rprime, apply_d, apply_dprime, apply_b, apply_bprime, apply_l,
// 				apply_lprime, apply_u2, apply_f2, apply_r2, apply_d2, apply_b2, apply_l2];

// fn opposite_move(index: usize) -> u8 {
// 	match index {
// 		i if i > 11					=> i as u8,
// 		i if (i % 2 == 0)			=> (i + 1) as u8,
// 		i 							=> (i - 1) as u8,
// 	}
// }

// fn move_to_string(index: u8) -> String
// {
// 	match index {
// 		0 => "U ".to_string(),
// 		1 => "U' ".to_string(),
// 		2 => "F ".to_string(),
// 		3 => "F' ".to_string(),
// 		4 => "R ".to_string(),
// 		5 => "R' ".to_string(),
// 		6 => "D ".to_string(),
// 		7 => "D' ".to_string(),
// 		8 => "B ".to_string(),
// 		9 => "B' ".to_string(),
// 		10 => "L ".to_string(),
// 		11 => "L' ".to_string(),
// 		12 => "U2 ".to_string(),
// 		13 => "F2 ".to_string(),
// 		14 => "R2 ".to_string(),
// 		15 => "D2 ".to_string(),
// 		16 => "B2 ".to_string(),
// 		_ => "L2 ".to_string(),
// 	}
// }

// fn translate(moves: Vec<u8>)
// {
// 	let mut alfa_moves: String = String::from("");

// 	for action in moves.iter()
// 	{
// 		// alfa_moves.push_str(move_to_string(opposite_move(*action as usize)).as_str());
// 		alfa_moves.push_str(move_to_string(*action).as_str());
// 	}
// }

// fn start_normal() {
// 	let mut elems = Elem::default();
// 	let mut info = generate_heuristic();
// 	elems.cube = gen_cube3();

// 	random_scrambling(&mut elems.cube, 100);
// 	get_heuristic(&info, &mut elems);
// 	roux(&info, &mut elems);
// 	solve_puzzle(&mut info, elems);
// }

fn main()
{
	// if !true {
	// 	start_normal();
	// } else if true {
		
	// let (corners, edges1, edges2) = load_data();

	// start_korf(vec![], &corners, &edges1, &edges2);
	// } else {
	// 	let mut elem = Elem::default();
	// 	elem.cube = gen_cube3();
	// 	print_debug_cube(&elem.cube);

	// 	random_scrambling(&mut elem.cube, 5);

	// 	// let mut info = generate_heuristic();
	// 	edge(&elem);
	// }
}
