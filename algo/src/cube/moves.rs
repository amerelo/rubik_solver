use rand::Rng;
use cube::print_3::{print_debug_cube}; //, print_test
use F_MOVE;

#[allow(dead_code)]
pub fn random_scrambling(cube: &mut Vec<u8>, n: i32)
{
	for _i in 0..n {
		let nbr = rand::thread_rng().gen_range(0, F_MOVE.len() -1);
		F_MOVE[nbr](cube);
	}
	print_debug_cube(&cube);
}

pub fn apply_u(cube: &mut Vec<u8>)
{
	cube.swap(8, 17);
	cube.swap(9, 18);
	cube.swap(10, 19);

	cube.swap(8, 14);
	cube.swap(9, 15);
	cube.swap(10, 16);

	cube.swap(8, 11);
	cube.swap(9, 12);
	cube.swap(10, 13);
	
	cube.swap(6, 3);
	cube.swap(6, 1);
	cube.swap(6, 4);

	cube.swap(5, 0);
	cube.swap(5, 2);
	cube.swap(5, 7);
}

pub fn apply_uprime(cube: &mut Vec<u8>)
{
	cube.swap(8, 11);
	cube.swap(9, 12);
	cube.swap(10, 13);

	cube.swap(8, 14);
	cube.swap(9, 15);
	cube.swap(10, 16);

	cube.swap(8, 17);
	cube.swap(9, 18);
	cube.swap(10, 19);

	cube.swap(6, 4);
	cube.swap(6, 1);
	cube.swap(6, 3);

	cube.swap(5, 7);
	cube.swap(5, 2);
	cube.swap(5, 0);

}

pub fn apply_u2(cube: &mut Vec<u8>)
{
	apply_u(cube);
	apply_u(cube);
}

pub fn apply_f(cube: &mut Vec<u8>)
{
	cube.swap(5, 14);
	cube.swap(6, 24);
	cube.swap(7, 34);

	cube.swap(5, 42);
	cube.swap(6, 41);
	cube.swap(7, 40);

	cube.swap(5, 30);
	cube.swap(6, 21);
	cube.swap(7, 10);

	cube.swap(12, 23);
	cube.swap(12, 32);
	cube.swap(12, 22);

	cube.swap(11, 13);
	cube.swap(11, 33);
	cube.swap(11, 31);
}

pub fn apply_fprime(cube: &mut Vec<u8>)
{
	cube.swap(5, 30);
	cube.swap(6, 21);
	cube.swap(7, 10);

	cube.swap(5, 42);
	cube.swap(6, 41);
	cube.swap(7, 40);

	cube.swap(5, 14);
	cube.swap(6, 24);
	cube.swap(7, 34);

	cube.swap(12, 22);
	cube.swap(12, 32);
	cube.swap(12, 23);

	cube.swap(11, 31);
	cube.swap(11, 33);
	cube.swap(11, 13);
}

pub fn apply_f2(cube: &mut Vec<u8>)
{
	apply_f(cube);
	apply_f(cube);
}

pub fn apply_r(cube: &mut Vec<u8>)
{
	cube.swap(17, 47);
	cube.swap(26, 44);
	cube.swap(37, 42);

	cube.swap(17, 33);
	cube.swap(26, 23);
	cube.swap(37, 13);

	cube.swap(17, 7);
	cube.swap(26, 4);
	cube.swap(37, 2);

	cube.swap(15, 25);
	cube.swap(15, 35);
	cube.swap(15, 24);

	cube.swap(14, 16);
	cube.swap(14, 36);
	cube.swap(14, 34);
}

pub fn apply_rprime(cube: &mut Vec<u8>)
{
	cube.swap(17, 7);
	cube.swap(26, 4);
	cube.swap(37, 2);

	cube.swap(17, 33);
	cube.swap(26, 23);
	cube.swap(37, 13);

	cube.swap(17, 47);
	cube.swap(26, 44);
	cube.swap(37, 42);

	cube.swap(15, 24);
	cube.swap(15, 35);
	cube.swap(15, 25);

	cube.swap(14, 34);
	cube.swap(14, 36);
	cube.swap(14, 16);
}

pub fn apply_r2(cube: &mut Vec<u8>)
{
	apply_r(cube);
	apply_r(cube);
}

pub fn apply_d(cube: &mut Vec<u8>)
{
	cube.swap(28, 31);
	cube.swap(29, 32);
	cube.swap(30, 33);

	cube.swap(28, 34);
	cube.swap(29, 35);
	cube.swap(30, 36);

	cube.swap(28, 37);
	cube.swap(29, 38);
	cube.swap(30, 39);

	cube.swap(41, 44);
	cube.swap(41, 46);
	cube.swap(41, 43);

	cube.swap(40, 42);
	cube.swap(40, 47);
	cube.swap(40, 45);
}

pub fn apply_dprime(cube: &mut Vec<u8>)
{
	cube.swap(28, 37);
	cube.swap(29, 38);
	cube.swap(30, 39);

	cube.swap(28, 34);
	cube.swap(29, 35);
	cube.swap(30, 36);

	cube.swap(28, 31);
	cube.swap(29, 32);
	cube.swap(30, 33);

	cube.swap(41, 43);
	cube.swap(41, 46);
	cube.swap(41, 44);

	cube.swap(40, 45);
	cube.swap(40, 47);
	cube.swap(40, 42);
}

pub fn apply_d2(cube: &mut Vec<u8>)
{
	apply_d(cube);
	apply_d(cube);
}

pub fn apply_b(cube: &mut Vec<u8>)
{
	cube.swap(0, 28);
	cube.swap(1, 20);
	cube.swap(2, 8);

	cube.swap(0, 47);
	cube.swap(1, 46);
	cube.swap(2, 45);

	cube.swap(0, 16);
	cube.swap(1, 25);
	cube.swap(2, 36);

	cube.swap(18, 27);
	cube.swap(18, 38);
	cube.swap(18, 26);

	cube.swap(17, 19);
	cube.swap(17, 39);
	cube.swap(17, 37);
}

pub fn apply_bprime(cube: &mut Vec<u8>)
{
	cube.swap(0, 16);
	cube.swap(1, 25);
	cube.swap(2, 36);

	cube.swap(0, 47);
	cube.swap(1, 46);
	cube.swap(2, 45);

	cube.swap(0, 28);
	cube.swap(1, 20);
	cube.swap(2, 8);

	cube.swap(18, 26);
	cube.swap(18, 38);
	cube.swap(18, 27);

	cube.swap(17, 37);
	cube.swap(17, 39);
	cube.swap(17, 19);
}

pub fn apply_b2(cube: &mut Vec<u8>)
{
	apply_b(cube);
	apply_b(cube);
}

pub fn apply_l(cube: &mut Vec<u8>)
{
	cube.swap(0, 11);
	cube.swap(3, 22);
	cube.swap(5, 31);

	cube.swap(0, 40);
	cube.swap(3, 43);
	cube.swap(5, 45);

	cube.swap(0, 39);
	cube.swap(3, 27);
	cube.swap(5, 19);

	cube.swap(9, 21);
	cube.swap(9, 29);
	cube.swap(9, 20);

	cube.swap(8, 10);
	cube.swap(8, 30);
	cube.swap(8, 28);
}

pub fn apply_lprime(cube: &mut Vec<u8>)
{
	cube.swap(0, 39);
	cube.swap(3, 27);
	cube.swap(5, 19);

	cube.swap(0, 40);
	cube.swap(3, 43);
	cube.swap(5, 45);

	cube.swap(0, 11);
	cube.swap(3, 22);
	cube.swap(5, 31);

	cube.swap(9, 20);
	cube.swap(9, 29);
	cube.swap(9, 21);

	cube.swap(8, 28);
	cube.swap(8, 30);
	cube.swap(8, 10);
}

pub fn apply_l2(cube: &mut Vec<u8>)
{
	apply_l(cube);
	apply_l(cube);
}
