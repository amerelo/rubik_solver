#ifndef SKYBOX_HPP
# define SKYBOX_HPP

# include <GLFW/glfw3.h>
# include <vector>
#include <GLM/vec3.hpp>

class Skybox
{
public:

    struct ModelData
    {
        GLuint			v_mem_size;
        GLuint			v_num_elem;
        GLfloat         *v_array;
        GLuint			f_mem_size;
        GLuint			f_num_elem;
        GLuint			*f_array;
    };

    ModelData       model;

    Skybox(void);
    ~Skybox(void);

    void        generateModel(void);
    void        print(void);
};

#endif
