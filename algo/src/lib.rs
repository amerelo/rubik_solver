#[macro_use]
extern crate serde_derive;
extern crate fnv;
extern crate serde;
extern crate bincode;
extern crate colored;
extern crate rand;
extern crate libc;

mod cube;
mod algorithmes;

use cube::{cube_3::*, moves::*, print_3::{print_debug_cube}};
use algorithmes::{ korf::*, thistlethwaite::*};
use std::slice;
use std::time::Instant;
use libc::{c_char};
use std::ffi::CString;

#[derive(Serialize, Deserialize, Debug)]
pub struct Info {
	pub lists: Cube3,
	pub steps: u8,
	pub fix_depth: Vec<u8>,
}

#[repr(C)]
pub struct Buffer {
	data: *mut *const u8,
	len: usize,
}

#[derive(Serialize, Deserialize, Debug)]
pub struct Data {
	pub lists: CubeKorf,
}

fn opposite_move(index: usize) -> u8 {
	match index {
		i if i > 11					=> i as u8,
		i if (i % 2 == 0)			=> (i + 1) as u8,
		i 							=> (i - 1) as u8,
	}
}

static F_MOVE: &[fn(&mut Vec<u8>)] = &[apply_u, apply_uprime, apply_f, apply_fprime,
	apply_r, apply_rprime, apply_d, apply_dprime, apply_b, apply_bprime, apply_l, apply_lprime, 

	apply_u2, apply_f2, apply_r2, apply_d2, apply_b2, apply_l2];
static S_MOVE: &[&str] = &["U ", "U' ", "F ", "F' ", "R ", "R' ", "D ", "D' ", "B ", "B' ", "L ", "L' ", "U2 ", "F2 ", "R2 ", "D2 ", "B2 ", "L2 "];

fn value_to_cmove(moves: &mut String, index: u8)
{
	moves.push_str(S_MOVE[index as usize].clone());
}


#[no_mangle]
pub extern "C" fn rust_function() {
	println!("Hello Lib");
}

#[no_mangle]
pub extern "C" fn Start_korf(ptr: *mut i32, size: usize, db_raw: *mut (Data, Data, Data)) -> *mut c_char
{
	unsafe {
		assert!(!ptr.is_null());
		let cube: Vec<u8> = slice::from_raw_parts(ptr, size).to_vec().iter().map(|&i| i as u8 ).collect();
		
		print_debug_cube(&cube);
		println!("cube {:?}", cube);
		
		assert!(!db_raw.is_null());
		let db = Box::from_raw(db_raw);
		let c_str_song = {
			let (corners, edges1, edges2) = db.as_ref();
			let moves = start_korf(cube, corners, edges1, edges2);
			
			// let mut buf: Vec<*const u8> = moves.iter().map(|&i| value_to_cmove(i)).collect();
			let mut moves_string: String = String::new();
			//  = moves.iter().map(|&i| value_to_cmove(i)).collect();
			for elem in moves.iter() {
				value_to_cmove(&mut moves_string, *elem);
			}
		 	CString::new(moves_string).unwrap()
		};
		std::mem::forget(db);
		return c_str_song.into_raw();
		// moves_string.push_str("\0");
		// let data = &mut*moves_string;
		// let len = buf.len();
		// std::mem::forget(moves_string);
		// return Buffer { data, len };
	};
}

#[no_mangle]
extern "C" fn free_buf(buf: Buffer) {
	let s = unsafe { std::slice::from_raw_parts_mut(buf.data, buf.len) };
	let s = s.as_mut_ptr();
	unsafe {
		Box::from_raw(s);
	}
}

#[no_mangle]
pub extern "C" fn load() -> *mut (Data, Data, Data)
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
	println!("all db's are loaded :)");
	let mut data = Box::new((corners, edges1, edges2));
	let ptr: *mut _ = &mut *data;
	// let test = Box::into_raw(data);
	std::mem::forget(data);
	ptr
}

#[no_mangle]
pub extern "C" fn destroy(ptr: &mut *mut (Data, Data, Data)) {
	if ptr.is_null() {
		return;
	}
	let obj: Box<(Data, Data, Data)> = unsafe { ::std::mem::transmute(*ptr) };

	// We don't *have* to do anything else; once obj goes out of scope, it will
	// be dropped.  I'm going to drop it explicitly, however, for clarity.
	::std::mem::drop(obj);
	// I am, however, going to null out the `ptr` we were passed just so the
	// calling code is less likely to accidentally re-use the pointer.
	*ptr = std::ptr::null_mut();
}


#[no_mangle]
pub extern "C" fn string_free(s: *mut c_char) {
	unsafe {
		if s.is_null() { return }
		CString::from_raw(s)
	};
}

#[no_mangle]
pub extern "C" fn thistletheaite(ptr: *mut i32, size: usize) -> *mut c_char
{
	let now = Instant::now();

	unsafe {
		assert!(!ptr.is_null());
		let cube: Vec<u8> = slice::from_raw_parts(ptr, size).to_vec().iter().map(|&i| i as u8 ).collect();
		print_debug_cube(&cube);

		let result = star_thistletheaite(change_cube_format(&cube));
		let c_str_song = {
			CString::new(result).unwrap()
		};

		print_time_elapsed(now);
		return c_str_song.into_raw();
	};

}