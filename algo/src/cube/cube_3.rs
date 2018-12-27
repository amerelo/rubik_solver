use std::default::Default;
use std::cmp::Ordering;
use std::collections::{HashSet, BinaryHeap};
use std::hash::{Hash, Hasher};
use fnv::FnvHashSet;

static CORNERS: &[u8] = &[0, 19, 8, 2, 16, 17, 5, 10, 11, 7, 13, 14, 40, 31, 30, 42, 33, 34, 45, 39, 28, 47, 36, 37];
static EDGES: &[u8] = &[1, 3, 4, 6, 9, 12, 15, 18, 20, 21, 22, 23, 24, 25, 26, 27, 29, 32, 35, 38, 41, 43, 44, 46];

pub enum CubeKind {
	CORNERS,
	EDGES1,
	EDGES2,
}

#[derive(Serialize, Deserialize, Clone, Eq, Debug)]
pub struct Elem {
	pub cube: Vec<u8>,
	pub heuristic: u8,
	pub moves: Vec<u8>,
	pub step: u8,
}

impl Default for Elem {
	fn default() -> Elem {
		Elem {
			cube: vec![],
			moves: vec![],
			step: 0,
			heuristic:0,
		}
	}
}

fn eq_corners(cube1: &Vec<u8> , cube2: &Vec<u8>) -> bool
{
	cube1.get(0) == cube2.get(0) && cube1.get(2) == cube2.get(2) && cube1.get(5) == cube2.get(5) &&
	cube1.get(7) == cube2.get(7) && cube1.get(40) == cube2.get(40) && cube1.get(42) == cube2.get(42) &&
	cube1.get(45) == cube2.get(45) && cube1.get(47) == cube2.get(47)
}

impl PartialEq for Elem {
	fn eq(&self, other: &Elem) -> bool {
		eq_corners(&self.cube , &other.cube)
	}
}

impl Hash for Elem {
	fn hash<H: Hasher>(&self, state: &mut H) {
		self.cube.hash(state);
	}
}

impl Ord for Elem {
	fn cmp(&self, other: &Elem) -> Ordering {
		//other.glob_heuristic.cmp(&self.glob_heuristic)
		other.heuristic.cmp(&self.heuristic)
		// other.total_cost.cmp(&self.total_cost)
		// .then_with(|| other.glob_heuristic.cmp(&self.glob_heuristic))
	}
}

impl PartialOrd for Elem {
	fn partial_cmp(&self, other: &Elem) -> Option<Ordering> {
		Some(self.cmp(other))
	}
}

#[allow(dead_code)]
pub fn gen_cube3() -> Vec<u8>
{
	let mut cube = vec![];

	for i in 0..48 {
		cube.push(i);
	}
	cube
}

#[derive(Serialize, Deserialize, Debug)]
pub struct Cube3 {
	pub open_l: BinaryHeap<Elem>,
	pub close_l: HashSet<Elem>,
}

impl Default for Cube3 {
	fn default() -> Cube3 {
		Cube3 {
			open_l: BinaryHeap::new(),
			close_l: HashSet::new()
		}
	}
}

#[derive(Serialize, Deserialize, Eq, Clone, Debug)]
pub struct CubeT {
	pub cube: Vec<u8>,
	pub last_move: u8,
	pub step: u8,
	pub moves: u8,
}

impl Default for CubeT {
	fn default() -> CubeT {
		CubeT {
			cube: vec![],
			last_move: 0,
			step: 0,
			moves: 0,
		}
	}
}

impl Ord for CubeT {
	fn cmp(&self, other: &CubeT) -> Ordering {
		self.step.cmp(&other.step)
		.then_with(|| other.last_move.cmp(&self.last_move))
		.then_with(|| other.moves.cmp(&self.moves))
	}
}

impl PartialOrd for CubeT {
	fn partial_cmp(&self, other: &CubeT) -> Option<Ordering> {
		Some(self.cmp(other))
	}
}


impl PartialEq for CubeT {
	fn eq(&self, other: &CubeT) -> bool {
		&self.cube == &other.cube
	}
}

impl Hash for CubeT {
	fn hash<H: Hasher>(&self, state: &mut H) {
		self.cube.hash(state);
	}
}


#[derive(Serialize, Deserialize, Clone, Eq, Debug)]
pub struct KElem {
	pub cube: u64,
}

impl Default for KElem {
	fn default() -> KElem {
		KElem {
			cube: 0,
		}
	}
}

impl PartialEq for KElem {
	fn eq(&self, other: &KElem) -> bool {
		(self.cube & 0xFFFFFFFFFF) == (other.cube & 0xFFFFFFFFFF)
	}
}

impl Hash for KElem {
	fn hash<H: Hasher>(&self, state: &mut H) {
		let real_cube = self.cube & 0xFFFFFFFFFF;
		real_cube.hash(state);
	}
}

#[derive(Serialize, Deserialize, Debug)]
pub struct CubeKorf {
	pub close_l: FnvHashSet<KElem>,
}

impl Default for CubeKorf {
	fn default() -> CubeKorf {
		CubeKorf {
			close_l: FnvHashSet::default()
			
		}
	}
}

pub fn get_index(val: u8, kind: &CubeKind, cube: &Vec<u8>) -> u64
{
	match kind {
		CubeKind::CORNERS	=> CORNERS.iter().position(|&r| r == val).unwrap() as u64,
		_ 					=> {
			let pos = cube.iter().position(|&r| r == val).unwrap() as u8;
			EDGES.iter().position(|&r| r == pos).unwrap() as u64
		},
	}
}

pub fn get_step(kelem: &KElem) -> u8
{
	(kelem.cube >> 45) as u8
}

pub fn get_move(kelem: &KElem) -> u16
{
	((kelem.cube >> 40) & 31) as u16
}

fn get_kind(tab: &[u16], elem: &CubeT, kelem: &mut KElem, kind: &CubeKind)
{
	for index in tab.iter() {
		kelem.cube <<= 5;
		match kind {
			CubeKind::CORNERS	=> kelem.cube += get_index(elem.cube[*index as usize] as u8, kind, &elem.cube),
			_					=> kelem.cube += get_index(*index as u8, kind, &elem.cube),
		}
	}
}

pub fn cube_to_kcube(elem: &CubeT, kelem: &mut KElem, kind: &CubeKind)
{
	let corners = [0, 2, 5, 7, 40, 42, 45, 47];
	let edges1 = [1, 3, 4, 6, 22, 23];
	let edges2 = [41, 43, 44, 46, 26, 27];

	kelem.cube = elem.step as u64;
	kelem.cube <<= 5;
	kelem.cube += elem.last_move as u64;
	match kind {
		CubeKind::CORNERS	=> (),
		_ 					=> kelem.cube <<= 10,
	}

	match kind {
		CubeKind::CORNERS => get_kind(&corners, elem, kelem, kind),
		CubeKind::EDGES1 => get_kind(&edges1, elem, kelem, kind),
		CubeKind::EDGES2 => get_kind(&edges2, elem, kelem, kind),
	}
}


fn match_face(piece: u8) -> String
{
	match piece {
		i if i <= 7																					=> "U".to_owned(),
		i if i >= 40																				=> "D".to_owned(),
		i if i == 8 || i == 9 || i == 10 || i == 20 || i == 21 || i == 28 || i == 29 || i == 30		=> "L".to_owned(),
		i if i == 14 || i == 15 || i == 16 || i == 24 || i == 25 || i == 34 || i == 35 || i == 36	=> "R".to_owned(),
		i if i == 11 || i == 12 || i == 13 || i == 22 || i == 23 || i == 31 || i == 32 || i == 33	=> "F".to_owned(),
		_																							=> "B".to_owned()
	}
}

// vec!["UF", "UR", "UB", "UL", "DF","DR", "DB","DL", "FR", "FL", "BR", "BL",
// "UFR", "URB", "UBL", "ULF",
// "DRF", "DFL", "DLB", "DBR"];
pub fn change_cube_format(cube: &Vec<u8>) -> Vec<String>
{
	//  6,  4,  1, 3,  41, 44, 46, 43,  23, 22,  26, 27
	// 12, 15, 18, 9,  32, 35, 38, 29,  24, 21,  25, 20
	let edge_pieces: &[&[u8; 2]; 12] =  &[
		&[6, 12], &[4, 15], &[1, 18], &[3, 9],
		&[41, 32], &[44, 35], &[46, 38], &[43, 29],
		&[23, 24], &[22, 21], &[26, 25], &[27, 20]
	];
	//  7,  2,  0,  5,  42, 40, 45, 47
	// 13, 16, 19, 10,  34, 31, 28, 37
	// 14, 17,  8, 11,  33, 30, 39, 36
	let corner_pieces: &[&[u8; 3]; 8] = &[
		&[7, 13,14], &[2, 16, 17], &[0, 19, 8], &[5, 10, 11],
		&[42, 34, 33], &[40, 31, 30], &[45, 28, 39], &[47, 37, 36]
	];

	let mut new_cube: Vec<String> = vec![];

	for piece_search in edge_pieces.iter() {
		let mut str1 = match_face(cube[piece_search[0] as usize]);
		str1.push_str(&match_face(cube[piece_search[1] as usize]));
		new_cube.push(str1);
	}

	for piece_search in corner_pieces.iter() {
		let mut str1 = match_face(cube[piece_search[0] as usize]);
		str1.push_str(&match_face(cube[piece_search[1] as usize]));
		str1.push_str(&match_face(cube[piece_search[2] as usize]));
		new_cube.push(str1);
	}
	new_cube
}
