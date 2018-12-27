// use std::time::Instant;
// use cube::heuristic_3::{new_korf};
use cube::print_3::{print_debug_cube};
use cube::cube_3::*;
use Data;
// use cube::moves::{random_scrambling};

use bincode::{serialize, deserialize};
use std::collections::{ BinaryHeap};
use std::time::Instant;
use std::fs::File;
use std::io::prelude::*;
use std::io::Result;

use F_MOVE;
use opposite_move;
use cube::cube_3::CubeKind;

pub fn print_time_elapsed(time: Instant)
{
	let elapsed = time.elapsed();
	let sec = (elapsed.as_secs() as f64) + (elapsed.subsec_nanos() as f64 / 1000_000_000.0);
	println!("Puzzle solved in {:.4} seconds", sec);
}

#[allow(dead_code)]
fn gen_database(data: &mut Data, kind: CubeKind)
{
	let mut elem = CubeT::default();
	elem.cube = gen_cube3();
	let mut elemk = KElem::default();
	cube_to_kcube(&elem, &mut elemk, &kind);

	let mut open_l: Vec<CubeT> = vec![];
	open_l.push(elem);
	
	let mut tmpk;
	'outer: loop {
		let elem_study: CubeT;

		match open_l.pop() {
			Some(elem) => elem_study = elem,
			None => {
				println!("no more elems in list" );
				break;
			},
		}

		match elem_study.step {
			1 => println!("step ---------- 1\n" ),
			_ => ()
		}

		tmpk = KElem::default();
		cube_to_kcube(&elem_study, &mut tmpk, &kind);
		match data.lists.close_l.get(&tmpk) {
			Some(kelem) if elem_study.step >= get_step(kelem)	=> continue 'outer,
			_													=> (),
		}

		data.lists.close_l.replace(tmpk.clone());

		if elem_study.step > 11 {
			continue 'outer;
		}

		for (i, func) in F_MOVE.iter().enumerate()
		{
			let mut new_elem = elem_study.clone();
			func(&mut new_elem.cube);
			new_elem.last_move = i as u8;
			new_elem.step = elem_study.step + 1;

			open_l.push(new_elem);
		}
	}
	println!("len {}", data.lists.close_l.len());
}

#[allow(dead_code)]
pub fn wirte_file(data: &Data, name: &String) -> Result<()> 
{
	let serialized: Vec<u8> = serialize(&data).unwrap();
	let mut file = File::create(name)?;

	file.write_all(&serialized)?;

	Ok(())
}

#[allow(dead_code)]
pub fn gen_data()
{
	let mut cor :Data = Data{lists: CubeKorf::default()};;

	gen_database(&mut cor, CubeKind::CORNERS);
	match wirte_file(&mut cor, &"./corners.data".to_string())
	{
		Err(_) => println!("{}", "error at write"),
		Ok(_) => println!("{}", "write ok"),
	}
	
	let mut edg1 :Data = Data{lists: CubeKorf::default()};;

	gen_database(&mut edg1, CubeKind::CORNERS);
	match wirte_file(&mut edg1, &"./edges1.data".to_string())
	{
		Err(_) => println!("{}", "error at write"),
		Ok(_) => println!("{}", "write ok"),
	}
	
	let mut edg2 :Data = Data{lists: CubeKorf::default()};;

	gen_database(&mut edg2, CubeKind::CORNERS);
	match wirte_file(&mut edg2, &"./edges1.data".to_string())
	{
		Err(_) => println!("{}", "error at write"),
		Ok(_) => println!("{}", "write ok"),
	}
}

pub fn read_file(name: &String) -> Result<Data> 
{
	let mut file = File::open(name)?;
	let mut serialized = Vec::with_capacity((file.metadata().unwrap().len() + 1) as usize);
	
	file.read_to_end(&mut serialized)?;

	let data : Data = deserialize(&serialized).unwrap();
	Ok(data)
}

fn value_from_tab(tab: &Data, cube: &CubeT, kind: CubeKind) -> (u8, CubeT)
{
	let mut elemk: KElem = KElem::default();

	cube_to_kcube(cube, &mut elemk, &kind);
	match tab.lists.close_l.get(&elemk) {
		Some(val)	=> {
			let m = opposite_move(get_move(&val) as usize) as usize;
			let mut next_cube = cube.clone();
			if get_step(&val) == 0 {
				return (0, cube.clone());
			}
			F_MOVE[m](&mut next_cube.cube);
			(get_step(&val), next_cube)
		},
		_			=> panic!("value not found in tab"),
	}
}

fn get_kind_move<'a>(cor: &'a Data, edg1: &'a Data, edg2: &'a Data, cube: &CubeT) -> u8
{
	let (vc, _c) = value_from_tab(cor, cube, CubeKind::CORNERS);
	let (ve1, _e1) = value_from_tab(edg1, cube, CubeKind::EDGES1);
	let (ve2, _e2) = value_from_tab(edg2, cube, CubeKind::EDGES2);
	let heuristics = vec![vc, ve1, ve2];
	
	// let (max, _i) = heuristics.iter().enumerate().map(|(x, y)| (y, x)).max().unwrap();
	let max = heuristics.iter().max().unwrap();

	return *max;
}

fn ida_star(cor: &Data, edg1: &Data, edg2: &Data, elem: &mut CubeT) -> Vec<u8>
{
	let gobal_max;
	let mut tmp = CubeT::default();
	tmp.cube = elem.cube.clone();
	tmp.step = 0;
	tmp.last_move = 42;
	tmp.moves = 42;

	let mut open_l: BinaryHeap<CubeT>= BinaryHeap::new();
	open_l.push(tmp.clone());

	match get_kind_move(cor, edg1, edg2, &tmp) {
		max if max < 7	=> gobal_max = max + 1,
		max if max < 11	=> gobal_max = max + 2,
		_ 				=> {gobal_max = 23},
	}
	// println!("global_max {}", gobal_max);
	let mut moves: Vec<u8> = vec![];

	'outer: loop {
		let elem_study: CubeT;

		match open_l.pop() {
			Some(elem) => {elem_study = elem},
			None => {
				panic!("no more elems in list");
			},
		}

		if elem_study.step > gobal_max {
			continue 'outer;
		}

		// println!(" open l =========>  {:?}", open_l);

		// match moves.len() {
		// 	nbr if nbr == elem_study.step as usize	=> { moves.pop(); },
		// 	nbr if nbr >= elem_study.step as usize	=> { moves.pop(); moves.pop();}
		// 	_										=> (),
		// }
		while moves.len() != 0 && moves.len() >= (elem_study.step as usize) {
			// println!("moves.len() = {} || elem_study.step = {}", moves.len(), elem_study.step);
			moves.pop();
		}

		if elem_study.step != 0 {
			moves.push(elem_study.moves);
		}
		// print_debug_cube(&elem_study.cube);
		// println!("nbr of - {:?} step {}", moves, elem_study.step);
		for (i, func) in F_MOVE.iter().enumerate()
		{
				let mut new_elem = elem_study.clone();
				func(&mut new_elem.cube);
				
				new_elem.step = elem_study.step + 1;
				new_elem.moves = i as u8;

				match get_kind_move(cor, edg1, edg2, &new_elem) {
					0 => {
						println!("finish at step {}", new_elem.step);
						print_debug_cube(&new_elem.cube);
						moves.push(new_elem.moves);
						break 'outer ;
					},
					max => {new_elem.last_move = max},
				}

				if new_elem.last_move <= elem_study.last_move {
					open_l.push(new_elem);
				}
		}
		// println!("=========>  {:?}", elem_study);
	}
	// println!("nbr of state {:?}", moves);
	moves
}

#[allow(dead_code)]
pub fn load_data() -> (Data, Data, Data)
{
	let corners;
	let edges1;
	let edges2;

	match read_file(&"/sgoinfre/goinfre/Perso/amerelo/corners.test".to_string())
	{
		Err(_) => panic!("error corners.test"),
		Ok(tab) => corners = tab,
	}

	match read_file(&"/sgoinfre/goinfre/Perso/amerelo/edges1.test".to_string())
	{
		Err(_) => panic!("error edges1.test"),
		Ok(tab) => edges1 = tab,
	}

	match read_file(&"/sgoinfre/goinfre/Perso/amerelo/edges2.test".to_string())
	{
		Err(_) => panic!("error edges2.test"),
		Ok(tab) => edges2 = tab,
	}

	(corners, edges1, edges2)
}

pub fn start_korf(cube: Vec<u8>, corners: &Data, edges1: &Data, edges2: &Data) -> Vec<u8>
{
	let mut elem = CubeT::default();

	elem.cube = cube;
	let now = Instant::now();
	let moves = ida_star(&corners, &edges1, &edges2, &mut elem);
	print_time_elapsed(now);
	moves
}
