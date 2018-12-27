// use std::time::Instant;
use std::collections::{VecDeque, HashMap};

static APPLICABLEMOVES: &[i32; 5] = &[0, 262143, 259263, 74943, 74898];
static AFFECTEDCUBIES: &[ &[i32; 8]] = &[
	&[0, 1, 2, 3, 0, 1, 2, 3], // U
	&[4, 7, 6, 5, 4, 5, 6, 7], // D
	&[0, 9, 4, 8, 0, 3, 5, 4], // F
	&[2, 10, 6, 11, 2, 1, 7, 6], // B
	&[3, 11, 7, 9, 3, 2, 6, 5], // L
	&[1, 8, 5, 10, 1, 0, 4, 7], // R
];

pub fn star_thistletheaite(cube: Vec< String >) -> String
{
	let goal: Vec<String> = vec!["UF".to_owned(), "UR".to_owned(), "UB".to_owned(), "UL".to_owned(), "DF".to_owned(), "DR".to_owned(), "DB".to_owned(), "DL".to_owned(), "FR".to_owned(), "FL".to_owned(), "BR".to_owned(), "BL".to_owned(),
	"UFR".to_owned(), "URB".to_owned(), "UBL".to_owned(), "ULF".to_owned(), "DRF".to_owned(), "DFL".to_owned(), "DLB".to_owned(), "DBR".to_owned()];
	
	let mut current : Vec<i32> = vec![0; 40];
	let mut last : Vec<i32> = vec![0; 40];
	let mut list_moves : Vec<String> = vec![];

	for i in 0..20 {
		last[i] = i as i32;

		let mut cubie = cube[i].clone();
		while !goal.contains(&cubie) {
			let letter = cubie.remove(0);
			cubie.push( letter );
			current[i + 20] += 1;
		}
		current[i] = goal.iter().position(|r| r == &cubie).unwrap() as i32;
	}
	// println!("goald {:?}", last);
	// println!("current {:?}", current);

	loop_phase(&mut current, &mut last, &mut list_moves);
	// println!("END == current {:?}", current);
    
    println!("Solution Found in {} moves", list_moves.len());
	list_moves.join(" ")
}

fn loop_phase(currentstate: &mut Vec<i32>, goalstate: &mut Vec<i32>, list_moves : &mut Vec<String>)
{
	for phase in 1..5 {
		let mut currentid : Vec<i32> = get_id(&currentstate, phase);
		let mut goalid = get_id(&goalstate, phase);

		if currentid == goalid {
			continue;
		}
		let mut q: VecDeque<Vec<i32> > = VecDeque::default();
		q.push_back(currentstate.clone());
		q.push_back(goalstate.clone());
		let mut predecessor: HashMap<Vec<i32>, Vec<i32> > = HashMap::default();
		let mut moves: HashMap<Vec<i32>, i32 > = HashMap::default();
		let mut lastmove: HashMap<Vec<i32>, i32 > = HashMap::default();
		moves.insert(currentid.clone(), 1);
		moves.insert(goalid.clone(), 2);

		// println!("  phase {:?}", phase);
		internal_loop(phase, q, moves, &mut predecessor, &mut lastmove, &mut currentid, &goalid, currentstate, list_moves);
	}
}

fn internal_loop(phase: i32, mut q: VecDeque<Vec<i32> >, mut moves: HashMap< Vec<i32>, i32>, predecessor: &mut HashMap<Vec<i32>, 
	Vec<i32> >, lastmove: &mut HashMap<Vec<i32>, i32 > ,currentid: &mut Vec<i32>, goalid: &Vec<i32>, mut currentstate: &mut Vec<i32>, 
	list_moves : &mut Vec<String>)
{
	loop {
		let oldstate: Vec<i32>;
		match q.pop_front() {
			Some(elem) => oldstate = elem,
			None => panic!("no elem in queue"),
		}
		let mut oldid = get_id(&oldstate, phase);
		let olddir = get_map_id(&moves, &oldid);
		for m in 0..18 {
			if ((&APPLICABLEMOVES[phase as usize]) & (1 << m)) != 0 {
				let mut newstate = oldstate.clone();
				apply_move(m, &mut newstate);
				let mut newid = get_id(&newstate, phase);
				let newdir = get_map_id(&moves, &newid);
				let mut mv = m;
				match (newdir, olddir) {
					(Some(new), Some(old)) if new != old => {
						if old > 1 {
							// println!("rev");
							let mut tmp = newid;
							newid = oldid;
							oldid = tmp;
							mv = inverse(m);
						}

						let mut algorithm = vec![mv; 1];

						let mut count = oldid.iter().zip(currentid.iter()).filter(|&(a, b)| a == b).count();
						let mut oldlen = oldid.len();
						let mut newold: & Vec<i32> = & oldid.clone();
						while count != oldlen {
							algorithm.insert(0, *lastmove.get(newold).unwrap());
							newold = predecessor.get(newold).unwrap();
							count = newold.iter().zip(currentid.iter()).filter(|&(a, b)| a == b).count();
							oldlen = newold.len();
						}

						let mut count = newid.iter().zip(goalid.iter()).filter(|&(a, b)| a == b).count();
						let mut newlen = newid.len();
						let mut new: & Vec<i32> = & newid.clone();
						while count != newlen {
							algorithm.push(inverse(*lastmove.get(new).unwrap()));
							new = predecessor.get(new).unwrap();
							count = new.iter().zip(goalid.iter()).filter(|&(a, b)| a == b).count();
							newlen = new.len();
						}
						
						for t in 0..algorithm.len() {
							let mut fmove: String = "UDFBLR".chars().nth((algorithm[t] / 3 )as usize).unwrap().to_owned().to_string();
								// .chars().enumerate().position(|(i, _)| i as i32 == algorithm[t] / 3).unwrap()
							match algorithm[t] % 3 + 1 {
								2 => fmove.push_str("2"),
								3 => fmove.push_str("'"),
								_ => {;},
							};
							list_moves.push(fmove);
							apply_move(algorithm[t], &mut currentstate);
						}
						return ;
					},
					(None, Some(old)) => {
						q.push_back( newstate );
						moves.insert(newid.clone(), old.clone());
						lastmove.insert(newid.clone(), mv);
						predecessor.insert(newid.clone(), oldid.clone());
					},
					(_, _) => {;},
				}
			}
		}
	}
}

fn apply_move(m: i32, state: &mut Vec<i32> ) {
	let mut turns = m % 3;
	let face: usize = (m / 3) as usize;

	while turns >= 0 {
		let oldstate = state.clone();
		for i in 0..8 {
			let isorner = (i > 3) as i32;
			let target = AFFECTEDCUBIES[face][i as usize] + isorner * 12;
			let tmp: usize = if (i & 3) == 3 {i - 3} else {i + 1 };
			let or = AFFECTEDCUBIES[face][tmp] + isorner * 12;
			let orientation = if i < 4 { (face > 1 && face < 4) as i32} 
				else if face < 2 { 0 as i32}
				else {(2 - (i & 1)) as i32};
			state[target as usize] = oldstate[or as usize];

			state[(target + 20) as usize] = (oldstate[(or + 20) as usize] + orientation) % (2 + isorner);
			state[(target + 20) as usize] = oldstate[(or + 20) as usize] + orientation;
			if turns == 0 {
				state[(target + 20) as usize] %= 2 + isorner;
			}
		}
		turns -= 1;
	}
}

fn inverse(m: i32) -> i32 {
	m + 2 - 2 * (m % 3)
}

fn get_map_id(moves: &HashMap< Vec<i32>, i32>, key : &Vec<i32>) -> Option<i32>
{
	match moves.get(key) {
		Some(val)	=> Some(*val),
		None 		=> None,
	}
}

fn get_id(state: &Vec<i32>, phase: i32) -> Vec<i32>
{
	//--- Phase 1: Edge orientations.
	if phase < 2 {
		return state.iter().enumerate().filter(|&(i, _a)| i >= 20 && i < 32).map(|(_, &a)| a).collect();
	}
	//-- Phase 2: Corner orientations, E slice edges.
	if phase < 3 {
		let mut result : Vec<i32> = state.iter().enumerate().filter(|&(i, _a)| i >= 31 && i < 40).map(|(_, &a)| a).collect();
		for e in 0..12 {
			result[0] |= (state[e] / 8) << e;
		}
		return result;
	}
	//--- Phase 3: Edge slices M and S, corner tetrads, overall parity.
	if phase < 4 {
		let mut result : Vec<i32> = vec![0; 3];
		for e in 0..12 {
			result[0] |= (if state[e] > 7 {2} else {state[e] & 1}) << (3*e)
		}
		for c in 0..8 {
			result[1] |= ((state[c + 12 ] - 12) & 5) << (3 * c);
		}
		for i in 12..20 {
			for j in (i + 1)..20 {
				result[2] ^= (state[i] > state[j]) as i32;
			}
		}
		return result;
	}
	//--- Phase 4: The rest.
	return state.clone();
}
