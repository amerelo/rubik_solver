//
// Created by Hugo JEANNIN on 5/23/17.
//

#include "../inc/Animation.hpp"

Animation::Animation()
{
    std::cerr << "Animation() constructor called." << std::endl;
}

Animation::~Animation()
{
    std::cerr << "Animation() destructor called." << std::endl;
}

void Animation::init(Resolver *resolver)
{
    using namespace glm;

    this->resolver = resolver;
    rotation_speed_indice = 2.0f;
//    rotation_speed_indice = 10.0f;
    rotation_speed = rotation_speed_indice / TPS;
    rotation_amount = 0.0f;
    rotation_goal = 0.0f;
    rotation_axis = AXIS_X;
    global_rotation = glm::mat4(1.0f);

    // Rubix Cube setup. ID to position.
    id_2_pos.emplace( 0, translate(mat4(1.0f), vec3(-1.0f, -1.0f, -1.0f)));
    id_2_pos.emplace( 1, translate(mat4(1.0f), vec3( 0.0f, -1.0f, -1.0f)));
    id_2_pos.emplace( 2, translate(mat4(1.0f), vec3( 1.0f, -1.0f, -1.0f)));
    id_2_pos.emplace( 3, translate(mat4(1.0f), vec3(-1.0f,  0.0f, -1.0f)));
    id_2_pos.emplace( 4, translate(mat4(1.0f), vec3( 0.0f,  0.0f, -1.0f)));
    id_2_pos.emplace( 5, translate(mat4(1.0f), vec3( 1.0f,  0.0f, -1.0f)));
    id_2_pos.emplace( 6, translate(mat4(1.0f), vec3(-1.0f,  1.0f, -1.0f)));
    id_2_pos.emplace( 7, translate(mat4(1.0f), vec3( 0.0f,  1.0f, -1.0f)));
    id_2_pos.emplace( 8, translate(mat4(1.0f), vec3( 1.0f,  1.0f, -1.0f)));
    id_2_pos.emplace( 9, translate(mat4(1.0f), vec3(-1.0f, -1.0f,  0.0f)));
    id_2_pos.emplace(10, translate(mat4(1.0f), vec3( 0.0f, -1.0f,  0.0f)));
    id_2_pos.emplace(11, translate(mat4(1.0f), vec3( 1.0f, -1.0f,  0.0f)));
    id_2_pos.emplace(12, translate(mat4(1.0f), vec3(-1.0f,  0.0f,  0.0f)));
    id_2_pos.emplace(13, translate(mat4(1.0f), vec3( 0.0f,  0.0f,  0.0f)));
    id_2_pos.emplace(14, translate(mat4(1.0f), vec3( 1.0f,  0.0f,  0.0f)));
    id_2_pos.emplace(15, translate(mat4(1.0f), vec3(-1.0f,  1.0f,  0.0f)));
    id_2_pos.emplace(16, translate(mat4(1.0f), vec3( 0.0f,  1.0f,  0.0f)));
    id_2_pos.emplace(17, translate(mat4(1.0f), vec3( 1.0f,  1.0f,  0.0f)));
    id_2_pos.emplace(18, translate(mat4(1.0f), vec3(-1.0f, -1.0f,  1.0f)));
    id_2_pos.emplace(19, translate(mat4(1.0f), vec3( 0.0f, -1.0f,  1.0f)));
    id_2_pos.emplace(20, translate(mat4(1.0f), vec3( 1.0f, -1.0f,  1.0f)));
    id_2_pos.emplace(21, translate(mat4(1.0f), vec3(-1.0f,  0.0f,  1.0f)));
    id_2_pos.emplace(22, translate(mat4(1.0f), vec3( 0.0f,  0.0f,  1.0f)));
    id_2_pos.emplace(23, translate(mat4(1.0f), vec3( 1.0f,  0.0f,  1.0f)));
    id_2_pos.emplace(24, translate(mat4(1.0f), vec3(-1.0f,  1.0f,  1.0f)));
    id_2_pos.emplace(25, translate(mat4(1.0f), vec3( 0.0f,  1.0f,  1.0f)));
    id_2_pos.emplace(26, translate(mat4(1.0f), vec3( 1.0f,  1.0f,  1.0f)));

    loadRubikCube();
    if (DEMO_ON_STARTUP)
    {
        applyRubikCubeCreation();
        alpha_indice = 0.0f;
    }

}

void Animation::loadRubikCube()
{
    clearEverything();
    sceneRubikCube();
    animRubikCubeCreation();
    animRubikCubeRotations();
    animDecorativeCubeCreation();

    initRubikCube();
}

void
Animation::buildCustomModelAttrib(int amount, std::string name, int model_id, GLuint texture_id, glm::mat4 init_matrix)
{
    int iter = 0;
    while (iter < amount)
    {
        v_model_attrib.push_back({
                                         true,
                                         false,
                                         -1,
                                         -1,
                                         name,
                                         model_id,
                                         texture_id,
                                         init_matrix,
                                         init_matrix,
                                         glm::mat4(1.0f),
                                         glm::mat4(1.0f),
                                         glm::mat4(1.0f),
                                         glm::mat4(1.0f),
                                         glm::mat4(1.0f)
                                 });
        iter++;
    }
}

void Animation::addEmptyTS(int amount)
{
    int iter = 0;
    while (iter < amount)
    {
        v_transf_serie.push_back({
                                         false,
                                         0.0f,
                                         0.0f,
                                         0.0f,
                                         0.0f
                                 });
        iter++;
    }
}

void Animation::createNewTransformation(double duration, int type, glm::mat4 matrix, std::string name)
{
    t_transf *pouet = new t_transf;

    pouet->duration = duration;
    pouet->type = type;
    pouet->matrix = matrix;
    pouet->name = name;

    origin_transf_ptr.push_back(pouet);
}

void Animation::buildTS(t_transf_serie *transf_serie, int size, ...)
{
    /// truc du futur qui te prend des argument a l' infini.
    va_list args;
    va_start(args, size);
    for (int iter_args = 0; iter_args < size; ++iter_args)
        transf_serie->serie.push_back(origin_transf_ptr[va_arg(args, int)]);
    va_end(args);
}

void Animation::setTSIndividualStartTimings(t_transf_serie *transf_serie, int size, ...)
{
    /// truc du futur qui te prend des argument a l' infini.
    va_list args;
    va_start(args, size);
    for (int iter_args = 0; iter_args < size; ++iter_args)
        transf_serie->start_timing.push_back(va_arg(args, double));
    va_end(args);
}

void Animation::linkTS(t_transf_serie *transf_serie, t_model_attrib *model_attrib)
{
    transf_serie->models.push_back(model_attrib);
}

void Animation::linkTS(int TS_ID, int ma_ID)
{
    v_transf_serie[TS_ID].models.push_back(&v_model_attrib[ma_ID]);
}

void Animation::setTSGlobalDuration(t_transf_serie *transf_serie, double end_time, double delay)
{
    transf_serie->serie_start_timer = delay;
    transf_serie->serie_end_timer = end_time;
}

void Animation::applyEndFormation(t_transf_serie &transf_serie)
{
    for (auto &model : transf_serie.models)
    {
        model->init_mat = model->end_formation;
        model->matrix = model->init_mat;
        model->pos_id = model->end_pos_id;
    }
}

void Animation::activateEnsemble(std::vector<t_transf_serie *> &ensemble)
{
    double current_time = glfwGetTime();
    for (auto &ts : ensemble)
    {
        ts->is_active = true;
        ts->serie_start_time = current_time + ts->serie_start_timer;
        ts->serie_end_time = ts->serie_start_time + ts->serie_end_timer - (0.0166667f * 1);
        if (ts->serie_end_time > last_anim_timing)
            last_anim_timing = ts->serie_end_time + (0.0166667f * 1) ;
    }
}

void Animation::stopAllAnimation()
{
    /// Stop everything
    for (auto &iter_v_ma : v_model_attrib)
    {
        iter_v_ma.trans_mat = glm::mat4(1.0f);
        iter_v_ma.rot_mat = glm::mat4(1.0f);
        iter_v_ma.scale_mat = glm::mat4(1.0f);
        iter_v_ma.matrix = iter_v_ma.init_mat;
    }
    for (auto &iter_v_ts : v_transf_serie)
    {
        iter_v_ts.is_active = false;
        iter_v_ts.serie_start_time = 0.0f;
        iter_v_ts.serie_end_time = 0.0f;
    }
}

void Animation::stopSerie(t_transf_serie &transf_serie)
{
    transf_serie.is_active = false;
    transf_serie.serie_start_time = 0.0f; /// more security than anything
    transf_serie.serie_end_time = 0.0f;
    for (auto &tsm : transf_serie.models)
    {
        tsm->trans_mat = glm::mat4(1.0f);
        tsm->rot_mat = glm::mat4(1.0f);
        tsm->scale_mat = glm::mat4(1.0f);
        tsm->matrix = tsm->init_mat;
    }
}

void Animation::clearTSsModels(int start, int end)
{
    for (int iter_ts = start; iter_ts <= end; ++iter_ts)
        v_transf_serie[iter_ts].models.clear();
}

void Animation::update()
{
    if (iter_alpha_indice)
    {
        alpha_indice += 0.01f;
        if (alpha_indice >= 0.8f)
            iter_alpha_indice = false;
    }
    updateGlobalRotation();

    /// Apply init_matrix even if not active.
    for (auto &model : v_model_attrib)
    {
        model.matrix = glm::mat4(1.0f);
        if (model.should_rotate)
            model.matrix *= global_rotation;
        model.matrix *= model.init_mat;
    }

    /// Triggers.
    for (auto &trigger : triggers)
    {
        if (trigger.active)
        {
            if (glfwGetTime() >= trigger.timing)
            {
                *trigger.to_switch = !*trigger.to_switch;
                trigger.active = false;
            }
        }
    }

    if (ANIMATION_VERBOSE)
        std::cerr << "{ ";

    for (auto &iter_ts : v_transf_serie)
    {
        if (iter_ts.is_active)
        {
            /// If current time is in range.
            if (glfwGetTime() >= iter_ts.serie_start_time &&
                glfwGetTime() < iter_ts.serie_end_time)
            {
                for (int iter_t = 0; iter_t < iter_ts.serie.size(); ++iter_t)
                {
                    /// If transf should start.
                    if (glfwGetTime() >=
                        iter_ts.serie_start_time +
                        iter_ts.start_timing[iter_t]
                        && glfwGetTime() <
                           iter_ts.serie_start_time +
                           iter_ts.start_timing[iter_t] +
                           iter_ts.serie[iter_t]->duration)
                    {
                        if (ANIMATION_VERBOSE)
                        {
                            std::cerr << "TIME: " << iter_ts.serie_start_time +
                                                     iter_ts.start_timing[iter_t] +
                                                     iter_ts.serie[iter_t]->duration
                                      << " > " << glfwGetTime() << " > " <<
                                      iter_ts.serie_start_time +
                                      iter_ts.start_timing[iter_t] << " ";
                        }
                        for (int iter_m = 0; iter_m < iter_ts.models.size(); ++iter_m)
                        {
                            if (iter_ts.serie[iter_t]->type == TRANS)
                                iter_ts.models[iter_m]->trans_mat *= iter_ts.serie[iter_t]->matrix;
                            if (iter_ts.serie[iter_t]->type == ROT)
                                iter_ts.models[iter_m]->rot_mat *= iter_ts.serie[iter_t]->matrix;
                            if (iter_ts.serie[iter_t]->type == SCALE)
                                iter_ts.models[iter_m]->scale_mat *= iter_ts.serie[iter_t]->matrix;
                        }
                    }
                    for (auto &model : iter_ts.models)
                    {
                        if (ANIMATION_VERBOSE)
                            std::cerr << "[" << model->name << " -> " << iter_ts.serie[iter_t]->name << "] ";
                        /// combine transformation
                        model->matrix = glm::mat4(1.0f);
                        if (model->should_rotate)
                            model->matrix *= global_rotation;
                        model->matrix *= model->init_mat;
                        model->matrix *= model->trans_mat;
                        model->matrix *= model->rot_mat;
                        model->matrix *= model->scale_mat;
                    }
                }
            }
            if (glfwGetTime() >= iter_ts.serie_end_time)
            {
                stopSerie(iter_ts);
                applyEndFormation(iter_ts);
            }
        }
    }
    if (ANIMATION_VERBOSE)
        std::cerr << "}" << std::endl;
}

void Animation::updateGlobalRotation()
{
    if (rotation_amount < rotation_goal)
        rotation_amount += rotation_speed;
    if (rotation_amount >= rotation_goal)
    {
        rotation_amount = 0.0f;
        for (auto &v_m_a: v_model_attrib)
        {
            v_m_a.should_rotate = false;
        }
    }
    glm::vec3 axis;
    if (rotation_axis == AXIS_X)
        axis = glm::vec3(1.0f, 0.0f, 0.0f);
    else if (rotation_axis == AXIS_Y)
        axis = glm::vec3(0.0f, 1.0f, 0.0f);
    else if (rotation_axis == AXIS_Z)
        axis = glm::vec3(0.0f, 0.0f, 1.0f);
    else if (rotation_axis == AXIS_R_X)
        axis = glm::vec3(-1.0f, 0.0f, 0.0f);
    else if (rotation_axis == AXIS_R_Y)
        axis = glm::vec3(0.0f, -1.0f, 0.0f);
    else if (rotation_axis == AXIS_R_Z)
        axis = glm::vec3(0.0f, 0.0f, -1.0f);
    else
        std::cerr << "Wrong Axis for global rotation." << std::endl;

    global_rotation = glm::rotate(glm::mat4(1.0f), rotation_amount, axis);
}

bool Animation::isAnyAnimationOn()
{
    if (glfwGetTime() > last_anim_timing + (0.0166667f * 5))
        return false;
    return true;
}

void Animation::changeRotationSpeed()
{
    if (rotation_speed_indice == 2.0f)
    {
        rotation_speed_indice = 10.0f;
    }
    else
    {
        rotation_speed_indice = 2.0f;
    }
    rotation_speed = rotation_speed_indice / TPS;

    quarter_rotation_duration = ((float) M_PI_2) / rotation_speed_indice;
    half_rotation_duration = ((float) M_PI) / rotation_speed_indice;

    /// Not realy optimal but works.
    /// Quarter Rotation
    v_transf_serie[27].start_timing.pop_back();
    v_transf_serie[27].start_timing.pop_back();
    v_transf_serie[27].start_timing.push_back(0.0f);
    v_transf_serie[27].start_timing.push_back(quarter_rotation_duration - 18.0f / TPS);
    setTSGlobalDuration(&v_transf_serie[27], quarter_rotation_duration, 0.0f); // delay for smooth transitions

    /// Half Rotation
    v_transf_serie[28].start_timing.pop_back();
    v_transf_serie[28].start_timing.pop_back();
    v_transf_serie[28].start_timing.push_back(0.0f);
    v_transf_serie[28].start_timing.push_back(half_rotation_duration - 18.0f / TPS);
    setTSGlobalDuration(&v_transf_serie[28], half_rotation_duration, 0.0f); // delay for smooth transitions
}

void Animation::clearEverything()
{
    stopAllAnimation();
    origin_transf_ptr.clear();
    v_transf_serie.clear();
    v_model_attrib.clear();
}

void Animation::sceneRubikCube()
{
    using namespace glm;

    buildCustomModelAttrib(1, "rubik_cube_00", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(-1.0f, -1.0f, -1.0f)));
    buildCustomModelAttrib(1, "rubik_cube_01", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(0.0f, -1.0f, -1.0f)));
    buildCustomModelAttrib(1, "rubik_cube_02", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(1.0f, -1.0f, -1.0f)));
    buildCustomModelAttrib(1, "rubik_cube_03", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(-1.0f, 0.0f, -1.0f)));
    buildCustomModelAttrib(1, "rubik_cube_04", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(0.0f, 0.0f, -1.0f)));
    buildCustomModelAttrib(1, "rubik_cube_05", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(1.0f, 0.0f, -1.0f)));
    buildCustomModelAttrib(1, "rubik_cube_06", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(-1.0f, 1.0f, -1.0f)));
    buildCustomModelAttrib(1, "rubik_cube_07", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(0.0f, 1.0f, -1.0f)));
    buildCustomModelAttrib(1, "rubik_cube_08", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(1.0f, 1.0f, -1.0f)));
    buildCustomModelAttrib(1, "rubik_cube_09", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(-1.0f, -1.0f, 0.0f)));
    buildCustomModelAttrib(1, "rubik_cube_10", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(0.0f, -1.0f, 0.0f)));
    buildCustomModelAttrib(1, "rubik_cube_11", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(1.0f, -1.0f, 0.0f)));
    buildCustomModelAttrib(1, "rubik_cube_12", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(-1.0f, 0.0f, 0.0f)));
    buildCustomModelAttrib(1, "rubik_cube_13", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f)));
    buildCustomModelAttrib(1, "rubik_cube_14", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(1.0f, 0.0f, 0.0f)));
    buildCustomModelAttrib(1, "rubik_cube_15", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(-1.0f, 1.0f, 0.0f)));
    buildCustomModelAttrib(1, "rubik_cube_16", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(0.0f, 1.0f, 0.0f)));
    buildCustomModelAttrib(1, "rubik_cube_17", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(1.0f, 1.0f, 0.0f)));
    buildCustomModelAttrib(1, "rubik_cube_18", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(-1.0f, -1.0f, 1.0f)));
    buildCustomModelAttrib(1, "rubik_cube_19", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(0.0f, -1.0f, 1.0f)));
    buildCustomModelAttrib(1, "rubik_cube_20", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(1.0f, -1.0f, 1.0f)));
    buildCustomModelAttrib(1, "rubik_cube_21", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(-1.0f, 0.0f, 1.0f)));
    buildCustomModelAttrib(1, "rubik_cube_22", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(0.0f, 0.0f, 1.0f)));
    buildCustomModelAttrib(1, "rubik_cube_23", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(1.0f, 0.0f, 1.0f)));
    buildCustomModelAttrib(1, "rubik_cube_24", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(-1.0f, 1.0f, 1.0f)));
    buildCustomModelAttrib(1, "rubik_cube_25", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(0.0f, 1.0f, 1.0f)));
    buildCustomModelAttrib(1, "rubik_cube_26", CUBE_RUBIK, TEX_RUBIK, translate(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f)));

    buildCustomModelAttrib(1, "decorative_cube_27", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(0.0f, -8.0f, 0.0f)));

    buildCustomModelAttrib(1, "decorative_cube_28", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(20.0f, -8.0f, 0.0f)));
    buildCustomModelAttrib(1, "decorative_cube_29", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(20.0f, -8.0f, 20.0f)));
    buildCustomModelAttrib(1, "decorative_cube_30", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(0.0f, -8.0f, 20.0f)));
    buildCustomModelAttrib(1, "decorative_cube_31", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(-20.0f, -8.0f, 20.0f)));
    buildCustomModelAttrib(1, "decorative_cube_32", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(-20.0f, -8.0f, 0.0f)));
    buildCustomModelAttrib(1, "decorative_cube_33", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(-20.0f, -8.0f, -20.0f)));
    buildCustomModelAttrib(1, "decorative_cube_34", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(0.0f, -8.0f, -20.0f)));
    buildCustomModelAttrib(1, "decorative_cube_35", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(20.0f, -8.0f, -20.0f)));

    buildCustomModelAttrib(1, "decorative_cube_36", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(40.0f, -8.0f, -20.0f)));
    buildCustomModelAttrib(1, "decorative_cube_37", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(40.0f, -8.0f, -0.0f)));
    buildCustomModelAttrib(1, "decorative_cube_38", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(40.0f, -8.0f, 20.0f)));
    buildCustomModelAttrib(1, "decorative_cube_39", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(40.0f, -8.0f, 40.0f)));
    buildCustomModelAttrib(1, "decorative_cube_40", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(20.0f, -8.0f, 40.0f)));
    buildCustomModelAttrib(1, "decorative_cube_41", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(0.0f, -8.0f, 40.0f)));
    buildCustomModelAttrib(1, "decorative_cube_42", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(-20.0f, -8.0f, 40.0f)));
    buildCustomModelAttrib(1, "decorative_cube_43", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(-40.0f, -8.0f, 40.0f)));
    buildCustomModelAttrib(1, "decorative_cube_44", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(-40.0f, -8.0f, 20.0f)));
    buildCustomModelAttrib(1, "decorative_cube_45", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(-40.0f, -8.0f, -0.0f)));
    buildCustomModelAttrib(1, "decorative_cube_46", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(-40.0f, -8.0f, -20.0f)));
    buildCustomModelAttrib(1, "decorative_cube_47", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(-40.0f, -8.0f, -40.0f)));
    buildCustomModelAttrib(1, "decorative_cube_48", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(-20.0f, -8.0f, -40.0f)));
    buildCustomModelAttrib(1, "decorative_cube_49", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(20.0f, -8.0f, -40.0f)));
    buildCustomModelAttrib(1, "decorative_cube_50", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(0.0f, -8.0f, -40.0f)));
    buildCustomModelAttrib(1, "decorative_cube_51", CUBE_BLOCK, TEX_BACKGROUND_BLOCK, translate(mat4(1.0f), vec3(40.0f, -8.0f, -40.0f)));

    buildCustomModelAttrib(1, "reflection_square_52", SQUARE_REFL, TEX_REFLECTION, translate(mat4(1.0f), vec3(0.0f, -2.5f, 0.0f)));

    for (int i = 27; i < 36; i++)
    {
        v_model_attrib[i].init_mat *= scale(mat4(1.0f), vec3(20.0f, 1.0f, 20.0f));
    }
    for (int i = 36; i < 52; i++)
    {
        v_model_attrib[i].init_mat *= scale(mat4(1.0f), vec3(20.0f, 1.0f, 20.0f));
    }
    v_model_attrib[52].init_mat *= scale(mat4(1.0f), vec3(22.0f, 0.0f, 22.0f));
}

void Animation::animRubikCubeCreation()
{
    using namespace glm;

#define P0  0.0f + 3.0f
#define P1  1.0f + 3.0f
#define P2  1.6f + 3.0f
#define P3  2.2f + 3.0f
#define P4  2.6f + 3.0f
#define P5  3.0f + 3.0f
#define P6  3.2f + 3.0f
#define P7  3.4f + 3.0f
#define P8  3.5f + 3.0f
#define P9  4.0f + 3.0f
#define E1  5.0f + 3.0f
#define E2  5.1f + 3.0f
#define E3  5.2f + 3.0f
#define E4  5.3f + 3.0f
#define E5  5.4f + 3.0f
#define E6  5.5f + 3.0f
#define E7  5.6f + 3.0f
#define E8  5.7f + 3.0f
#define E9  5.8f + 3.0f

    /// trigger to stop
    if (DEMO_ON_STARTUP)
    {
        triggers.push_back({true, 12.0f, &camera_demo_is_on});
        triggers.push_back({true, 12.0f + 3.0f, &demo_reflection_is_on});
        triggers.push_back({true, 15.0f + 3.0f, &iter_alpha_indice});
    }

    addEmptyTS(3 * 9);

    createNewTransformation(0.24f, TRANS, translate(mat4(1.0f), vec3(5.0f / TPS, 0.0f, 0.0f)), "0_move_right");//  0 R
    createNewTransformation(0.24f, TRANS, translate(mat4(1.0f), vec3(-5.0f / TPS, 0.0f, 0.0f)), "1_move_left");//  1 L
    createNewTransformation(0.24f, TRANS, translate(mat4(1.0f), vec3(0.0f, 5.0f / TPS, 0.0f)), "2_move_up");//     2 U
    createNewTransformation(0.24f, TRANS, translate(mat4(1.0f), vec3(0.0f, -5.0f / TPS, 0.0f)), "3_move_down");//  3 D
    createNewTransformation(0.24f, TRANS, translate(mat4(1.0f), vec3(0.0f, 0.0f, -5.0f / TPS)), "5_move_front");// 5 F
    createNewTransformation(0.24f, TRANS, translate(mat4(1.0f), vec3(0.0f, 0.0f, 5.0f / TPS)), "4_move_back");//   4 B
    createNewTransformation(1.0f, SCALE, scale(mat4(1.0f), vec3(1.01, 1.01, 1.01)), "6_grow");//              6
    createNewTransformation(0.1f, SCALE, scale(mat4(1.0f), vec3(0.9, 0.9, 0.9)), "7_reduce");//            7
/// TAKE CARE 4 and 5 are reverse in order to fit the animation!!


    buildTS(&v_transf_serie[17], 2, 0, 2);
    setTSIndividualStartTimings(&v_transf_serie[17], 2, P0, P7);
    buildTS(&v_transf_serie[15], 2, 1, 2);
    setTSIndividualStartTimings(&v_transf_serie[15], 2, P0, P7);
    buildTS(&v_transf_serie[16], 1, 2);
    setTSIndividualStartTimings(&v_transf_serie[16], 1, P7);

    buildTS(&v_transf_serie[8], 3, 0, 2, 4);
    setTSIndividualStartTimings(&v_transf_serie[8], 3, P0, P8, P8);
    buildTS(&v_transf_serie[6], 3, 1, 2, 4);
    setTSIndividualStartTimings(&v_transf_serie[6], 3, P0, P8, P8);
    buildTS(&v_transf_serie[7], 2, 2, 4);
    setTSIndividualStartTimings(&v_transf_serie[7], 2, P8, P8);

    buildTS(&v_transf_serie[20], 3, 0, 3, 5);
    setTSIndividualStartTimings(&v_transf_serie[20], 3, P0, P4, P4);
    buildTS(&v_transf_serie[18], 3, 1, 3, 5);
    setTSIndividualStartTimings(&v_transf_serie[18], 3, P0, P4, P4);
    buildTS(&v_transf_serie[19], 2, 3, 5);
    setTSIndividualStartTimings(&v_transf_serie[19], 2, P4, P4);

    buildTS(&v_transf_serie[23], 2, 0, 5);
    setTSIndividualStartTimings(&v_transf_serie[23], 2, P0, P5);
    buildTS(&v_transf_serie[21], 2, 1, 5);
    setTSIndividualStartTimings(&v_transf_serie[21], 2, P0, P5);
    buildTS(&v_transf_serie[22], 1, 5);
    setTSIndividualStartTimings(&v_transf_serie[22], 1, P5);

    buildTS(&v_transf_serie[26], 3, 0, 2, 5);
    setTSIndividualStartTimings(&v_transf_serie[26], 3, P0, P6, P6);
    buildTS(&v_transf_serie[24], 3, 1, 2, 5);
    setTSIndividualStartTimings(&v_transf_serie[24], 3, P0, P6, P6);
    buildTS(&v_transf_serie[25], 2, 2, 5);
    setTSIndividualStartTimings(&v_transf_serie[25], 2, P6, P6);

    buildTS(&v_transf_serie[14], 1, 0);
    setTSIndividualStartTimings(&v_transf_serie[14], 1, P0);
    buildTS(&v_transf_serie[12], 1, 1);
    setTSIndividualStartTimings(&v_transf_serie[12], 1, P0);
    buildTS(&v_transf_serie[13], 0);
    setTSIndividualStartTimings(&v_transf_serie[13], 0);

    buildTS(&v_transf_serie[5], 2, 0, 4);
    setTSIndividualStartTimings(&v_transf_serie[5], 2, P0, P1);
    buildTS(&v_transf_serie[3], 2, 1, 4);
    setTSIndividualStartTimings(&v_transf_serie[3], 2, P0, P1);
    buildTS(&v_transf_serie[4], 1, 4);
    setTSIndividualStartTimings(&v_transf_serie[4], 1, P1);

    buildTS(&v_transf_serie[2], 3, 0, 4, 3);
    setTSIndividualStartTimings(&v_transf_serie[2], 3, P0, P2, P2);
    buildTS(&v_transf_serie[0], 3, 1, 4, 3);
    setTSIndividualStartTimings(&v_transf_serie[0], 3, P0, P2, P2);
    buildTS(&v_transf_serie[1], 2, 4, 3);
    setTSIndividualStartTimings(&v_transf_serie[1], 2, P2, P2);

    buildTS(&v_transf_serie[11], 2, 0, 3);
    setTSIndividualStartTimings(&v_transf_serie[11], 2, P0, P3);
    buildTS(&v_transf_serie[9], 2, 1, 3);
    setTSIndividualStartTimings(&v_transf_serie[9], 2, P0, P3);
    buildTS(&v_transf_serie[10], 1, 3);
    setTSIndividualStartTimings(&v_transf_serie[10], 1, P3);

    for (auto &iter_ts : v_transf_serie)
    {
        iter_ts.serie.push_back(origin_transf_ptr[7]);
        iter_ts.serie.push_back(origin_transf_ptr[6]);
    }
    v_transf_serie[14].start_timing.push_back(P0);
    v_transf_serie[13].start_timing.push_back(P0);
    v_transf_serie[12].start_timing.push_back(P0);
    v_transf_serie[5].start_timing.push_back(P1);
    v_transf_serie[3].start_timing.push_back(P1);
    v_transf_serie[4].start_timing.push_back(P1);
    v_transf_serie[1].start_timing.push_back(P2);
    v_transf_serie[2].start_timing.push_back(P2);
    v_transf_serie[0].start_timing.push_back(P2);
    v_transf_serie[11].start_timing.push_back(P3);
    v_transf_serie[9].start_timing.push_back(P3);
    v_transf_serie[10].start_timing.push_back(P3);
    v_transf_serie[20].start_timing.push_back(P4);
    v_transf_serie[18].start_timing.push_back(P4);
    v_transf_serie[19].start_timing.push_back(P4);
    v_transf_serie[23].start_timing.push_back(P5);
    v_transf_serie[21].start_timing.push_back(P5);
    v_transf_serie[22].start_timing.push_back(P5);
    v_transf_serie[26].start_timing.push_back(P6);
    v_transf_serie[24].start_timing.push_back(P6);
    v_transf_serie[25].start_timing.push_back(P6);
    v_transf_serie[17].start_timing.push_back(P7);
    v_transf_serie[15].start_timing.push_back(P7);
    v_transf_serie[16].start_timing.push_back(P7);
    v_transf_serie[8].start_timing.push_back(P8);
    v_transf_serie[6].start_timing.push_back(P8);
    v_transf_serie[7].start_timing.push_back(P8);

    v_transf_serie[14].start_timing.push_back(P1);
    v_transf_serie[13].start_timing.push_back(P1);
    v_transf_serie[12].start_timing.push_back(P1);
    v_transf_serie[5].start_timing.push_back(P2);
    v_transf_serie[3].start_timing.push_back(P2);
    v_transf_serie[4].start_timing.push_back(P2);
    v_transf_serie[1].start_timing.push_back(P3);
    v_transf_serie[2].start_timing.push_back(P3);
    v_transf_serie[0].start_timing.push_back(P3);
    v_transf_serie[11].start_timing.push_back(P4);
    v_transf_serie[9].start_timing.push_back(P4);
    v_transf_serie[10].start_timing.push_back(P4);
    v_transf_serie[20].start_timing.push_back(P5);
    v_transf_serie[18].start_timing.push_back(P5);
    v_transf_serie[19].start_timing.push_back(P5);
    v_transf_serie[23].start_timing.push_back(P6);
    v_transf_serie[21].start_timing.push_back(P6);
    v_transf_serie[22].start_timing.push_back(P6);
    v_transf_serie[26].start_timing.push_back(P7);
    v_transf_serie[24].start_timing.push_back(P7);
    v_transf_serie[25].start_timing.push_back(P7);
    v_transf_serie[17].start_timing.push_back(P8);
    v_transf_serie[15].start_timing.push_back(P8);
    v_transf_serie[16].start_timing.push_back(P8);
    v_transf_serie[8].start_timing.push_back(P9);
    v_transf_serie[6].start_timing.push_back(P9);
    v_transf_serie[7].start_timing.push_back(P9);

    setTSGlobalDuration(&v_transf_serie[14], E1, 2.0f);
    setTSGlobalDuration(&v_transf_serie[13], E1, 2.0f);
    setTSGlobalDuration(&v_transf_serie[12], E1, 2.0f);
    setTSGlobalDuration(&v_transf_serie[5], E2, 2.0f);
    setTSGlobalDuration(&v_transf_serie[3], E2, 2.0f);
    setTSGlobalDuration(&v_transf_serie[4], E2, 2.0f);
    setTSGlobalDuration(&v_transf_serie[1], E3, 2.0f);
    setTSGlobalDuration(&v_transf_serie[2], E3, 2.0f);
    setTSGlobalDuration(&v_transf_serie[0], E3, 2.0f);
    setTSGlobalDuration(&v_transf_serie[11], E4, 2.0f);
    setTSGlobalDuration(&v_transf_serie[9], E4, 2.0f);
    setTSGlobalDuration(&v_transf_serie[10], E4, 2.0f);
    setTSGlobalDuration(&v_transf_serie[20], E5, 2.0f);
    setTSGlobalDuration(&v_transf_serie[18], E5, 2.0f);
    setTSGlobalDuration(&v_transf_serie[19], E5, 2.0f);
    setTSGlobalDuration(&v_transf_serie[23], E6, 2.0f);
    setTSGlobalDuration(&v_transf_serie[21], E6, 2.0f);
    setTSGlobalDuration(&v_transf_serie[22], E6, 2.0f);
    setTSGlobalDuration(&v_transf_serie[26], E7, 2.0f);
    setTSGlobalDuration(&v_transf_serie[24], E7, 2.0f);
    setTSGlobalDuration(&v_transf_serie[25], E7, 2.0f);
    setTSGlobalDuration(&v_transf_serie[17], E8, 2.0f);
    setTSGlobalDuration(&v_transf_serie[15], E8, 2.0f);
    setTSGlobalDuration(&v_transf_serie[16], E8, 2.0f);
    setTSGlobalDuration(&v_transf_serie[8], E9, 2.0f);
    setTSGlobalDuration(&v_transf_serie[6], E9, 2.0f);
    setTSGlobalDuration(&v_transf_serie[7], E9, 2.0f);
}

void Animation::decorativeCubeDown()
{
    for (int dc = 27; dc < 52; ++dc)
    {
        v_model_attrib[dc].end_formation = v_model_attrib[dc].init_mat;
        v_model_attrib[dc].init_mat *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -130.0f, 0.0f));
        v_model_attrib[dc].init_mat *= glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 1.0f, 0.5f));
    }
    v_model_attrib[52].end_formation = v_model_attrib[52].init_mat;
    v_model_attrib[52].init_mat *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -10.0f, 0.0f));
}

void Animation::animDecorativeCubeCreation()
{
    using namespace glm;

    addEmptyTS(26);
    GLfloat scale_large_duration = 1.2f;
    GLfloat normal_up_duration = 2.0f;
    GLfloat slow_forward_duration = 9.99f;
    GLfloat fast_up_duration = 3.0f;
    GLfloat time_between_start = 0.04f;
    GLfloat start_timing = E9 + 4.0f; // 5.8 + 4.0
    GLfloat timing;

    createNewTransformation(normal_up_duration, TRANS, translate(mat4(1.0f), vec3(0.0f, 5.0f / TPS, 0.0f)),
                            "10_move_up");// 10 U
    createNewTransformation(fast_up_duration, TRANS, translate(mat4(1.0f), vec3(0.0f, 40.0f / TPS, 0.0f)),
                            "11_move_up_fast");// 11 U
    createNewTransformation(slow_forward_duration, TRANS, translate(mat4(1.0f), vec3(0.0f, 1.0f / TPS, 0.0f)),
                            "12_move_up_slow");// 12 U
    createNewTransformation(scale_large_duration, SCALE, scale(mat4(1.0f), vec3(1.01f, 1.0f, 1.01f)),
                            "13_scale_large");// 13


    for (int i = 29; i < 54; ++i)
    {
        buildTS(&v_transf_serie[i], 3, 11, 10, 13);
    }
    buildTS(&v_transf_serie[54], 1, 12);

    timing = start_timing;
    for (int i = 29; i < 54; ++i)
    {
        timing += time_between_start;
        setTSIndividualStartTimings(&v_transf_serie[i], 3, timing - fast_up_duration, timing, timing);
    }
    setTSIndividualStartTimings(&v_transf_serie[54], 1, 6.0f);

    timing = normal_up_duration + start_timing;
    for (int i = 29; i < 54; ++i)
    {
        timing += time_between_start;
        setTSGlobalDuration(&v_transf_serie[i], timing, 0.0f);
    }
    setTSGlobalDuration(&v_transf_serie[54], slow_forward_duration + 6.0f, 0.0f);
}

void Animation::rubikBackToOrigin()
{
    for (int rub = 0; rub < 27; ++rub)
    {
        v_model_attrib[rub].init_mat = glm::mat4(1.0f);
        v_model_attrib[rub].matrix = glm::mat4(1.0f);
    }
}

void Animation::applyRubikCubeCreation()
{
    using namespace glm;

    camera_demo_is_on = true;
    rubikBackToOrigin();
    decorativeCubeDown();

    clearTSsModels(0, 26);
    clearTSsModels(29, 52);

    for (int i = 0; i < 27; ++i)
    {
        linkTS(&v_transf_serie[i], &v_model_attrib[i]);
    }
    /// because TS 27 and 28 are for cube rotations
    for (int dc = 27; dc < 53; ++dc)
    {
        linkTS(&v_transf_serie[dc + 2], &v_model_attrib[dc]);
    }
    for (auto &item: id_2_pos)
    {
        v_transf_serie[item.first].models[0]->end_formation = item.second;
    }

    ensemble1.clear();

    for (int i = 0; i < 55; ++i)
    {
        ensemble1.push_back(&v_transf_serie[i]);
    }

    activateEnsemble(ensemble1);
}

void Animation::animRubikCubeRotations()
{
    using namespace glm;

    addEmptyTS(2);
    createNewTransformation(18.0f / TPS, SCALE, scale(mat4(1.0f), vec3(0.98f, 0.98f, 0.98f)), "8_reduce_mid");
    createNewTransformation(18.0f / TPS, SCALE, scale(mat4(1.0f), vec3(1.02f, 1.02f, 1.02f)), "9_grow_mid");

    // This is modified by changeRotationSpeed();
    quarter_rotation_duration = ((float) M_PI_2) / rotation_speed_indice;
    half_rotation_duration = ((float) M_PI) / rotation_speed_indice;

    /// Quarter Rotation
    buildTS(&v_transf_serie[27], 2, 8, 9);
    setTSIndividualStartTimings(&v_transf_serie[27], 2, 0.0f, quarter_rotation_duration - 18.0f / TPS);
    setTSGlobalDuration(&v_transf_serie[27], quarter_rotation_duration, 0.0f);

    /// Half Rotation
    buildTS(&v_transf_serie[28], 2, 8, 9);
    setTSIndividualStartTimings(&v_transf_serie[28], 2, 0.0f, half_rotation_duration - 18.0f / TPS);
    setTSGlobalDuration(&v_transf_serie[28], half_rotation_duration, 0.0f);
}

void Animation::initRubikCube()
{
    for (auto &item: id_2_pos)
    {
        v_model_attrib[item.first].pos_id = item.first;
        v_model_attrib[item.first].init_mat = item.second;
    }
    for (auto &model: v_model_attrib)
    {
        model.end_formation = model.init_mat;
        model.end_pos_id = model.pos_id;
        model.global_rotation_orientation = glm::mat4(1.0f);
        model.should_rotate = false;
    }
}

void Animation::setEndFormation(int model_id, int pos_id)
{
    v_model_attrib[model_id].end_formation = id_2_pos[pos_id];
    v_model_attrib[model_id].end_pos_id = pos_id;
}

int Animation::getModelFromPosID(int pos_id)
{
    for (int iter_vma = 0; iter_vma < v_model_attrib.size(); iter_vma++)
    {
        if (v_model_attrib[iter_vma].pos_id == pos_id)
            return (iter_vma);
    }
    return (-1);
}

void Animation::printModelAttribPosID()
{
    for (int i = 0; i < 3; ++i)
    {
        std::cerr << "MA: " << i << " pos_id: " << v_model_attrib[i].pos_id << " end_pos_id: "
                  << v_model_attrib[i].end_pos_id << std::endl;
//        std::cerr << "name: " << v_model_attrib[i].name << "ERC: "
//                  << glm::to_string(v_model_attrib[i].global_rotation_orientation) << std::endl;
    }
}