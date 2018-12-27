//
// Created by Hugo JEANNIN on 3/10/17.
//

#ifndef CORE_HPP
# define CORE_HPP
# if defined(__APPLE_CC__)
#  ifndef GLFW_INCLUDE_GLCOREARB
#   define GLFW_INCLUDE_GLCOREARB
#  endif
#  ifndef GLFW_INCLUDE_GLEXT
#   define GLFW_INCLUDE_GLEXT
#  endif
# else
#  define GL_GLEXT_PROTOTYPES
# endif

# include <GLFW/glfw3.h>

# include <thread>
# include <iostream>
# include <cmath>
# include <GLM/ext.hpp>
# include <GLM/detail/type_mat4x4.hpp>

# include "Resolver.hpp"
# include "Constant.hpp"
# include "ShaderManager.hpp"
# include "Camera.hpp"
# include "Animation.hpp"
# include "TextureManager.hpp"
# include "ObjectLoader.hpp"
# include "Skybox.hpp"
# include <queue>
# include <iterator>

class Core
{
public:
    GLFWwindow      *window;

    glm::mat4       vp_matrix;
    glm::mat4       mvp_matrix;
    glm::vec3       light_pos;

    GLuint          res_x;
    GLuint          res_y;

    GLuint          vaos[VAO_NUM];
    GLuint          vbos[VBO_NUM];
    GLuint          fbos[FBO_NUM];
    GLuint          texture_IDs[TEX_NUM];

    TextureManager  texture_manager;

    ObjectLoader    *object_cube_rubik;
    ObjectLoader    *object_cube_rubik_low_poly;
    ObjectLoader    *object_cube_block;
    ObjectLoader    *object_square;
    Skybox          skybox;

    Resolver        resolver;

    Animation       animation;

    Camera          camera;

    ShaderManager   shader_manager;
    GLuint          shader_program_id[SHADER_NUM];

    // Attribute Locations for every shader:
    GLuint          position_loc = 0;
    GLuint          normal_loc = 1;
    GLuint          texture_coordinates_loc = 2;
    GLuint          color_loc = 1;

    GLuint          m_mvp_matrix_loc;
    GLuint          m_camera_pos_loc;
    GLuint          m_model_loc;
    GLuint          m_texture_loc;
    GLuint          m_light_pos_loc;

    GLuint          r_mvp_matrix_loc;
    GLuint          r_frame_texture_loc;
    GLuint          r_alpha_texture_loc;
    GLuint          r_alpha_indice_loc;

    GLuint          ss_texture_loc;

    bool            render_axes_on = false;

    bool            anim_queue_is_running = false;
    std::queue<void (Animation::*)()>      anim_queue;
    std::queue<int>                        resolv_queue;
    std::vector<std::string>        raw_play_list_sequence;
    bool            anim_delayer = false;

    Core();

    ~Core();

    void init();

    bool loadShaders();

    void getShadersLocations();

    void createBuffers();

    void loadTextures();

    void renderAxes();
    void renderSkybox(glm::mat4 &camera_matrix, glm::mat4 &camera_perspective_matrix);
    void renderModels();
    void renderReflection();
    void renderReflectionSquare();

    void renderImage();

    GLfloat *createAxesBuffer();

    void loadSequences();
    void addRandomMoves(int amount);
    void createPlayList(std::string raw_instructions);
    void runPlayList();

    void resolveRubik();
};

#endif //CORE_HPP
