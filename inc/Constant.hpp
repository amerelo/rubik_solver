//
// Created by Hugo JEANNIN on 5/21/17.
//

#ifndef CONSTANT_HPP
# define CONSTANT_HPP

//////////////
//  Config  //
//////////////

//#define FULL_SCREEN true
#define FULL_SCREEN false

//#define CONFIG_5k
//#define CONFIG_2_5k
//#define CONFIG_1080p
#define CONFIG_DEV

#ifdef CONFIG_5k

#  define SAMPLE_RATE 		1
#  define INITIAL_RES_X		5120
#  define INITIAL_RES_Y		2880

#endif
#ifdef CONFIG_2_5k

#  define SAMPLE_RATE 		1
#  define INITIAL_RES_X		2560
#  define INITIAL_RES_Y		1440

#endif

#ifdef CONFIG_1080p

#  define SAMPLE_RATE       4
#  define INITIAL_RES_X     1920
#  define INITIAL_RES_Y     1080

#endif

#ifdef CONFIG_DEV

#  define SAMPLE_RATE        4
#  define INITIAL_RES_X        1600
#  define INITIAL_RES_Y        900

#endif

# define REFL_TEX_RES       2048

//#define CURSOR_MODE		0x00034001		//NORMAL
#define CURSOR_MODE        0x00034002        //HIDDEN
//#define CURSOR_MODE		0x00034003		//DISABLED

//#define CAMERA_CFG_AUTO_LOAD    true
#define CAMERA_CFG_AUTO_LOAD    false

#define CAMERA_ROTATE_AROUND_ON     true
//#define CAMERA_ROTATE_AROUND_ON     false

//#define ANIMATION_VERBOSE   true
#define ANIMATION_VERBOSE   false

#define TICK_PER_SECOND     60.0f
#define TPS                 TICK_PER_SECOND

#define DEMO_ON_STARTUP     true
//#define DEMO_ON_STARTUP     false

//////////////
//  OpenGL  //
//////////////

# define SHADER_NUM         4
# define VAO_NUM            6
# define VBO_NUM            7
# define FBO_NUM            1
# define TEX_NUM            9
# define MODEL_NUM          4

enum shaders
{
    SHADER_AXES,
    SHADER_SKYBOX,
    SHADER_MODELS,
    SHADER_REFLECTION,
};

enum vaos
{
    VAO_AXES,
    VAO_SKYBOX,
    VAO_RUBIK,
    VAO_CUBE_BLOCK,
    VAO_LOW_POLY_RUBIK,
    VAO_SQUARE,
};

enum vbos
{
    VBO_AXES_LINES,
    VBO_SKYBOX_TRIANGLES,
    VBO_SKYBOX_FACES,
    VBO_RUBIK_INTERLEAVED,
    VBO_CUBE_BLOCK_INTERLEAVED,
    VBO_LOW_POLY_RUBIK_INTERLEAVED,
    VBO_SQUARE_INTERLEAVED,
};

enum fbos
{
    REFLECTION
};

enum textures
{
    TEX_RUBIK,
    TEX_LOW_POLY_RUBIK,
    TEX_BACKGROUND_BLOCK,
    TEX_SKYBOX,
    TEX_REFLECTION,
    TEX_REFLECTION_DEPTH,
    TEX_REFLECTION_ALPHA,
};

enum models
{
    UNDERTEMINED_MODEL,
    CUBE_RUBIK,
    CUBE_BLOCK,
    SQUARE_REFL,
};

enum data_formatting_status
{
    UNDETERMINED,
    INTERLEAVED_FAT_DATA,
    INDEXED_INTERLEAVED_DATA
};

#endif //CONSTANT_HPP
