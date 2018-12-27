//
// Created by Hugo JEANNIN on 3/10/17.
//

#include "../inc/Core.hpp"

Core::Core()
{
    std::cerr << "Core() constructor called." << std::endl;
}

Core::~Core()
{
    glDeleteFramebuffers(1, fbos);
    glDeleteBuffers(VBO_NUM, vbos);
    glDeleteVertexArrays(VAO_NUM, vaos);
    glDeleteTextures(TEX_NUM, texture_IDs);
    std::cerr << "Core() destructor called." << std::endl;
}

void
Core::init()
{
    if (DEMO_ON_STARTUP)
        animation.demo_reflection_is_on = false;
    res_x = INITIAL_RES_X;
    res_y = INITIAL_RES_Y;
    camera.init();
    animation.init(&resolver);
    loadSequences();
    light_pos = glm::vec3(2.4f, 2.4f, 5.4f);
}

bool
Core::loadShaders()
{
    if (!shader_manager.read("../shaders/models.vertex.glsl", 0, "../shaders/models.fragment.glsl"))
        return false;
    shader_manager.compile();
    shader_program_id[SHADER_MODELS] = glCreateProgram();
    shader_manager.linkProgram(&shader_program_id[SHADER_MODELS]);

    if (!shader_manager.read("../shaders/axes.vertex.glsl", 0, "../shaders/axes.fragment.glsl"))
        return false;
    shader_manager.compile();
    shader_program_id[SHADER_AXES] = glCreateProgram();
    shader_manager.linkProgram(&shader_program_id[SHADER_AXES]);

    if (!shader_manager.read("../shaders/skybox.vertex.glsl", 0, "../shaders/skybox.fragment.glsl"))
        return false;
    shader_manager.compile();
    shader_program_id[SHADER_SKYBOX] = glCreateProgram();
    shader_manager.linkProgram(&shader_program_id[SHADER_SKYBOX]);

    if (!shader_manager.read("../shaders/reflection.vertex.glsl", 0, "../shaders/reflection.fragment.glsl"))
        return false;
    shader_manager.compile();
    shader_program_id[SHADER_REFLECTION] = glCreateProgram();
    shader_manager.linkProgram(&shader_program_id[SHADER_REFLECTION]);

    return true;
}

void
Core::getShadersLocations()
{
    // Must cast, inconsistency between glUniform (use GLint) and glVertexAttribPointer (use GLuint)
    m_mvp_matrix_loc = (GLuint) glGetUniformLocation(shader_program_id[SHADER_MODELS], "mvp_matrix");
    m_camera_pos_loc = (GLuint) glGetUniformLocation(shader_program_id[SHADER_MODELS], "camera_pos");
    m_model_loc = (GLuint) glGetUniformLocation(shader_program_id[SHADER_MODELS], "model_matrix");
    m_texture_loc = (GLuint) glGetUniformLocation(shader_program_id[SHADER_MODELS], "tex");
    m_light_pos_loc = (GLuint) glGetUniformLocation(shader_program_id[SHADER_MODELS], "light_pos");

    ss_texture_loc = (GLuint) glGetUniformLocation(shader_program_id[SHADER_SKYBOX], "tex");

    r_mvp_matrix_loc = (GLuint) glGetUniformLocation(shader_program_id[SHADER_REFLECTION], "mvp_matrix");
    r_frame_texture_loc = (GLuint) glGetUniformLocation(shader_program_id[SHADER_REFLECTION], "frame_tex");
    r_alpha_texture_loc = (GLuint) glGetUniformLocation(shader_program_id[SHADER_REFLECTION], "alpha_tex");
    r_alpha_indice_loc = (GLuint) glGetUniformLocation(shader_program_id[SHADER_REFLECTION], "alpha_indice");
}

void
Core::createBuffers()
{
    glGenFramebuffers(1, fbos);
    glBindFramebuffer(GL_FRAMEBUFFER, fbos[REFLECTION]);
    GLfloat *ptr_axes;

    glGenVertexArrays(VAO_NUM, vaos);

    /// Axes
    glBindVertexArray(vaos[VAO_AXES]);
    glGenBuffers(1, &vbos[VBO_AXES_LINES]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[VBO_AXES_LINES]);
    ptr_axes = createAxesBuffer();
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 216, ptr_axes, GL_STATIC_DRAW);
    free(ptr_axes);
    glEnableVertexAttribArray(position_loc);
    glVertexAttribPointer(position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, nullptr);
    glEnableVertexAttribArray(color_loc);
    glVertexAttribPointer(color_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void *) (3 * sizeof(GLfloat)));


    /// Skybox
    glBindVertexArray(vaos[VAO_SKYBOX]);
    glGenBuffers(2, &vbos[VBO_SKYBOX_TRIANGLES]);
    skybox.generateModel();
    glBindBuffer(GL_ARRAY_BUFFER, vbos[VBO_SKYBOX_TRIANGLES]);
    glBufferData(GL_ARRAY_BUFFER, skybox.model.v_mem_size, skybox.model.v_array, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[VBO_SKYBOX_FACES]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, skybox.model.f_mem_size, skybox.model.f_array, GL_STATIC_DRAW);
    glEnableVertexAttribArray(position_loc);
    glVertexAttribPointer(position_loc, 3, GL_FLOAT, GL_FALSE, 0, 0);


    /// Rubik
    glBindVertexArray(vaos[VAO_RUBIK]);
    glGenBuffers(1, &vbos[VBO_RUBIK_INTERLEAVED]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[VBO_RUBIK_INTERLEAVED]);
    glBufferData(GL_ARRAY_BUFFER, object_cube_rubik->interleaved_fat_data_mem_size,
                 object_cube_rubik->interleaved_fat_data_array, GL_STATIC_DRAW);
    glVertexAttribPointer(position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, nullptr);
    glEnableVertexAttribArray(position_loc);
    glVertexAttribPointer(texture_coordinates_loc, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8,
                          (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(texture_coordinates_loc);
    glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void *) (5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(normal_loc);
    object_cube_rubik->binded_array_buffer_id = VBO_RUBIK_INTERLEAVED;


    /// Cube block
    glBindVertexArray(vaos[VAO_CUBE_BLOCK]);
    glGenBuffers(1, &vbos[VBO_CUBE_BLOCK_INTERLEAVED]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[VBO_CUBE_BLOCK_INTERLEAVED]);
    glBufferData(GL_ARRAY_BUFFER, object_cube_block->interleaved_fat_data_mem_size,
                 object_cube_block->interleaved_fat_data_array,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, nullptr);
    glEnableVertexAttribArray(position_loc);
    glVertexAttribPointer(texture_coordinates_loc, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8,
                          (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(texture_coordinates_loc);
    glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void *) (5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(normal_loc);
    object_cube_block->binded_array_buffer_id = VBO_CUBE_BLOCK_INTERLEAVED;


    /// Low Res Rubik
    glBindVertexArray(vaos[VAO_LOW_POLY_RUBIK]);
    glGenBuffers(1, &vbos[VBO_LOW_POLY_RUBIK_INTERLEAVED]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[VBO_LOW_POLY_RUBIK_INTERLEAVED]);
    glBufferData(GL_ARRAY_BUFFER, object_cube_rubik_low_poly->interleaved_fat_data_mem_size,
                 object_cube_rubik_low_poly->interleaved_fat_data_array, GL_STATIC_DRAW);
    glVertexAttribPointer(position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, nullptr);
    glEnableVertexAttribArray(position_loc);
    glVertexAttribPointer(texture_coordinates_loc, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8,
                          (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(texture_coordinates_loc);
    glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void *) (5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(normal_loc);
    object_cube_rubik_low_poly->binded_array_buffer_id = VBO_LOW_POLY_RUBIK_INTERLEAVED;


    /// Square reflection
    glBindVertexArray(vaos[VAO_SQUARE]);
    glGenBuffers(1, &vbos[VBO_SQUARE_INTERLEAVED]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[VBO_SQUARE_INTERLEAVED]);
    glBufferData(GL_ARRAY_BUFFER, object_square->interleaved_fat_data_mem_size,
                 object_square->interleaved_fat_data_array, GL_STATIC_DRAW);
    glVertexAttribPointer(position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, nullptr);
    glEnableVertexAttribArray(position_loc);
    glVertexAttribPointer(texture_coordinates_loc, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8,
                          (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(texture_coordinates_loc);
    glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void *) (5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(normal_loc);
    object_cube_block->binded_array_buffer_id = VBO_SQUARE_INTERLEAVED;

    object_cube_rubik->freeInterleavedData();
    object_cube_rubik_low_poly->freeInterleavedData();
    object_cube_block->freeInterleavedData();
    object_square->freeInterleavedData();
}

void
Core::loadTextures()
{
    // Can't load texture before creating buffers.
    glGenTextures(TEX_NUM, texture_IDs);

    glActiveTexture(GL_TEXTURE0);
    texture_manager.loadImageFile(texture_IDs[TEX_RUBIK], "../assets/texture/rubik.png");
    glActiveTexture(GL_TEXTURE1);
    texture_manager.loadImageFile(texture_IDs[TEX_LOW_POLY_RUBIK], "../assets/texture/low_res_rubik.png");
    glActiveTexture(GL_TEXTURE2);
    texture_manager.loadImageFile(texture_IDs[TEX_BACKGROUND_BLOCK], "../assets/texture/white_marble.png");
    glActiveTexture(GL_TEXTURE3);
    std::vector<const GLchar *> faces_skybox;
    faces_skybox.push_back("../assets/texture/skybox/sleepyhollow_rt.jpg");
    faces_skybox.push_back("../assets/texture/skybox/sleepyhollow_lf.jpg");
    faces_skybox.push_back("../assets/texture/skybox/sleepyhollow_up.jpg");
    faces_skybox.push_back("../assets/texture/skybox/sleepyhollow_dn.jpg");
    faces_skybox.push_back("../assets/texture/skybox/sleepyhollow_bk.jpg");
    faces_skybox.push_back("../assets/texture/skybox/sleepyhollow_ft.jpg");
    texture_manager.loadCubemap(texture_IDs[TEX_SKYBOX], faces_skybox);

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, texture_IDs[TEX_REFLECTION]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, REFL_TEX_RES, REFL_TEX_RES, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_IDs[TEX_REFLECTION], 0);

    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, texture_IDs[TEX_REFLECTION_DEPTH]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, REFL_TEX_RES, REFL_TEX_RES, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture_IDs[TEX_REFLECTION_DEPTH], 0);

    glActiveTexture(GL_TEXTURE6);
    texture_manager.loadAlphaTexture(texture_IDs[TEX_REFLECTION_ALPHA], "../assets/texture/reflection_alpha.png");
}

void Core::renderAxes()
{
    glUseProgram(shader_program_id[SHADER_AXES]);
    glUniformMatrix4fv((GLuint) glGetUniformLocation(shader_program_id[SHADER_AXES], "mvp_matrix"), 1, GL_FALSE,
                       glm::value_ptr(vp_matrix));

    glBindVertexArray(vaos[VAO_AXES]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[VBO_AXES_LINES]);
    glDrawArrays(GL_LINES, 0, 36);
}

void Core::renderSkybox(glm::mat4 &camera_matrix, glm::mat4 &camera_perspective_matrix)
{
    glm::mat4 untranslated_view_matrix;

    glUseProgram(shader_program_id[SHADER_SKYBOX]);
    glUniform1i(ss_texture_loc, TEX_SKYBOX);
    /// Convert to mat3 and back to mat4 to remove any translation component.
    untranslated_view_matrix = glm::mat4(glm::mat3(camera_matrix));
    vp_matrix = camera_perspective_matrix;
    vp_matrix *= untranslated_view_matrix;
    glUniformMatrix4fv((GLuint) glGetUniformLocation(shader_program_id[SHADER_SKYBOX], "mvp_matrix"), 1, GL_FALSE,
                       glm::value_ptr(vp_matrix));

    glBindVertexArray(vaos[VAO_SKYBOX]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[VBO_SKYBOX_TRIANGLES]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[VBO_SKYBOX_FACES]);
    glDepthMask(GL_FALSE);
    glDrawElements(GL_TRIANGLES, skybox.model.f_num_elem, GL_UNSIGNED_INT, 0);
    glDepthMask(GL_TRUE);
}

void
Core::renderModels()
{
    glUseProgram(shader_program_id[SHADER_MODELS]);
    glUniform3fv(m_camera_pos_loc, 1, glm::value_ptr(camera.pos));
    glUniform3fv(
            m_light_pos_loc,
            1,
            glm::value_ptr(light_pos)
    );

    glBindVertexArray(vaos[VAO_RUBIK]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[VBO_RUBIK_INTERLEAVED]);
    glUniform1i(m_texture_loc, TEX_RUBIK);
    for (int i = 0; i < 27; ++i)
    {
        mvp_matrix = vp_matrix;
        mvp_matrix *= animation.v_model_attrib[i].matrix;
        glUniformMatrix4fv(m_mvp_matrix_loc, 1, GL_FALSE, glm::value_ptr(mvp_matrix));
        glUniformMatrix4fv(m_model_loc, 1, GL_FALSE, glm::value_ptr(animation.v_model_attrib[i].matrix));
        glDrawArrays(GL_TRIANGLES, 0, object_cube_rubik->interleaved_fat_data_num_elem);
    }

    glBindVertexArray(vaos[VAO_CUBE_BLOCK]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[VBO_CUBE_BLOCK_INTERLEAVED]);
    glUniform1i(m_texture_loc, TEX_BACKGROUND_BLOCK);
    for (int j = 27; j < 52; ++j)
    {
        mvp_matrix = vp_matrix;
        mvp_matrix *= animation.v_model_attrib[j].matrix;
        glUniformMatrix4fv(m_mvp_matrix_loc, 1, GL_FALSE, glm::value_ptr(mvp_matrix));
        glUniformMatrix4fv(m_model_loc, 1, GL_FALSE, glm::value_ptr(animation.v_model_attrib[j].matrix));
        glDrawArrays(GL_TRIANGLES, 0, object_cube_block->interleaved_fat_data_num_elem);

    }
}

void Core::renderReflection()
{
    GLenum status;

    renderSkybox(camera.refl_matrix, camera.refl_perspective_matrix);
    glUseProgram(shader_program_id[SHADER_MODELS]);
    glUniform3fv(m_camera_pos_loc, 1, glm::value_ptr(camera.refl_pos));
    glUniform3fv(
            m_light_pos_loc,
            1,
            glm::value_ptr(light_pos)
    );

    vp_matrix = camera.refl_perspective_matrix;
    vp_matrix *= camera.refl_matrix;

    glBindVertexArray(vaos[VAO_LOW_POLY_RUBIK]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[VBO_LOW_POLY_RUBIK_INTERLEAVED]);
    glUniform1i(m_texture_loc, TEX_LOW_POLY_RUBIK);
    for (int i = 0; i < 27; ++i)
    {
        mvp_matrix = vp_matrix;
        mvp_matrix *= animation.v_model_attrib[i].matrix;
        glUniformMatrix4fv(m_mvp_matrix_loc, 1, GL_FALSE, glm::value_ptr(mvp_matrix));
        glUniformMatrix4fv(m_model_loc, 1, GL_FALSE, glm::value_ptr(animation.v_model_attrib[i].matrix));
        glDrawArrays(GL_TRIANGLES, 0, object_cube_rubik_low_poly->interleaved_fat_data_num_elem);
    }
    status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "FB error, status: 0x" << status << std::endl;
    }
}

void Core::renderReflectionSquare()
{
    glUseProgram(shader_program_id[SHADER_REFLECTION]);
    glm::mat4 turn_disque = glm::rotate(animation.v_model_attrib[52].matrix, -camera.center_horizontal_angle,
                                        camera.up);

    mvp_matrix = vp_matrix;
    mvp_matrix *= turn_disque;

    glBindVertexArray(vaos[VAO_SQUARE]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[VBO_SQUARE_INTERLEAVED]);
    glUniform1i(r_frame_texture_loc, TEX_REFLECTION);
    glUniform1i(r_alpha_texture_loc, TEX_REFLECTION_ALPHA);
    glUniform1f(r_alpha_indice_loc, animation.alpha_indice);
    glUniformMatrix4fv(r_mvp_matrix_loc, 1, GL_FALSE, glm::value_ptr(mvp_matrix));
    glDrawArrays(GL_TRIANGLES, 0, object_square->interleaved_fat_data_num_elem);
}

void Core::renderImage()
{
    if (animation.demo_reflection_is_on)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbos[REFLECTION]);
        glViewport(0, 0, REFL_TEX_RES, REFL_TEX_RES);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderReflection();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, res_x, res_y);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderSkybox(camera.matrix, camera.perspective_matrix);
    vp_matrix = camera.perspective_matrix;
    vp_matrix *= camera.matrix;
    if (render_axes_on)
        renderAxes();
    renderModels();
    renderReflectionSquare();
}

GLfloat *Core::createAxesBuffer()
{
    GLfloat axes_rgb_vertex_and_color[216] = {
            //Red +
            0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            100.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,

            0.0f, 0.01f, 0.0f,
            1.0f, 0.0f, 0.0f,
            100.0f, 0.01f, 0.0f,
            1.0f, 0.0f, 0.0f,

            0.0f, -0.01f, 0.0f,
            1.0f, 0.0f, 0.0f,
            100.0f, -0.01f, 0.0f,
            1.0f, 0.0f, 0.0f,

            0.0f, 0.0f, 0.01f,
            1.0f, 0.0f, 0.0f,
            100.0f, 0.0f, 0.1f,
            1.0f, 0.0f, 0.0f,

            0.0f, 0.0f, -0.01f,
            1.0f, 0.0f, 0.0f,
            100.0f, 0.0f, -0.1f,
            1.0f, 0.0f, 0.0f,

            //Green +
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 100.0f, 0.0f,
            0.0f, 1.0f, 0.0f,

            0.01f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.01f, 100.0f, 0.0f,
            0.0f, 1.0f, 0.0f,

            -0.01f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            -0.01f, 100.0f, 0.0f,
            0.0f, 1.0f, 0.0f,

            0.0f, 0.0f, 0.01f,
            0.0f, 1.0f, 0.0f,
            0.0f, 100.0f, 0.01f,
            0.0f, 1.0f, 0.0f,

            0.0f, 0.0f, -0.01f,
            0.0f, 1.0f, 0.0f,
            0.0f, 100.0f, -0.01f,
            0.0f, 1.0f, 0.0f,

            //Blue +
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 100.0f,
            0.0f, 0.0f, 1.0f,

            0.01f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.01f, 0.0f, 100.0f,
            0.0f, 0.0f, 1.0f,

            -0.01f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            -0.01f, 0.0f, 100.0f,
            0.0f, 0.0f, 1.0f,

            0.0f, 0.01f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.01f, 100.0f,
            0.0f, 0.0f, 1.0f,

            0.0f, -0.01f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, -0.01f, 100.0f,
            0.0f, 0.0f, 1.0f,

            // Red -
            0.0f, 0.0f, 0.0f,
            0.7f, 0.0f, 0.0f,
            -100.0f, 0.0f, 0.0f,
            0.7f, 0.0f, 0.0f,

            // Green -
            0.0f, 0.0f, 0.0f,
            0.0f, 0.7f, 0.0f,
            0.0f, -100.0f, 0.0f,
            0.0f, 0.7f, 0.0f,

            // Blue -
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.7f,
            0.0f, 0.0f, -100.0f,
            0.0f, 0.0f, 0.7f,
    };
    GLfloat *pouet = new GLfloat[216];
    for (int i = 0; i < 216; ++i)
        pouet[i] = axes_rgb_vertex_and_color[i];
    return pouet;
}

void Core::loadSequences()
{
    std::string line;
    std::ifstream r_s_cfg("../config/rubik_shuffles.cfg");
    int i = 0;

    if (r_s_cfg.is_open())
    {
        while (getline(r_s_cfg, line) && i <= 10)
        {
            raw_play_list_sequence.push_back(line);
            i++;
        }
        while (i <= 10)
        {
            raw_play_list_sequence.push_back("");
            i++;
        }
        r_s_cfg.close();
    }
    else
    {
        std::cerr << "Failed to load Rubik Shuffles config." << std::endl;
    }
}

void Core::addRandomMoves(int amount)
{
    int move_id = -1;
    std::string move_string;
    srand((unsigned int) glfwGetTime());

    for (int i = 0; i < amount; ++i)
    {
        move_id = rand() % 18;
        createPlayList(resolver.id_2_move_text_array[move_id]);
    }
}

void Core::createPlayList(std::string raw_instructions)
{
    std::istringstream iss(raw_instructions);
    std::vector<std::string> instructions{std::istream_iterator<std::string>{iss},
                                          std::istream_iterator<std::string>{}};

    for (auto &instruction: instructions)
    {
//        std::cerr << instruction << std::endl;
        if (instruction == "U")
        {
            anim_queue.push({&Animation::applyRubikCube_U});
            resolv_queue.push(0);
        }
        else if (instruction == "U2")
        {
            anim_queue.push({&Animation::applyRubikCube_U2});
            resolv_queue.push(1);
        }
        else if (instruction == "U'")
        {
            anim_queue.push({&Animation::applyRubikCube_Uprime});
            resolv_queue.push(2);
        }
        else if (instruction == "D")
        {
            anim_queue.push({&Animation::applyRubikCube_D});
            resolv_queue.push(3);
        }
        else if (instruction == "D2")
        {
            anim_queue.push({&Animation::applyRubikCube_D2});
            resolv_queue.push(4);
        }
        else if (instruction == "D'")
        {
            anim_queue.push({&Animation::applyRubikCube_Dprime});
            resolv_queue.push(5);
        }
        else if (instruction == "R")
        {
            anim_queue.push({&Animation::applyRubikCube_R});
            resolv_queue.push(6);
        }
        else if (instruction == "R2")
        {
            anim_queue.push({&Animation::applyRubikCube_R2});
            resolv_queue.push(7);
        }
        else if (instruction == "R'")
        {
            anim_queue.push({&Animation::applyRubikCube_Rprime});
            resolv_queue.push(8);
        }
        else if (instruction == "L")
        {
            anim_queue.push({&Animation::applyRubikCube_L});
            resolv_queue.push(9);
        }
        else if (instruction == "L2")
        {
            anim_queue.push({&Animation::applyRubikCube_L2});
            resolv_queue.push(10);
        }
        else if (instruction == "L'")
        {
            anim_queue.push({&Animation::applyRubikCube_Lprime});
            resolv_queue.push(11);
        }
        else if (instruction == "F")
        {
            anim_queue.push({&Animation::applyRubikCube_F});
            resolv_queue.push(12);
        }
        else if (instruction == "F2")
        {
            anim_queue.push({&Animation::applyRubikCube_F2});
            resolv_queue.push(13);
        }
        else if (instruction == "F'")
        {
            anim_queue.push({&Animation::applyRubikCube_Fprime});
            resolv_queue.push(14);
        }
        else if (instruction == "B")
        {
            anim_queue.push({&Animation::applyRubikCube_B});
            resolv_queue.push(15);
        }
        else if (instruction == "B2")
        {
            anim_queue.push({&Animation::applyRubikCube_B2});
            resolv_queue.push(16);
        }
        else if (instruction == "B'")
        {
            anim_queue.push({&Animation::applyRubikCube_Bprime});
            resolv_queue.push(17);
        }
        else
            std::cerr << " WUT?" << std::endl;
    }
}

void Core::runPlayList()
{
    if (anim_queue.size() != 0)
    {
        if (anim_delayer)
        {
            (animation.*anim_queue.front())();
            resolver.applyFromID(resolv_queue.front(), resolver.current_state, resolver.current_state);
            resolv_queue.pop();
            anim_queue.pop();
            anim_delayer = false;
        }
        if (!animation.isAnyAnimationOn())
        {
            anim_delayer = true;
        }
        if (resolver.play_list_will_resolve)
        {
            resolver.play_list_will_resolve = false;
        }
    }
    else
    {
        std::cerr << "Playlist is empty." << std::endl;
        anim_queue_is_running = false;
    }
}

void Core::resolveRubik()
{
    if (resolv_queue.size() == 0)
    {
        std::string str = resolver.solveState();
        createPlayList(str);
        // string_free(str);
        std::cout << "Solution Found:" << std::endl;
        std::cout << resolver.result << std::endl;
    }
    std::cout << "Playlist is not empty. Press [return] to launch it." << std::endl;
}

/// TODO put resolver on a thread.
/*
HPP
 # include <mutex>
# include <thread>

    std::thread     *th = NULL;

CPP
		if (th == NULL)
			th = new std::thread(&Core::resolve, this);
        solv_stage = ANIM;
    }
    if (solv_stage == ANIM)
	{
        solv_stage = animator.solvAnimation();
    }
    if (solv_stage == FINALIZE)
	{
        if (board.swap_queue_status == FILLING)
		{
            solv_stage = INITIATE;
        }
		else if (board.swap_queue_status == READY)
		{
            th->join();
            delete th;
            th = NULL;
            resetLight();
            solv_stage = OFF;
            move_stage = INITIATE;
        }
		else if (board.swap_queue_status == UNSOLVABLE)
		{
            th->join();
            delete th;
            th = NULL;
            resetLight();
            solv_stage = OFF;
            unsolv_stage = INITIATE;
        }
		else
        {
            solv_stage = OFF;
        }
    }


    void
Core::resolve(void)
{
    double      start_time = 0.0f;
    double      end_time = 0.0f;

    start_time = glfwGetTime();
    board.swap_queue_status = FILLING;
    algo.setBoard(&board);
    algo.setHeuristic(heuristic);
    algo.resolve();
    end_time = glfwGetTime();
    time_to_solve = end_time - start_time;
}
*/
