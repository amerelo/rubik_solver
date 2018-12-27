//
// Created by hjeannin on 13/11/17.
//

#ifndef OBJECT_LOADER_HPP
# define OBJECT_LOADER_HPP

# include <GLM/vec2.hpp>
# include <GLM/vec3.hpp>
# include <GLM/vec4.hpp>
# include "GLFW/glfw3.h"
# include <fstream>
# include <iostream>
# include <sstream>
# include "Constant.hpp"

enum smooth_status
{
    DON_T_KNOW,
    IS_SMOOTH,
    IS_NOT_SMOOTH
};

class ObjectLoader
{

public:
    const char  *filename;
    int         data_formatting_status = UNDETERMINED;
    int         smooth_status = DON_T_KNOW;
    GLuint      binded_array_buffer_id;
    GLuint      binded_element_buffer_id;

    typedef struct  s_indexed_interleaved_data
    {
        GLfloat     *array;
        GLuint      num_elem;
        GLuint      mem_size;
        GLsizei     stride;
        GLuint      *index;
        GLuint      index_num_elem;
        GLuint      index_mem_size;
    }               t_indexed_interleaved_data;

    glm::vec3   *vertex_array;
    GLuint      vertex_array_num_elem = 0;
    glm::vec2   *uv_array;
    GLuint      uv_array_num_elem = 0;
    glm::vec3   *normal_array;
    GLuint      normal_array_num_elem = 0;
    GLuint      *v_index_array;
    GLuint      v_index_array_num_elem = 0;
    GLuint      *uv_index_array;
    GLuint      uv_index_array_num_elem = 0;
    GLuint      *n_index_array;
    GLuint      n_index_array_num_elem = 0;

    GLfloat     *interleaved_fat_data_array;
    GLuint      interleaved_fat_data_num_elem = 0;
    GLuint      interleaved_fat_data_mem_size = 0;

    t_indexed_interleaved_data  iid;

    ObjectLoader();

    ~ObjectLoader();

    explicit ObjectLoader(const char *filename);

    bool parseObjectFile();

    void fitIndexesToOpenGL();

    void makeOpenGLBuffer();

    void printParsedData();

    void createFATInterleavedData();

    void createIndexedInterleavedData();

    void printIIDArray();

    void freeTemporaryMemory();

    void freeInterleavedData();
};

#endif //OBJECT_LOADER_HPP
