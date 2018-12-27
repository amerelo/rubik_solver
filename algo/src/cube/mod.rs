pub mod moves;
pub mod print_3;
pub mod cube_3;
// pub mod heuristic_3;


//     X   ->  RED      ->  RIGHT
//     Y   ->  WHITE    ->  UP
//     Z   ->  GREEN    ->  FRONT
//     -X  ->  ORANGE   ->  LEFT
//     -Y  ->  YELLOW   ->  DOWN
//     -Z  ->  BLUE     ->  BACK
//
//                  [ 0][ 1][ 2]
//                  [ 3][ U][ 4]
//                  [ 5][ 6][ 7]
//
//     [ 8][ 9][10] [11][12][13] [14][15][16] [17][18][19]
//     [20][ L][21] [22][ F][23] [24][ R][25] [26][ B][27]
//     [28][29][30] [31][32][33] [34][35][36] [37][38][39]
//
//                  [40][41][42]
//                  [43][ D][44]
//                  [45][46][47]
//

// 5 11 3 17 12 17 12 17 12 2 4 10 2 4 0 5 13 12 2 0 4 1 5 3
// R' L' F' L2 U2 L2 U2 L2 U2 F R L  FRUR'U'F' U2 F U R U' R' F'

//   u => 0, u' => 1,
//   
//   f => 2, f' => 3,
//   
//   r => 4, r' => 5,
//   
//   d => 6, d' => 7,
//   
//   b => 8, b' => 9,
//   
//   l => 10, l' => 11,
// 
//   u2 => 12, f2 => 13, r2 => 14,
// 
// 	 d2 => 15, b2 => 16, l2 => 17

// F U2 D B F' R L R' D' B' B'

// U edges -> [1, 3, 4, 6]
// D edges -> [41, 43, 44, 46]
// 
// F edges -> [12, 22, 23, 32]
// B edges -> [18, 26, 27, 38]
// 
// L edges -> [9, 20, 21, 29]
// R edges -> [15, 24, 25, 35]
// 
// [0,19,8,2,16,17,5,10,11,7,13,14,40,31,30,42,33,34,45,39,28,47,36,37]
// 
// corners : val(0-1-2)
// 0-19-8
// 2-16-17
// 5-10-11
// 7-13-14
// 
// 40-31-30
// 42-33-34
// 45-39-28
// 47-36-37

// edges-1 : val(1-2)
// 1, 18
// 3, 9
// 4, 15
// 6, 12
// 22, 21
// 23, 24

// 41, 32
// 43, 29
// 44, 35
// 46, 38
// 26, 25
// 27, 20