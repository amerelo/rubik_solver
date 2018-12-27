use colored::*;
use cube::moves::*;

fn print_color(i: u8)
{
	if i >= 40 && i <= 48 {
		print!("{: >2} ", i.to_string().yellow().bold());
	} else if i == 8 || i == 9 || i == 10 || i == 20 || i == 21 || i == 28 || i == 29 || i == 30 {
		print!("{: >2} ", i.to_string().magenta().bold());
	} else if i == 11 || i == 12 || i == 13 || i == 22 || i == 23 || i == 31 || i == 32 || i == 33 {
		print!("{: >2} ", i.to_string().green().bold());
	} else if i == 14 || i == 15 || i == 16 || i == 24 || i == 25 || i == 34 || i == 35 || i == 36 {
		print!("{: >2} ", i.to_string().red().bold());
	} else if i == 17 || i == 18 || i == 19 || i == 26 || i == 27 || i == 37 || i == 38 || i == 39 {
		print!("{: >2} ", i.to_string().blue().bold());
	} else  {
		print!("{: >2} ", i.to_string().white().bold());
	}
}

pub fn print_debug_cube(cube: &Vec<u8>)
{
	print!("{}{:15}", "\n"," ");
	print_color(cube[0] as u8);
	print_color(cube[1] as u8);
	print_color(cube[2] as u8);
	print!("{}{:15}", "\n"," ");
	print_color(cube[3] as u8);
	print!("{: >3}", "U ".white().bold());
	print_color(cube[4] as u8);
	print!("{}{:15}", "\n"," ");
	print_color(cube[5] as u8);
	print_color(cube[6] as u8);
	print_color(cube[7] as u8);
	println!("");

	print!("{}{:5}", "\n"," ");
	print_color(cube[8] as u8);
	print_color(cube[9] as u8);
	print_color(cube[10] as u8);
	print!("{}"," ");
	print_color(cube[11] as u8);
	print_color(cube[12] as u8);
	print_color(cube[13] as u8);
	print!("{}"," ");
	print_color(cube[14] as u8);
	print_color(cube[15] as u8);
	print_color(cube[16] as u8);
	print!("{}"," ");
	print_color(cube[17] as u8);
	print_color(cube[18] as u8);
	print_color(cube[19] as u8);
	
	print!("{}{:5}", "\n"," ");
	print_color(cube[20] as u8);
	print!("{: >3}", "L ".magenta().bold());
	print_color(cube[21] as u8);
	print!("{}"," ");
	print_color(cube[22] as u8);
	print!("{: >3}", "F ".green().bold());
	print_color(cube[23] as u8);
	print!("{}"," ");
	print_color(cube[24] as u8);
	print!("{: >3}", "R ".red().bold());
	print_color(cube[25] as u8);
	print!("{}"," ");
	print_color(cube[26] as u8);
	print!("{: >3}", "B ".blue().bold());
	print_color(cube[27] as u8);
	
	print!("{}{:5}", "\n"," ");
	print_color(cube[28] as u8);
	print_color(cube[29] as u8);
	print_color(cube[30] as u8);
	print!("{}"," ");
	print_color(cube[31] as u8);
	print_color(cube[32] as u8);
	print_color(cube[33] as u8);
	print!("{}"," ");
	print_color(cube[34] as u8);
	print_color(cube[35] as u8);
	print_color(cube[36] as u8);
	print!("{}"," ");
	print_color(cube[37] as u8);
	print_color(cube[38] as u8);
	print_color(cube[39] as u8);

	print!("{}{:15}", "\n\n"," ");
	print_color(cube[40] as u8);
	print_color(cube[41] as u8);
	print_color(cube[42] as u8);
	print!("{}{:15}", "\n"," ");
	print_color(cube[43] as u8);
	print!("{: >3}", "D ".yellow().bold());
	print_color(cube[44] as u8);
	print!("{}{:15}", "\n"," ");
	print_color(cube[45] as u8);
	print_color(cube[46] as u8);
	print_color(cube[47] as u8);
	println!("");
	println!("--------------------------------------------------------");
}

#[allow(dead_code)]
pub fn print_test(cube: &mut Vec<u8>)
{
	print_debug_cube(&cube);

	apply_u(cube);
	print_debug_cube(&cube);
	apply_uprime(cube);

	print_debug_cube(&cube);

	apply_f(cube);
	print_debug_cube(&cube);
	apply_fprime(cube);

	print_debug_cube(&cube);

	apply_r(cube);
	print_debug_cube(&cube);
	apply_rprime(cube);

	print_debug_cube(&cube);

	apply_d(cube);
	print_debug_cube(&cube);
	apply_dprime(cube);

	print_debug_cube(&cube);

	apply_b(cube);
	print_debug_cube(&cube);
	apply_bprime(cube);

	print_debug_cube(&cube);

	apply_l(cube);
	print_debug_cube(&cube);
	apply_lprime(cube);

	print_debug_cube(&cube);
}
