
#ifndef RESOLVER_HPP
# define RESOLVER_HPP

# include <iostream>
# include <string>
# include <cmath>
# include <map>
# include <stdio.h>

typedef struct Data t_data;

typedef struct {
	char **str;
	size_t size;
} buffer_t;

extern "C" void rust_function();
extern "C" void *load();
extern "C" void start();
// extern "C" buffer_t Start_korf(int *, size_t, void *);
extern "C" char *Start_korf(int *, size_t, void *);
extern "C" char *thistletheaite(int *, size_t);

// extern "C" buffer_t Start_korf(unsigned char *, size_t, void *);
extern "C" void string_free(char * str);
extern "C" void free_buf(buffer_t buf);
extern "C" void destroy(void *data);

enum    moves
{
    U, U2, Up, D, D2, Dp, R, R2, Rp, L, L2, Lp, F, F2, Fp, B, B2, Bp
};

enum    algo
{
    DATABASE_ALGO,
    FAST_ALGO
};

class Resolver
{
private:

    const std::string     _id_2_tiny_move_text_array[12] = {

            "U ", "U' ",
            "D ", "D' ",
            "R ", "R' ",
            "L ", "L' ",
            "F ", "F' ",
            "B ", "B' "
    };

    void (*_id_2_move_func_array[18])(int src[48], int dst[48]);
    void (*_id_2_tiny_move_func_array[12])(int src[48], int dst[48]);

public:
    const std::string id_2_move_text_array[18] = {

            "U ", "U2 ", "U' ",
            "D ", "D2 ", "D' ",
            "R ", "R2 ", "R' ",
            "L ", "L2 ", "L' ",
            "F ", "F2 ", "F' ",
            "B ", "B2 ", "B' "
    };

    int             used_algo = FAST_ALGO;
    int             current_state[48];
    bool            play_list_will_resolve = false;
    std::string     result;
    void            *database;

    Resolver();
    ~Resolver();

    /// Algo
    std::string solveState();
    void switchAlgo();

    /// Tools
    void stateCopy(int src[48], int dst[48]);
    void createResolvedState(int dst[48]);
    int  scoreState(int src[48]);

    /// Print
    void twoDigitOnly(int i, int id);
    void prettyRubikCubePrint(int src[48]);

    /// Transformations
    void addIDtoResult(int id);
    void addTinyIDtoResult(int id);
    void applyFromID(int id, int src[48], int dst[48], bool verbose = false);
    void applyFromTinyID(int id, int src[48], int dst[48], bool verbose = false);

    static void apply_U(int src[48], int dst[48]);
    static void apply_U2(int src[48], int dst[48]);
    static void apply_Uprime(int src[48], int dst[48]);
    static void apply_D2(int src[48], int dst[48]);
    static void apply_Dprime(int src[48], int dst[48]);
    static void apply_D(int src[48], int dst[48]);
    static void apply_R(int src[48], int dst[48]);
    static void apply_R2(int src[48], int dst[48]);
    static void apply_Rprime(int src[48], int dst[48]);
    static void apply_L(int src[48], int dst[48]);
    static void apply_L2(int src[48], int dst[48]);
    static void apply_Lprime(int src[48], int dst[48]);
    static void apply_F(int src[48], int dst[48]);
    static void apply_F2(int src[48], int dst[48]);
    static void apply_Fprime(int src[48], int dst[48]);
    static void apply_B(int src[48], int dst[48]);
    static void apply_B2(int src[48], int dst[48]);
    static void apply_Bprime(int src[48], int dst[48]);

};

#endif //RESOLVER_HPP


    ////////////////////////////////////
    ///     X   ->  ORANGE  ->  RIGHT
    ///     Y   ->  WHITE   ->  UP
    ///     Z   ->  BLUE    ->  FRONT
    ///     -X  ->  YELLOW  ->  LEFT
    ///     -Y  ->  GREEN   ->  DOWN
    ///     -Z  ->  RED     ->  BACK
    ////////////////////////////////////
    ////////////////////////////////////////////////////////////////
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
