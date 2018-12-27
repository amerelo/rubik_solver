#include <iostream>
#include "../inc/Skybox.hpp"

Skybox::Skybox()
{
    return ;
}

Skybox::~Skybox()
{
    return ;
}

void
Skybox::generateModel(void)
{
    //////////////////////////////////////////////////////////////////
    //                                           					//
    //          4----5		        ^  Y	                     	//
    //         /|   /|              |                     .------.  //
    //       0----1  |              |                    /          //
    //       |  7-|--6              |----->  X          |    <-.    //
    //       |/   | /              /                     \      |   //
    //       3____2               /                        \___/    //
    //                          |,  Z                               //
    //                                           DEFAULT is GL_CCW  //
    //////////////////////////////////////////////////////////////////

    model.v_num_elem = 8 * 3;
    model.f_num_elem = 36;
    model.v_array = new GLfloat[model.v_num_elem];
    model.f_array = new GLuint[model.f_num_elem];
    model.v_mem_size = sizeof(GLfloat) * model.v_num_elem;
    model.f_mem_size = sizeof(GLuint) * model.f_num_elem;

    model.v_array[0] = -0.5f;
    model.v_array[1] = 0.5f;
    model.v_array[2] = 0.5f;

    model.v_array[3] = 0.5f;
    model.v_array[4] = 0.5f;
    model.v_array[5] = 0.5f;

    model.v_array[6] = 0.5f;
    model.v_array[7] = -0.5f;
    model.v_array[8] = 0.5f;

    model.v_array[9] = -0.5f;
    model.v_array[10] = -0.5f;
    model.v_array[11] = 0.5f;

    model.v_array[12] = -0.5f;
    model.v_array[13] = 0.5f;
    model.v_array[14] = -0.5f;

    model.v_array[15] = 0.5f;
    model.v_array[16] = 0.5f;
    model.v_array[17] = -0.5f;

    model.v_array[18] = 0.5f;
    model.v_array[19] = -0.5f;
    model.v_array[20] = -0.5f;

    model.v_array[21] = -0.5f;
    model.v_array[22] = -0.5f;
    model.v_array[23] = -0.5f;

    model.f_array[0] = 0;
    model.f_array[1] = 1;
    model.f_array[2] = 2;

    model.f_array[3] = 0;
    model.f_array[4] = 2;
    model.f_array[5] = 3;

    model.f_array[6] = 1;
    model.f_array[7] = 5;
    model.f_array[8] = 6;

    model.f_array[9] = 1;
    model.f_array[10] = 6;
    model.f_array[11] = 2;

    model.f_array[12] = 5;
    model.f_array[13] = 4;
    model.f_array[14] = 7;

    model.f_array[15] = 5;
    model.f_array[16] = 7;
    model.f_array[17] = 6;

    model.f_array[18] = 4;
    model.f_array[19] = 0;
    model.f_array[20] = 3;

    model.f_array[21] = 4;
    model.f_array[22] = 3;
    model.f_array[23] = 7;

    model.f_array[24] = 1;
    model.f_array[25] = 0;
    model.f_array[26] = 4;

    model.f_array[27] = 1;
    model.f_array[28] = 4;
    model.f_array[29] = 5;

    model.f_array[30] = 6;
    model.f_array[31] = 7;
    model.f_array[32] = 3;

    model.f_array[33] = 6;
    model.f_array[34] = 3;
    model.f_array[35] = 2;
}

void Skybox::print()
{
    std::cerr << "face: ";
    for (int i = 0; i < model.f_num_elem; ++i)
    {
        std::cerr << "[" << model.f_array[i] << "]";
    }
    std::cerr << std::endl;
    std::cerr << "vertex: ";
    for (int i = 0; i < model.v_num_elem; ++i)
    {
        std::cerr << "[" << model.v_array[i] << "]";
    }
    std::cerr << std::endl;

}