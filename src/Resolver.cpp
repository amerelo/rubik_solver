#include "../inc/Resolver.hpp"

// int main(void) {
// 	rust_function();
// 	unsigned char numbers[48] = {1,2,3,4,5,6,7,8,9,10,
// 								11,12,13,14,15,16,17,18,19,20,
// 								21,22,23,24,25,26,27,28,29,30,
// 								31,32,33,34,35,36,37,38,39,40,
// 								41,42,43,44,45,46,47,48};
// 	void *top = load();
// 	buffer_t buf = Start_korf(numbers, sizeof(numbers), top);
// 	destroy(top);
// 	// printf("%zu\n", buf.size);
// 	// printf("%s\n", buf.str[0]);
// 	// printf("%s\n", buf.str[1]);
// 	// free_buf(buf);
// 	return (0);
//  }

Resolver::Resolver()
{
    createResolvedState(current_state);

    std::cout << "Now loading databases." << std::endl;
    this->database = NULL;

    _id_2_move_func_array[0] = apply_U;
    _id_2_move_func_array[1] = apply_U2;
    _id_2_move_func_array[2] = apply_Uprime;
    _id_2_move_func_array[3] = apply_D;
    _id_2_move_func_array[4] = apply_D2;
    _id_2_move_func_array[5] = apply_Dprime;
    _id_2_move_func_array[6] = apply_R;
    _id_2_move_func_array[7] = apply_R2;
    _id_2_move_func_array[8] = apply_Rprime;
    _id_2_move_func_array[9] = apply_L;
    _id_2_move_func_array[10] = apply_L2;
    _id_2_move_func_array[11] = apply_Lprime;
    _id_2_move_func_array[12] = apply_F;
    _id_2_move_func_array[13] = apply_F2;
    _id_2_move_func_array[14] = apply_Fprime;
    _id_2_move_func_array[15] = apply_B;
    _id_2_move_func_array[16] = apply_B2;
    _id_2_move_func_array[17] = apply_Bprime;

    _id_2_tiny_move_func_array[ 0] = apply_U;
    _id_2_tiny_move_func_array[ 1] = apply_Uprime;
    _id_2_tiny_move_func_array[ 2] = apply_D;
    _id_2_tiny_move_func_array[ 3] = apply_Dprime;
    _id_2_tiny_move_func_array[ 4] = apply_R;
    _id_2_tiny_move_func_array[ 5] = apply_Rprime;
    _id_2_tiny_move_func_array[ 6] = apply_L;
    _id_2_tiny_move_func_array[ 7] = apply_Lprime;
    _id_2_tiny_move_func_array[ 8] = apply_F;
    _id_2_tiny_move_func_array[ 9] = apply_Fprime;
    _id_2_tiny_move_func_array[10] = apply_B;
    _id_2_tiny_move_func_array[11] = apply_Bprime;
    std::cerr << "Resolver() constructor called." << std::endl;

    result.clear();
}

Resolver::~Resolver()
{
    std::cerr << "Resolver() destructor called." << std::endl;
    if (this->database)
        destroy(this->database);
}

std::string Resolver::solveState()
{
        /*
    Pour Amerelo
    Utiliser la fonction comme ca:

    TaFonctionDeResolutionRust(current_state[48]);

    current_state[48] est comment le rubik est configure en ce moment, il correspond aussi a ce que tu as en 3D.
    /////////////////////////////////////////////////////////////////
    ///
    ///                  [ 0][ 1][ 2]
    ///                  [ 3][ U][ 4]
    ///                  [ 5][ 6][ 7]
    ///
    ///     [ 8][ 9][10] [11][12][13] [14][15][16] [17][18][19]
    ///     [20][ L][21] [22][ F][23] [24][ R][25] [26][ B][27]
    ///     [28][29][30] [31][32][33] [34][35][36] [37][38][39]
    ///
    ///                  [40][41][42]
    ///                  [43][ D][44]
    ///                  [45][46][47]
    ///
    ////////////////////////////////////////////////////////////////

    en retour j'attend std::string     result; qui est une string avec chaque move pour resoudre le current_state[48],
     avec chaque move sous cette forme.
            "U ", "U2 ", "U' ",
            "D ", "D2 ", "D' ",
            "R ", "R2 ", "R' ",
            "L ", "L2 ", "L' ",
            "F ", "F2 ", "F' ",
            "B ", "B2 ", "B' "
     ( fait bien attention chaque move est separe par un espace ex: "U L2 B L' R " )
     ( Je vais le lire avec cette fonction Core::createPlayList() qui ajouter des data a queue des animation 3D)
     ( Tu peux aussi me r'envoyer des int et je les converti avec id_2_move_text_array[X] )
    */

//    std::cerr << "shuffle amount = " << shuffle_amount << std::endl;
    char * tmp;
    // result.clear();
    if (used_algo == DATABASE_ALGO)
        tmp = Start_korf(current_state, 48, database);
    else if (used_algo == FAST_ALGO)
        tmp = thistletheaite(current_state, 48);
    else
    {
        std::cerr << "Can't find the algo you want to use:" << used_algo << std::endl;
    }

    // int size = 0;
    // while(buf.str[size])
    // {
    //     std::cout << buf.str[size] << std::endl;
    //     size++;
    // }

    // prettyRubikCubePrint(current_state);
    // 	unsigned char numbers[48] = {1,2,3,4,5,6,7,8,9,10,
    // 								11,12,13,14,15,16,17,18,19,20,
    // 								21,22,23,24,25,26,27,28,29,30,
    // 								31,32,33,34,35,36,37,38,39,40,
    // 								41,42,43,44,45,46,47,48};
    // destroy(top);
    // 	// printf("%zu\n", buf.size);
    // 	// printf("%s\n", buf.str[0]);
    // 	// printf("%s\n", buf.str[1]);
    // 	// free_buf(buf);

    // simpleBruteForce();
    /// EXEMPLE: return result in string form exemple: 'U2 U2 '
    //    result.append(id_2_move_text_array[1]);
    //    result.append(id_2_move_text_array[1]);
    result = tmp;
    string_free(tmp);
    return (result);
}

void Resolver::switchAlgo()
{
    std::cout << "Switching Algo: ";
    if (used_algo == DATABASE_ALGO)
    {
        used_algo = FAST_ALGO;
        std::cout << "Fast Algo" << std::endl;
    }
    else if (used_algo == FAST_ALGO)
    {
        if (!this->database)
            this->database = load();
        used_algo = DATABASE_ALGO;
        std::cout << "DataBase Algo" << std::endl;
    }
    else
        std::cerr << "Can't switch algo." << std::endl;
}

void Resolver::stateCopy(int *src, int *dst)
{
    for (int i = 0; i < 48; ++i)
    {
        dst[i] = src[i];
    }
}

void Resolver::createResolvedState(int dst[48])
{
    for (int k = 0; k < 48; ++k)
    {
        dst[k] = k;
    }
}

int Resolver::scoreState(int src[48])
{
    int score;

    score = 0;
    for (int i = 0; i < 48; ++i)
    {
        if (src[i] == i)
            score++;
    }
    return (score);
}

void Resolver::addIDtoResult(int id)
{
    result.append(id_2_move_text_array[id]);
}

void Resolver::addTinyIDtoResult(int id)
{
    result.append(_id_2_tiny_move_text_array[id]);
}

void Resolver::twoDigitOnly(int i, int id)
{
    if (i >= 40 && i <= 48)
        std::cout << "\033[42m\033[30m";    // Green
    else if (i == 8 || i == 9 || i == 10 || i == 20 || i == 21 || i == 28 || i == 29 || i == 30)
        std::cout << "\033[43m\033[30m";    // Yellow
    else if (i == 11 || i == 12 || i == 13 || i == 22 || i == 23 || i == 31 || i == 32 || i == 33)
        std::cout << "\033[44m\033[30m";    // Blue
    else if (i == 14 || i == 15 || i == 16 || i == 24 || i == 25 || i == 34 || i == 35 || i == 36)
        std::cout << "\033[45m\033[30m";    // Orange
    else if (i == 17 || i == 18 || i == 19 || i == 26 || i == 27 || i == 37 || i == 38 || i == 39)
        std::cout << "\033[41m\033[30m";    // Red
    else if (i >= 0 && i <= 7)
        std::cout << "\033[47m\033[30m";    // White
    if (i == id)
    {
        if (i < 10 && i >= 0)
            std::cout << "( " << i << ")";
        else
            std::cout << "(" << i << ")";
    }
    else
    {
        if (i < 10 && i >= 0)
            std::cout << "[ " << i << "]";
        else
            std::cout << "[" << i << "]";
    }
    std::cout << "\033[0m";
}

void Resolver::prettyRubikCubePrint(int src[48])
{
//    std::cout << "\033[33mHH\033[0m\n";
    std::cout << std::endl << "                  ";
    twoDigitOnly(src[0], 0);
    twoDigitOnly(src[1], 1);
    twoDigitOnly(src[2], 2);
    std::cout << std::endl << "                  ";
    twoDigitOnly(src[3], 3);
    std::cout << "\033[47m[ U]\033[0m";
    twoDigitOnly(src[4], 4);
    std::cout << std::endl << "                  ";
    twoDigitOnly(src[5], 5);
    twoDigitOnly(src[6], 6);
    twoDigitOnly(src[7], 7);
    std::cout << std::endl;

    std::cout << std::endl << "     ";
    twoDigitOnly(src[8], 8);
    twoDigitOnly(src[9], 9);
    twoDigitOnly(src[10], 10);
    std::cout << " ";
    twoDigitOnly(src[11], 11);
    twoDigitOnly(src[12], 12);
    twoDigitOnly(src[13], 13);
    std::cout << " ";
    twoDigitOnly(src[14], 14);
    twoDigitOnly(src[15], 15);
    twoDigitOnly(src[16], 16);
    std::cout << " ";
    twoDigitOnly(src[17], 17);
    twoDigitOnly(src[18], 18);
    twoDigitOnly(src[19], 19);
    std::cout << std::endl << "     ";
    twoDigitOnly(src[20], 20);
    std::cout << "\033[43m[ L]\033[0m";
    twoDigitOnly(src[21], 21);
    std::cout << " ";
    twoDigitOnly(src[22], 22);
    std::cout << "\033[44m[ F]\033[0m";
    twoDigitOnly(src[23], 23);
    std::cout << " ";
    twoDigitOnly(src[24], 24);
    std::cout << "\033[45m[ R]\033[0m";
    twoDigitOnly(src[25], 25);
    std::cout << " ";
    twoDigitOnly(src[26], 26);
    std::cout << "\033[41m[ B]\033[0m";
    twoDigitOnly(src[27], 27);
    std::cout << std::endl << "     ";
    twoDigitOnly(src[28], 28);
    twoDigitOnly(src[29], 29);
    twoDigitOnly(src[30], 30);
    std::cout << " ";
    twoDigitOnly(src[31], 31);
    twoDigitOnly(src[32], 32);
    twoDigitOnly(src[33], 33);
    std::cout << " ";
    twoDigitOnly(src[34], 34);
    twoDigitOnly(src[35], 35);
    twoDigitOnly(src[36], 36);
    std::cout << " ";
    twoDigitOnly(src[37], 37);
    twoDigitOnly(src[38], 38);
    twoDigitOnly(src[39], 39);
    std::cout << std::endl;

    std::cout << std::endl << "                  ";
    twoDigitOnly(src[40], 40);
    twoDigitOnly(src[41], 41);
    twoDigitOnly(src[42], 42);
    std::cout << std::endl << "                  ";
    twoDigitOnly(src[43], 43);
    std::cout << "\033[42m[ U]\033[0m";
    twoDigitOnly(src[44], 44);
    std::cout << std::endl << "                  ";
    twoDigitOnly(src[45], 45);
    twoDigitOnly(src[46], 46);
    twoDigitOnly(src[47], 47);
    std::cout << std::endl;
}

void Resolver::applyFromID(int id, int src[48], int dst[48], bool verbose)
{
    (_id_2_move_func_array[id])(src, dst);
    if (verbose)
        std::cerr << id_2_move_text_array[id];
}

void Resolver::applyFromTinyID(int id, int src[48], int dst[48], bool verbose)
{
    (_id_2_tiny_move_func_array[id])(src, dst);
    if (verbose)
        std::cerr << _id_2_tiny_move_text_array[id];
}

void Resolver::apply_U(int src[48], int dst[48])
{
    /// Who ever is in pos X goes in pos Y
    int temp[20];

    temp[0] = src[0];
    temp[1] = src[1];
    temp[2] = src[2];
    temp[3] = src[3];
    temp[4] = src[4];
    temp[5] = src[5];
    temp[6] = src[6];
    temp[7] = src[7];
    temp[8] = src[8];
    temp[9] = src[9];
    temp[10] = src[10];
    temp[11] = src[11];
    temp[12] = src[12];
    temp[13] = src[13];
    temp[14] = src[14];
    temp[15] = src[15];
    temp[16] = src[16];
    temp[17] = src[17];
    temp[18] = src[18];
    temp[19] = src[19];

    dst[2] = temp[0];
    dst[4] = temp[1];
    dst[7] = temp[2];
    dst[1] = temp[3];
    dst[6] = temp[4];
    dst[0] = temp[5];
    dst[3] = temp[6];
    dst[5] = temp[7];
    dst[17] = temp[8];
    dst[18] = temp[9];
    dst[19] = temp[10];
    dst[8] = temp[11];
    dst[9] = temp[12];
    dst[10] = temp[13];
    dst[11] = temp[14];
    dst[12] = temp[15];
    dst[13] = temp[16];
    dst[14] = temp[17];
    dst[15] = temp[18];
    dst[16] = temp[19];
}

void Resolver::apply_U2(int src[48], int dst[48])
{
    int temp[20];

    temp[0] = src[0];
    temp[1] = src[1];
    temp[2] = src[2];
    temp[3] = src[3];
    temp[4] = src[4];
    temp[5] = src[5];
    temp[6] = src[6];
    temp[7] = src[7];
    temp[8] = src[8];
    temp[9] = src[9];
    temp[10] = src[10];
    temp[11] = src[11];
    temp[12] = src[12];
    temp[13] = src[13];
    temp[14] = src[14];
    temp[15] = src[15];
    temp[16] = src[16];
    temp[17] = src[17];
    temp[18] = src[18];
    temp[19] = src[19];

    dst[7] = temp[0];
    dst[6] = temp[1];
    dst[5] = temp[2];
    dst[4] = temp[3];
    dst[3] = temp[4];
    dst[2] = temp[5];
    dst[1] = temp[6];
    dst[0] = temp[7];
    dst[14] = temp[8];
    dst[15] = temp[9];
    dst[16] = temp[10];
    dst[17] = temp[11];
    dst[18] = temp[12];
    dst[19] = temp[13];
    dst[8] = temp[14];
    dst[9] = temp[15];
    dst[10] = temp[16];
    dst[11] = temp[17];
    dst[12] = temp[18];
    dst[13] = temp[19];
}

void Resolver::apply_Uprime(int src[48], int dst[48])
{
    int temp[20];

    temp[0] = src[0];
    temp[1] = src[1];
    temp[2] = src[2];
    temp[3] = src[3];
    temp[4] = src[4];
    temp[5] = src[5];
    temp[6] = src[6];
    temp[7] = src[7];
    temp[8] = src[8];
    temp[9] = src[9];
    temp[10] = src[10];
    temp[11] = src[11];
    temp[12] = src[12];
    temp[13] = src[13];
    temp[14] = src[14];
    temp[15] = src[15];
    temp[16] = src[16];
    temp[17] = src[17];
    temp[18] = src[18];
    temp[19] = src[19];

    dst[5] = temp[0];
    dst[3] = temp[1];
    dst[0] = temp[2];
    dst[6] = temp[3];
    dst[1] = temp[4];
    dst[7] = temp[5];
    dst[4] = temp[6];
    dst[2] = temp[7];
    dst[11] = temp[8];
    dst[12] = temp[9];
    dst[13] = temp[10];
    dst[14] = temp[11];
    dst[15] = temp[12];
    dst[16] = temp[13];
    dst[17] = temp[14];
    dst[18] = temp[15];
    dst[19] = temp[16];
    dst[8] = temp[17];
    dst[9] = temp[18];
    dst[10] = temp[19];
}

void Resolver::apply_D(int src[48], int dst[48])
{
    int temp[20];

    temp[0] = src[31];
    temp[1] = src[32];
    temp[2] = src[33];
    temp[3] = src[34];
    temp[4] = src[35];
    temp[5] = src[36];
    temp[6] = src[37];
    temp[7] = src[38];
    temp[8] = src[39];
    temp[9] = src[28];
    temp[10] = src[29];
    temp[11] = src[30];

    temp[12] = src[40];
    temp[13] = src[41];
    temp[14] = src[42];
    temp[15] = src[44];
    temp[16] = src[47];
    temp[17] = src[46];
    temp[18] = src[45];
    temp[19] = src[43];

    dst[34] = temp[0];
    dst[35] = temp[1];
    dst[36] = temp[2];
    dst[37] = temp[3];
    dst[38] = temp[4];
    dst[39] = temp[5];
    dst[28] = temp[6];
    dst[29] = temp[7];
    dst[30] = temp[8];
    dst[31] = temp[9];
    dst[32] = temp[10];
    dst[33] = temp[11];

    dst[42] = temp[12];
    dst[44] = temp[13];
    dst[47] = temp[14];
    dst[46] = temp[15];
    dst[45] = temp[16];
    dst[43] = temp[17];
    dst[40] = temp[18];
    dst[41] = temp[19];
}

void Resolver::apply_D2(int src[48], int dst[48])
{
    int temp[20];

    temp[0] = src[31];
    temp[1] = src[32];
    temp[2] = src[33];
    temp[3] = src[34];
    temp[4] = src[35];
    temp[5] = src[36];
    temp[6] = src[37];
    temp[7] = src[38];
    temp[8] = src[39];
    temp[9] = src[28];
    temp[10] = src[29];
    temp[11] = src[30];

    temp[12] = src[40];
    temp[13] = src[41];
    temp[14] = src[42];
    temp[15] = src[44];
    temp[16] = src[47];
    temp[17] = src[46];
    temp[18] = src[45];
    temp[19] = src[43];

    dst[37] = temp[0];
    dst[38] = temp[1];
    dst[39] = temp[2];
    dst[28] = temp[3];
    dst[29] = temp[4];
    dst[30] = temp[5];
    dst[31] = temp[6];
    dst[32] = temp[7];
    dst[33] = temp[8];
    dst[34] = temp[9];
    dst[35] = temp[10];
    dst[36] = temp[11];

    dst[47] = temp[12];
    dst[46] = temp[13];
    dst[45] = temp[14];
    dst[43] = temp[15];
    dst[40] = temp[16];
    dst[41] = temp[17];
    dst[42] = temp[18];
    dst[44] = temp[19];
}

void Resolver::apply_Dprime(int src[48], int dst[48])
{
    int temp[20];

    temp[0] = src[31];
    temp[1] = src[32];
    temp[2] = src[33];
    temp[3] = src[34];
    temp[4] = src[35];
    temp[5] = src[36];
    temp[6] = src[37];
    temp[7] = src[38];
    temp[8] = src[39];
    temp[9] = src[28];
    temp[10] = src[29];
    temp[11] = src[30];

    temp[12] = src[40];
    temp[13] = src[41];
    temp[14] = src[42];
    temp[15] = src[44];
    temp[16] = src[47];
    temp[17] = src[46];
    temp[18] = src[45];
    temp[19] = src[43];

    dst[28] = temp[0];
    dst[29] = temp[1];
    dst[30] = temp[2];
    dst[31] = temp[3];
    dst[32] = temp[4];
    dst[33] = temp[5];
    dst[34] = temp[6];
    dst[35] = temp[7];
    dst[36] = temp[8];
    dst[37] = temp[9];
    dst[38] = temp[10];
    dst[39] = temp[11];

    dst[45] = temp[12];
    dst[43] = temp[13];
    dst[40] = temp[14];
    dst[41] = temp[15];
    dst[42] = temp[16];
    dst[44] = temp[17];
    dst[47] = temp[18];
    dst[46] = temp[19];
}

void Resolver::apply_R(int src[48], int dst[48])
{
    int temp[20];

    temp[0] = src[7];
    temp[1] = src[4];
    temp[2] = src[2];
    temp[3] = src[17];
    temp[4] = src[26];
    temp[5] = src[37];
    temp[6] = src[47];
    temp[7] = src[44];
    temp[8] = src[42];
    temp[9] = src[33];
    temp[10] = src[23];
    temp[11] = src[13];

    temp[12] = src[14];
    temp[13] = src[15];
    temp[14] = src[16];
    temp[15] = src[25];
    temp[16] = src[36];
    temp[17] = src[35];
    temp[18] = src[34];
    temp[19] = src[24];

    dst[17] = temp[0];
    dst[26] = temp[1];
    dst[37] = temp[2];
    dst[47] = temp[3];
    dst[44] = temp[4];
    dst[42] = temp[5];
    dst[33] = temp[6];
    dst[23] = temp[7];
    dst[13] = temp[8];
    dst[7] = temp[9];
    dst[4] = temp[10];
    dst[2] = temp[11];

    dst[16] = temp[12];
    dst[25] = temp[13];
    dst[36] = temp[14];
    dst[35] = temp[15];
    dst[34] = temp[16];
    dst[24] = temp[17];
    dst[14] = temp[18];
    dst[15] = temp[19];
}

void Resolver::apply_R2(int src[48], int dst[48])
{
    int temp[20];

    temp[0] = src[7];
    temp[1] = src[4];
    temp[2] = src[2];
    temp[3] = src[17];
    temp[4] = src[26];
    temp[5] = src[37];
    temp[6] = src[47];
    temp[7] = src[44];
    temp[8] = src[42];
    temp[9] = src[33];
    temp[10] = src[23];
    temp[11] = src[13];

    temp[12] = src[14];
    temp[13] = src[15];
    temp[14] = src[16];
    temp[15] = src[25];
    temp[16] = src[36];
    temp[17] = src[35];
    temp[18] = src[34];
    temp[19] = src[24];

    dst[47] = temp[0];
    dst[44] = temp[1];
    dst[42] = temp[2];
    dst[33] = temp[3];
    dst[23] = temp[4];
    dst[13] = temp[5];
    dst[7] = temp[6];
    dst[4] = temp[7];
    dst[2] = temp[8];
    dst[17] = temp[9];
    dst[26] = temp[10];
    dst[37] = temp[11];

    dst[36] = temp[12];
    dst[35] = temp[13];
    dst[34] = temp[14];
    dst[24] = temp[15];
    dst[14] = temp[16];
    dst[15] = temp[17];
    dst[16] = temp[18];
    dst[25] = temp[19];
}

void Resolver::apply_Rprime(int src[48], int dst[48])
{
    int temp[20];

    temp[0] = src[7];
    temp[1] = src[4];
    temp[2] = src[2];
    temp[3] = src[17];
    temp[4] = src[26];
    temp[5] = src[37];
    temp[6] = src[47];
    temp[7] = src[44];
    temp[8] = src[42];
    temp[9] = src[33];
    temp[10] = src[23];
    temp[11] = src[13];

    temp[12] = src[14];
    temp[13] = src[15];
    temp[14] = src[16];
    temp[15] = src[25];
    temp[16] = src[36];
    temp[17] = src[35];
    temp[18] = src[34];
    temp[19] = src[24];

    dst[33] = temp[0];
    dst[23] = temp[1];
    dst[13] = temp[2];
    dst[7] = temp[3];
    dst[4] = temp[4];
    dst[2] = temp[5];
    dst[17] = temp[6];
    dst[26] = temp[7];
    dst[37] = temp[8];
    dst[47] = temp[9];
    dst[44] = temp[10];
    dst[42] = temp[11];

    dst[34] = temp[12];
    dst[24] = temp[13];
    dst[14] = temp[14];
    dst[15] = temp[15];
    dst[16] = temp[16];
    dst[25] = temp[17];
    dst[36] = temp[18];
    dst[35] = temp[19];
}

void Resolver::apply_L(int src[48], int dst[48])
{
    int temp[20];

    temp[0] = src[0];
    temp[1] = src[3];
    temp[2] = src[5];
    temp[3] = src[11];
    temp[4] = src[22];
    temp[5] = src[31];
    temp[6] = src[40];
    temp[7] = src[43];
    temp[8] = src[45];
    temp[9] = src[39];
    temp[10] = src[27];
    temp[11] = src[19];

    temp[12] = src[8];
    temp[13] = src[9];
    temp[14] = src[10];
    temp[15] = src[21];
    temp[16] = src[30];
    temp[17] = src[29];
    temp[18] = src[28];
    temp[19] = src[20];

    dst[11] = temp[0];
    dst[22] = temp[1];
    dst[31] = temp[2];
    dst[40] = temp[3];
    dst[43] = temp[4];
    dst[45] = temp[5];
    dst[39] = temp[6];
    dst[27] = temp[7];
    dst[19] = temp[8];
    dst[0] = temp[9];
    dst[3] = temp[10];
    dst[5] = temp[11];

    dst[10] = temp[12];
    dst[21] = temp[13];
    dst[30] = temp[14];
    dst[29] = temp[15];
    dst[28] = temp[16];
    dst[20] = temp[17];
    dst[8] = temp[18];
    dst[9] = temp[19];
}

void Resolver::apply_L2(int src[48], int dst[48])
{
    int temp[20];

    temp[0] = src[0];
    temp[1] = src[3];
    temp[2] = src[5];
    temp[3] = src[11];
    temp[4] = src[22];
    temp[5] = src[31];
    temp[6] = src[40];
    temp[7] = src[43];
    temp[8] = src[45];
    temp[9] = src[39];
    temp[10] = src[27];
    temp[11] = src[19];

    temp[12] = src[8];
    temp[13] = src[9];
    temp[14] = src[10];
    temp[15] = src[21];
    temp[16] = src[30];
    temp[17] = src[29];
    temp[18] = src[28];
    temp[19] = src[20];

    dst[40] = temp[0];
    dst[43] = temp[1];
    dst[45] = temp[2];
    dst[39] = temp[3];
    dst[27] = temp[4];
    dst[19] = temp[5];
    dst[0] = temp[6];
    dst[3] = temp[7];
    dst[5] = temp[8];
    dst[11] = temp[9];
    dst[22] = temp[10];
    dst[31] = temp[11];

    dst[30] = temp[12];
    dst[29] = temp[13];
    dst[28] = temp[14];
    dst[20] = temp[15];
    dst[8] = temp[16];
    dst[9] = temp[17];
    dst[10] = temp[18];
    dst[21] = temp[19];
}

void Resolver::apply_Lprime(int src[48], int dst[48])
{
    int temp[20];

    temp[0] = src[0];
    temp[1] = src[3];
    temp[2] = src[5];
    temp[3] = src[11];
    temp[4] = src[22];
    temp[5] = src[31];
    temp[6] = src[40];
    temp[7] = src[43];
    temp[8] = src[45];
    temp[9] = src[39];
    temp[10] = src[27];
    temp[11] = src[19];

    temp[12] = src[8];
    temp[13] = src[9];
    temp[14] = src[10];
    temp[15] = src[21];
    temp[16] = src[30];
    temp[17] = src[29];
    temp[18] = src[28];
    temp[19] = src[20];

    dst[39] = temp[0];
    dst[27] = temp[1];
    dst[19] = temp[2];
    dst[0] = temp[3];
    dst[3] = temp[4];
    dst[5] = temp[5];
    dst[11] = temp[6];
    dst[22] = temp[7];
    dst[31] = temp[8];
    dst[40] = temp[9];
    dst[43] = temp[10];
    dst[45] = temp[11];

    dst[28] = temp[12];
    dst[20] = temp[13];
    dst[8] = temp[14];
    dst[9] = temp[15];
    dst[10] = temp[16];
    dst[21] = temp[17];
    dst[30] = temp[18];
    dst[29] = temp[19];
}

void Resolver::apply_F(int src[48], int dst[48])
{
    int temp[20];

    temp[0] = src[5];
    temp[1] = src[6];
    temp[2] = src[7];
    temp[3] = src[14];
    temp[4] = src[24];
    temp[5] = src[34];
    temp[6] = src[42];
    temp[7] = src[41];
    temp[8] = src[40];
    temp[9] = src[30];
    temp[10] = src[21];
    temp[11] = src[10];

    temp[12] = src[11];
    temp[13] = src[12];
    temp[14] = src[13];
    temp[15] = src[23];
    temp[16] = src[33];
    temp[17] = src[32];
    temp[18] = src[31];
    temp[19] = src[22];

    dst[14] = temp[0];
    dst[24] = temp[1];
    dst[34] = temp[2];
    dst[42] = temp[3];
    dst[41] = temp[4];
    dst[40] = temp[5];
    dst[30] = temp[6];
    dst[21] = temp[7];
    dst[10] = temp[8];
    dst[5] = temp[9];
    dst[6] = temp[10];
    dst[7] = temp[11];

    dst[13] = temp[12];
    dst[23] = temp[13];
    dst[33] = temp[14];
    dst[32] = temp[15];
    dst[31] = temp[16];
    dst[22] = temp[17];
    dst[11] = temp[18];
    dst[12] = temp[19];
}

void Resolver::apply_F2(int src[48], int dst[48])
{
    int temp[20];

    temp[0] = src[5];
    temp[1] = src[6];
    temp[2] = src[7];
    temp[3] = src[14];
    temp[4] = src[24];
    temp[5] = src[34];
    temp[6] = src[42];
    temp[7] = src[41];
    temp[8] = src[40];
    temp[9] = src[30];
    temp[10] = src[21];
    temp[11] = src[10];

    temp[12] = src[11];
    temp[13] = src[12];
    temp[14] = src[13];
    temp[15] = src[23];
    temp[16] = src[33];
    temp[17] = src[32];
    temp[18] = src[31];
    temp[19] = src[22];

    dst[42] = temp[0];
    dst[41] = temp[1];
    dst[40] = temp[2];
    dst[30] = temp[3];
    dst[21] = temp[4];
    dst[10] = temp[5];
    dst[5] = temp[6];
    dst[6] = temp[7];
    dst[7] = temp[8];
    dst[14] = temp[9];
    dst[24] = temp[10];
    dst[34] = temp[11];

    dst[33] = temp[12];
    dst[32] = temp[13];
    dst[31] = temp[14];
    dst[22] = temp[15];
    dst[11] = temp[16];
    dst[12] = temp[17];
    dst[13] = temp[18];
    dst[23] = temp[19];
}

void Resolver::apply_Fprime(int src[48], int dst[48])
{
    int temp[20];

    temp[0] = src[5];
    temp[1] = src[6];
    temp[2] = src[7];
    temp[3] = src[14];
    temp[4] = src[24];
    temp[5] = src[34];
    temp[6] = src[42];
    temp[7] = src[41];
    temp[8] = src[40];
    temp[9] = src[30];
    temp[10] = src[21];
    temp[11] = src[10];

    temp[12] = src[11];
    temp[13] = src[12];
    temp[14] = src[13];
    temp[15] = src[23];
    temp[16] = src[33];
    temp[17] = src[32];
    temp[18] = src[31];
    temp[19] = src[22];

    dst[30] = temp[0];
    dst[21] = temp[1];
    dst[10] = temp[2];
    dst[5] = temp[3];
    dst[6] = temp[4];
    dst[7] = temp[5];
    dst[14] = temp[6];
    dst[24] = temp[7];
    dst[34] = temp[8];
    dst[42] = temp[9];
    dst[41] = temp[10];
    dst[40] = temp[11];

    dst[31] = temp[12];
    dst[22] = temp[13];
    dst[11] = temp[14];
    dst[12] = temp[15];
    dst[13] = temp[16];
    dst[23] = temp[17];
    dst[33] = temp[18];
    dst[32] = temp[19];
}

void Resolver::apply_B(int src[48], int dst[48])
{
    int temp[20];

    temp[ 0] = src[ 0];
    temp[ 1] = src[ 1];
    temp[ 2] = src[ 2];
    temp[ 3] = src[16];
    temp[ 4] = src[25];
    temp[ 5] = src[36];
    temp[ 6] = src[47];
    temp[ 7] = src[46];
    temp[ 8] = src[45];
    temp[ 9] = src[28];
    temp[10] = src[20];
    temp[11] = src[ 8];

    temp[12] = src[17];
    temp[13] = src[18];
    temp[14] = src[19];
    temp[15] = src[27];
    temp[16] = src[39];
    temp[17] = src[38];
    temp[18] = src[37];
    temp[19] = src[26];

    dst[28] = temp[ 0];
    dst[20] = temp[ 1];
    dst[ 8] = temp[ 2];
    dst[ 0] = temp[ 3];
    dst[ 1] = temp[ 4];
    dst[ 2] = temp[ 5];
    dst[16] = temp[ 6];
    dst[25] = temp[ 7];
    dst[36] = temp[ 8];
    dst[47] = temp[ 9];
    dst[46] = temp[10];
    dst[45] = temp[11];

    dst[19] = temp[12];
    dst[27] = temp[13];
    dst[39] = temp[14];
    dst[38] = temp[15];
    dst[37] = temp[16];
    dst[26] = temp[17];
    dst[17] = temp[18];
    dst[18] = temp[19];
}

void Resolver::apply_B2(int src[48], int dst[48])
{
    int temp[20];

    temp[ 0] = src[ 0];
    temp[ 1] = src[ 1];
    temp[ 2] = src[ 2];
    temp[ 3] = src[16];
    temp[ 4] = src[25];
    temp[ 5] = src[36];
    temp[ 6] = src[47];
    temp[ 7] = src[46];
    temp[ 8] = src[45];
    temp[ 9] = src[28];
    temp[10] = src[20];
    temp[11] = src[ 8];

    temp[12] = src[17];
    temp[13] = src[18];
    temp[14] = src[19];
    temp[15] = src[27];
    temp[16] = src[39];
    temp[17] = src[38];
    temp[18] = src[37];
    temp[19] = src[26];

    dst[47] = temp[ 0];
    dst[46] = temp[ 1];
    dst[45] = temp[ 2];
    dst[28] = temp[ 3];
    dst[20] = temp[ 4];
    dst[ 8] = temp[ 5];
    dst[ 0] = temp[ 6];
    dst[ 1] = temp[ 7];
    dst[ 2] = temp[ 8];
    dst[16] = temp[ 9];
    dst[25] = temp[10];
    dst[36] = temp[11];

    dst[39] = temp[12];
    dst[38] = temp[13];
    dst[37] = temp[14];
    dst[26] = temp[15];
    dst[17] = temp[16];
    dst[18] = temp[17];
    dst[19] = temp[18];
    dst[27] = temp[19];
}

void Resolver::apply_Bprime(int src[48], int dst[48])
{
    int temp[20];

    temp[ 0] = src[ 0];
    temp[ 1] = src[ 1];
    temp[ 2] = src[ 2];
    temp[ 3] = src[16];
    temp[ 4] = src[25];
    temp[ 5] = src[36];
    temp[ 6] = src[47];
    temp[ 7] = src[46];
    temp[ 8] = src[45];
    temp[ 9] = src[28];
    temp[10] = src[20];
    temp[11] = src[ 8];

    temp[12] = src[17];
    temp[13] = src[18];
    temp[14] = src[19];
    temp[15] = src[27];
    temp[16] = src[39];
    temp[17] = src[38];
    temp[18] = src[37];
    temp[19] = src[26];

    dst[16] = temp[ 0];
    dst[25] = temp[ 1];
    dst[36] = temp[ 2];
    dst[47] = temp[ 3];
    dst[46] = temp[ 4];
    dst[45] = temp[ 5];
    dst[28] = temp[ 6];
    dst[20] = temp[ 7];
    dst[ 8] = temp[ 8];
    dst[ 0] = temp[ 9];
    dst[ 1] = temp[10];
    dst[ 2] = temp[11];

    dst[37] = temp[12];
    dst[26] = temp[13];
    dst[17] = temp[14];
    dst[18] = temp[15];
    dst[19] = temp[16];
    dst[27] = temp[17];
    dst[39] = temp[18];
    dst[38] = temp[19];
}
