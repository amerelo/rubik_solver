
#include "../inc/Animation.hpp"

void Animation::applyRubikCube_U()
{
    using namespace glm;

    clearTSsModels(27, 27);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id == 6 || model.pos_id == 7 || model.pos_id == 8
                || model.pos_id == 15 || model.pos_id == 16|| model.pos_id == 17
                || model.pos_id == 24|| model.pos_id == 25|| model.pos_id == 26)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI_2;
    rotation_axis = AXIS_R_Y;

    /// which model a subject to rotation
    linkTS(27, getModelFromPosID(6));
    linkTS(27, getModelFromPosID(7));
    linkTS(27, getModelFromPosID(8));
    linkTS(27, getModelFromPosID(15));
    linkTS(27, getModelFromPosID(16));
    linkTS(27, getModelFromPosID(17));
    linkTS(27, getModelFromPosID(24));
    linkTS(27, getModelFromPosID(25));
    linkTS(27, getModelFromPosID(26));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID(6), 8);
    setEndFormation(getModelFromPosID(7), 17);
    setEndFormation(getModelFromPosID(8), 26);
    setEndFormation(getModelFromPosID(15), 7);
    setEndFormation(getModelFromPosID(16), 16);
    setEndFormation(getModelFromPosID(17), 25);
    setEndFormation(getModelFromPosID(24), 6);
    setEndFormation(getModelFromPosID(25), 15);
    setEndFormation(getModelFromPosID(26), 24);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI_2, vec3(0.0f, -1.0f, 0.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[27]);
    activateEnsemble(ensemble1);
}

void Animation::applyRubikCube_U2()
{
    using namespace glm;

    clearTSsModels(28, 28);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id == 6 || model.pos_id == 7 || model.pos_id == 8
            || model.pos_id == 15 || model.pos_id == 16|| model.pos_id == 17
            || model.pos_id == 24|| model.pos_id == 25|| model.pos_id == 26)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI;
    rotation_axis = AXIS_R_Y;

    /// which model a subject to rotation
    linkTS(28, getModelFromPosID(6));
    linkTS(28, getModelFromPosID(7));
    linkTS(28, getModelFromPosID(8));
    linkTS(28, getModelFromPosID(15));
    linkTS(28, getModelFromPosID(16));
    linkTS(28, getModelFromPosID(17));
    linkTS(28, getModelFromPosID(24));
    linkTS(28, getModelFromPosID(25));
    linkTS(28, getModelFromPosID(26));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID( 6), 26);
    setEndFormation(getModelFromPosID( 7), 25);
    setEndFormation(getModelFromPosID( 8), 24);
    setEndFormation(getModelFromPosID(15), 17);
    setEndFormation(getModelFromPosID(16), 16);
    setEndFormation(getModelFromPosID(17), 15);
    setEndFormation(getModelFromPosID(24),  8);
    setEndFormation(getModelFromPosID(25),  7);
    setEndFormation(getModelFromPosID(26),  6);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI, vec3(0.0f, -1.0f, 0.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[28]);
    activateEnsemble(ensemble1);
}

void Animation::applyRubikCube_Uprime()
{
    using namespace glm;

    clearTSsModels(27, 27);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id == 6 || model.pos_id == 7 || model.pos_id == 8
                || model.pos_id == 15 || model.pos_id == 16|| model.pos_id == 17
                || model.pos_id == 24|| model.pos_id == 25|| model.pos_id == 26)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI_2;
    rotation_axis = AXIS_Y;

    /// which model a subject to rotation
    linkTS(27, getModelFromPosID(6));
    linkTS(27, getModelFromPosID(7));
    linkTS(27, getModelFromPosID(8));
    linkTS(27, getModelFromPosID(15));
    linkTS(27, getModelFromPosID(16));
    linkTS(27, getModelFromPosID(17));
    linkTS(27, getModelFromPosID(24));
    linkTS(27, getModelFromPosID(25));
    linkTS(27, getModelFromPosID(26));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID( 6), 24);
    setEndFormation(getModelFromPosID( 7), 15);
    setEndFormation(getModelFromPosID( 8),  6);
    setEndFormation(getModelFromPosID(15), 25);
    setEndFormation(getModelFromPosID(16), 16);
    setEndFormation(getModelFromPosID(17),  7);
    setEndFormation(getModelFromPosID(24), 26);
    setEndFormation(getModelFromPosID(25), 17);
    setEndFormation(getModelFromPosID(26),  8);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI_2, vec3(0.0f, 1.0f, 0.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[27]);
    activateEnsemble(ensemble1);
}

void Animation::applyRubikCube_Dprime()
{
    using namespace glm;

    clearTSsModels(27, 27);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id == 0 || model.pos_id == 1 || model.pos_id == 2
            || model.pos_id ==  9 || model.pos_id == 10|| model.pos_id == 11
            || model.pos_id == 18|| model.pos_id == 19|| model.pos_id == 20)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI_2;
    rotation_axis = AXIS_R_Y;

    /// which model a subject to rotation
    linkTS(27, getModelFromPosID(0));
    linkTS(27, getModelFromPosID(1));
    linkTS(27, getModelFromPosID(2));
    linkTS(27, getModelFromPosID(9));
    linkTS(27, getModelFromPosID(10));
    linkTS(27, getModelFromPosID(11));
    linkTS(27, getModelFromPosID(18));
    linkTS(27, getModelFromPosID(19));
    linkTS(27, getModelFromPosID(20));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID( 0),  2);
    setEndFormation(getModelFromPosID( 1), 11);
    setEndFormation(getModelFromPosID( 2), 20);
    setEndFormation(getModelFromPosID( 9),  1);
    setEndFormation(getModelFromPosID(10), 10);
    setEndFormation(getModelFromPosID(11), 19);
    setEndFormation(getModelFromPosID(18),  0);
    setEndFormation(getModelFromPosID(19),  9);
    setEndFormation(getModelFromPosID(20), 18);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI_2, vec3(0.0f, -1.0f, 0.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[27]);
    activateEnsemble(ensemble1);
}

void Animation::applyRubikCube_D2()
{
    using namespace glm;

    clearTSsModels(28, 28);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id == 0 || model.pos_id == 1 || model.pos_id == 2
            || model.pos_id ==  9 || model.pos_id == 10|| model.pos_id == 11
            || model.pos_id == 18|| model.pos_id == 19|| model.pos_id == 20)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI;
    rotation_axis = AXIS_Y;

    /// which model a subject to rotation
    linkTS(28, getModelFromPosID(0));
    linkTS(28, getModelFromPosID(1));
    linkTS(28, getModelFromPosID(2));
    linkTS(28, getModelFromPosID(9));
    linkTS(28, getModelFromPosID(10));
    linkTS(28, getModelFromPosID(11));
    linkTS(28, getModelFromPosID(18));
    linkTS(28, getModelFromPosID(19));
    linkTS(28, getModelFromPosID(20));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID( 0), 20);
    setEndFormation(getModelFromPosID( 1), 19);
    setEndFormation(getModelFromPosID( 2), 18);
    setEndFormation(getModelFromPosID( 9), 11);
    setEndFormation(getModelFromPosID(10), 10);
    setEndFormation(getModelFromPosID(11),  9);
    setEndFormation(getModelFromPosID(18),  2);
    setEndFormation(getModelFromPosID(19),  1);
    setEndFormation(getModelFromPosID(20),  0);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI, vec3(0.0f, 1.0f, 0.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[28]);
    activateEnsemble(ensemble1);
}

void Animation::applyRubikCube_D()
{
    using namespace glm;

    clearTSsModels(27, 27);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id == 0 || model.pos_id == 1 || model.pos_id == 2
            || model.pos_id ==  9 || model.pos_id == 10|| model.pos_id == 11
            || model.pos_id == 18|| model.pos_id == 19|| model.pos_id == 20)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI_2;
    rotation_axis = AXIS_Y;

    /// which model a subject to rotation
    linkTS(27, getModelFromPosID(0));
    linkTS(27, getModelFromPosID(1));
    linkTS(27, getModelFromPosID(2));
    linkTS(27, getModelFromPosID(9));
    linkTS(27, getModelFromPosID(10));
    linkTS(27, getModelFromPosID(11));
    linkTS(27, getModelFromPosID(18));
    linkTS(27, getModelFromPosID(19));
    linkTS(27, getModelFromPosID(20));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID( 0), 18);
    setEndFormation(getModelFromPosID( 1),  9);
    setEndFormation(getModelFromPosID( 2),  0);
    setEndFormation(getModelFromPosID( 9), 19);
    setEndFormation(getModelFromPosID(10), 10);
    setEndFormation(getModelFromPosID(11),  1);
    setEndFormation(getModelFromPosID(18), 20);
    setEndFormation(getModelFromPosID(19), 11);
    setEndFormation(getModelFromPosID(20),  2);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI_2, vec3(0.0f, 1.0f, 0.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[27]);
    activateEnsemble(ensemble1);
}

void Animation::applyRubikCube_R()
{
    using namespace glm;

    clearTSsModels(27, 27);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id ==  8 ||
            model.pos_id ==  5 ||
            model.pos_id ==  2 ||
            model.pos_id == 17 ||
            model.pos_id == 14 ||
            model.pos_id == 11 ||
            model.pos_id == 26 ||
            model.pos_id == 23 ||
            model.pos_id == 20)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI_2;
    rotation_axis = AXIS_R_X;

    /// which model a subject to rotation
    linkTS(27, getModelFromPosID(8));
    linkTS(27, getModelFromPosID(5));
    linkTS(27, getModelFromPosID(2));
    linkTS(27, getModelFromPosID(17));
    linkTS(27, getModelFromPosID(14));
    linkTS(27, getModelFromPosID(11));
    linkTS(27, getModelFromPosID(26));
    linkTS(27, getModelFromPosID(23));
    linkTS(27, getModelFromPosID(20));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID( 8),  2);
    setEndFormation(getModelFromPosID( 5), 11);
    setEndFormation(getModelFromPosID( 2), 20);
    setEndFormation(getModelFromPosID(17),  5);
    setEndFormation(getModelFromPosID(14), 14);
    setEndFormation(getModelFromPosID(11), 23);
    setEndFormation(getModelFromPosID(26),  8);
    setEndFormation(getModelFromPosID(23), 17);
    setEndFormation(getModelFromPosID(20), 26);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI_2, vec3(-1.0f, 0.0f, 0.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[27]);
    activateEnsemble(ensemble1);
}

void Animation::applyRubikCube_R2()
{
    using namespace glm;

    clearTSsModels(28, 28);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id ==  8 ||
            model.pos_id ==  5 ||
            model.pos_id ==  2 ||
            model.pos_id == 17 ||
            model.pos_id == 14 ||
            model.pos_id == 11 ||
            model.pos_id == 26 ||
            model.pos_id == 23 ||
            model.pos_id == 20)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI;
    rotation_axis = AXIS_R_X;

    /// which model a subject to rotation
    linkTS(28, getModelFromPosID(8));
    linkTS(28, getModelFromPosID(5));
    linkTS(28, getModelFromPosID(2));
    linkTS(28, getModelFromPosID(17));
    linkTS(28, getModelFromPosID(14));
    linkTS(28, getModelFromPosID(11));
    linkTS(28, getModelFromPosID(26));
    linkTS(28, getModelFromPosID(23));
    linkTS(28, getModelFromPosID(20));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID( 8), 20);
    setEndFormation(getModelFromPosID( 5), 23);
    setEndFormation(getModelFromPosID( 2), 26);
    setEndFormation(getModelFromPosID(17), 11);
    setEndFormation(getModelFromPosID(14), 14);
    setEndFormation(getModelFromPosID(11), 17);
    setEndFormation(getModelFromPosID(26),  2);
    setEndFormation(getModelFromPosID(23),  5);
    setEndFormation(getModelFromPosID(20),  8);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI, vec3(-1.0f, 0.0f, 0.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[28]);
    activateEnsemble(ensemble1);
}

void Animation::applyRubikCube_Rprime()
{
    using namespace glm;

    clearTSsModels(27, 27);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id ==  8 ||
            model.pos_id ==  5 ||
            model.pos_id ==  2 ||
            model.pos_id == 17 ||
            model.pos_id == 14 ||
            model.pos_id == 11 ||
            model.pos_id == 26 ||
            model.pos_id == 23 ||
            model.pos_id == 20)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI_2;
    rotation_axis = AXIS_X;

    /// which model a subject to rotation
    linkTS(27, getModelFromPosID(8));
    linkTS(27, getModelFromPosID(5));
    linkTS(27, getModelFromPosID(2));
    linkTS(27, getModelFromPosID(17));
    linkTS(27, getModelFromPosID(14));
    linkTS(27, getModelFromPosID(11));
    linkTS(27, getModelFromPosID(26));
    linkTS(27, getModelFromPosID(23));
    linkTS(27, getModelFromPosID(20));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID( 8), 26);
    setEndFormation(getModelFromPosID( 5), 17);
    setEndFormation(getModelFromPosID( 2),  8);
    setEndFormation(getModelFromPosID(17), 23);
    setEndFormation(getModelFromPosID(14), 14);
    setEndFormation(getModelFromPosID(11),  5);
    setEndFormation(getModelFromPosID(26), 20);
    setEndFormation(getModelFromPosID(23), 11);
    setEndFormation(getModelFromPosID(20),  2);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI_2, vec3(1.0f, 0.0f, 0.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[27]);
    activateEnsemble(ensemble1);
}

void Animation::applyRubikCube_Lprime()
{
    using namespace glm;

    clearTSsModels(27, 27);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id ==  6 ||
            model.pos_id ==  3 ||
            model.pos_id ==  0 ||
            model.pos_id == 15 ||
            model.pos_id == 12 ||
            model.pos_id == 9 ||
            model.pos_id == 24 ||
            model.pos_id == 21 ||
            model.pos_id == 18)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI_2;
    rotation_axis = AXIS_R_X;

    /// which model a subject to rotation
    linkTS(27, getModelFromPosID(6));
    linkTS(27, getModelFromPosID(3));
    linkTS(27, getModelFromPosID(0));
    linkTS(27, getModelFromPosID(15));
    linkTS(27, getModelFromPosID(12));
    linkTS(27, getModelFromPosID(9));
    linkTS(27, getModelFromPosID(24));
    linkTS(27, getModelFromPosID(21));
    linkTS(27, getModelFromPosID(18));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID( 6),  0);
    setEndFormation(getModelFromPosID( 3),  9);
    setEndFormation(getModelFromPosID( 0), 18);
    setEndFormation(getModelFromPosID(15),  3);
    setEndFormation(getModelFromPosID(12), 12);
    setEndFormation(getModelFromPosID( 9), 21);
    setEndFormation(getModelFromPosID(24),  6);
    setEndFormation(getModelFromPosID(21), 15);
    setEndFormation(getModelFromPosID(18), 24);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI_2, vec3(-1.0f, 0.0f, 0.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[27]);
    activateEnsemble(ensemble1);
}

void Animation::applyRubikCube_L2()
{
    using namespace glm;

    clearTSsModels(28, 28);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id ==  6 ||
            model.pos_id ==  3 ||
            model.pos_id ==  0 ||
            model.pos_id == 15 ||
            model.pos_id == 12 ||
            model.pos_id ==  9 ||
            model.pos_id == 24 ||
            model.pos_id == 21 ||
            model.pos_id == 18)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI;
    rotation_axis = AXIS_X;

    /// which model a subject to rotation
    linkTS(28, getModelFromPosID(6));
    linkTS(28, getModelFromPosID(3));
    linkTS(28, getModelFromPosID(0));
    linkTS(28, getModelFromPosID(15));
    linkTS(28, getModelFromPosID(12));
    linkTS(28, getModelFromPosID(9));
    linkTS(28, getModelFromPosID(24));
    linkTS(28, getModelFromPosID(21));
    linkTS(28, getModelFromPosID(18));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID( 6), 18);
    setEndFormation(getModelFromPosID( 3), 21);
    setEndFormation(getModelFromPosID( 0), 24);
    setEndFormation(getModelFromPosID(15),  9);
    setEndFormation(getModelFromPosID(12), 12);
    setEndFormation(getModelFromPosID( 9), 15);
    setEndFormation(getModelFromPosID(24),  0);
    setEndFormation(getModelFromPosID(21),  3);
    setEndFormation(getModelFromPosID(18),  6);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI, vec3(1.0f, 0.0f, 0.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[28]);
    activateEnsemble(ensemble1);
}

void Animation::applyRubikCube_L()
{
    using namespace glm;

    clearTSsModels(27, 27);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id ==  6 ||
            model.pos_id ==  3 ||
            model.pos_id ==  0 ||
            model.pos_id == 15 ||
            model.pos_id == 12 ||
            model.pos_id ==  9 ||
            model.pos_id == 24 ||
            model.pos_id == 21 ||
            model.pos_id == 18)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI_2;
    rotation_axis = AXIS_X;

    /// which model a subject to rotation
    linkTS(27, getModelFromPosID(6));
    linkTS(27, getModelFromPosID(3));
    linkTS(27, getModelFromPosID(0));
    linkTS(27, getModelFromPosID(15));
    linkTS(27, getModelFromPosID(12));
    linkTS(27, getModelFromPosID(9));
    linkTS(27, getModelFromPosID(24));
    linkTS(27, getModelFromPosID(21));
    linkTS(27, getModelFromPosID(18));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID( 6), 24);
    setEndFormation(getModelFromPosID( 3), 15);
    setEndFormation(getModelFromPosID( 0),  6);
    setEndFormation(getModelFromPosID(15), 21);
    setEndFormation(getModelFromPosID(12), 12);
    setEndFormation(getModelFromPosID( 9),  3);
    setEndFormation(getModelFromPosID(24), 18);
    setEndFormation(getModelFromPosID(21),  9);
    setEndFormation(getModelFromPosID(18),  0);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI_2, vec3(1.0f, 0.0f, 0.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[27]);
    activateEnsemble(ensemble1);
}

void Animation::applyRubikCube_F()
{
    using namespace glm;

    clearTSsModels(27, 27);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id == 24 ||
            model.pos_id == 25 ||
            model.pos_id == 26 ||
            model.pos_id == 21 ||
            model.pos_id == 22 ||
            model.pos_id == 23 ||
            model.pos_id == 18 ||
            model.pos_id == 19 ||
            model.pos_id == 20)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI_2;
    rotation_axis = AXIS_R_Z;

    /// which model a subject to rotation
    linkTS(27, getModelFromPosID(24));
    linkTS(27, getModelFromPosID(25));
    linkTS(27, getModelFromPosID(26));
    linkTS(27, getModelFromPosID(21));
    linkTS(27, getModelFromPosID(22));
    linkTS(27, getModelFromPosID(23));
    linkTS(27, getModelFromPosID(18));
    linkTS(27, getModelFromPosID(19));
    linkTS(27, getModelFromPosID(20));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID(24), 26);
    setEndFormation(getModelFromPosID(25), 23);
    setEndFormation(getModelFromPosID(26), 20);
    setEndFormation(getModelFromPosID(21), 25);
    setEndFormation(getModelFromPosID(22), 22);
    setEndFormation(getModelFromPosID(23), 19);
    setEndFormation(getModelFromPosID(18), 24);
    setEndFormation(getModelFromPosID(19), 21);
    setEndFormation(getModelFromPosID(20), 18);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI_2, vec3(0.0f, 0.0f, -1.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[27]);
    activateEnsemble(ensemble1);
}

void Animation::applyRubikCube_F2()
{
    using namespace glm;

    clearTSsModels(28, 28);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id == 24 ||
            model.pos_id == 25 ||
            model.pos_id == 26 ||
            model.pos_id == 21 ||
            model.pos_id == 22 ||
            model.pos_id == 23 ||
            model.pos_id == 18 ||
            model.pos_id == 19 ||
            model.pos_id == 20)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI;
    rotation_axis = AXIS_R_Z;

    /// which model a subject to rotation
    linkTS(28, getModelFromPosID(24));
    linkTS(28, getModelFromPosID(25));
    linkTS(28, getModelFromPosID(26));
    linkTS(28, getModelFromPosID(21));
    linkTS(28, getModelFromPosID(22));
    linkTS(28, getModelFromPosID(23));
    linkTS(28, getModelFromPosID(18));
    linkTS(28, getModelFromPosID(19));
    linkTS(28, getModelFromPosID(20));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID(24), 20);
    setEndFormation(getModelFromPosID(25), 19);
    setEndFormation(getModelFromPosID(26), 18);
    setEndFormation(getModelFromPosID(21), 23);
    setEndFormation(getModelFromPosID(22), 22);
    setEndFormation(getModelFromPosID(23), 21);
    setEndFormation(getModelFromPosID(18), 26);
    setEndFormation(getModelFromPosID(19), 25);
    setEndFormation(getModelFromPosID(20), 24);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI, vec3(0.0f, 0.0f, -1.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[28]);
    activateEnsemble(ensemble1);
}

void Animation::applyRubikCube_Fprime()
{
    using namespace glm;

    clearTSsModels(27, 27);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id == 24 ||
            model.pos_id == 25 ||
            model.pos_id == 26 ||
            model.pos_id == 21 ||
            model.pos_id == 22 ||
            model.pos_id == 23 ||
            model.pos_id == 18 ||
            model.pos_id == 19 ||
            model.pos_id == 20)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI_2;
    rotation_axis = AXIS_Z;

    /// which model a subject to rotation
    linkTS(27, getModelFromPosID(24));
    linkTS(27, getModelFromPosID(25));
    linkTS(27, getModelFromPosID(26));
    linkTS(27, getModelFromPosID(21));
    linkTS(27, getModelFromPosID(22));
    linkTS(27, getModelFromPosID(23));
    linkTS(27, getModelFromPosID(18));
    linkTS(27, getModelFromPosID(19));
    linkTS(27, getModelFromPosID(20));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID(24), 18);
    setEndFormation(getModelFromPosID(25), 21);
    setEndFormation(getModelFromPosID(26), 24);
    setEndFormation(getModelFromPosID(21), 19);
    setEndFormation(getModelFromPosID(22), 22);
    setEndFormation(getModelFromPosID(23), 25);
    setEndFormation(getModelFromPosID(18), 20);
    setEndFormation(getModelFromPosID(19), 23);
    setEndFormation(getModelFromPosID(20), 26);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI_2, vec3(0.0f, 0.0f, 1.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[27]);
    activateEnsemble(ensemble1);
}

void Animation::applyRubikCube_Bprime()
{
    using namespace glm;

    clearTSsModels(27, 27);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id == 0 ||
            model.pos_id == 1 ||
            model.pos_id == 2 ||
            model.pos_id == 3 ||
            model.pos_id == 4 ||
            model.pos_id == 5 ||
            model.pos_id == 6 ||
            model.pos_id == 7 ||
            model.pos_id == 8)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI_2;
    rotation_axis = AXIS_R_Z;

    /// which model a subject to rotation
    linkTS(27, getModelFromPosID(0));
    linkTS(27, getModelFromPosID(1));
    linkTS(27, getModelFromPosID(2));
    linkTS(27, getModelFromPosID(3));
    linkTS(27, getModelFromPosID(4));
    linkTS(27, getModelFromPosID(5));
    linkTS(27, getModelFromPosID(6));
    linkTS(27, getModelFromPosID(7));
    linkTS(27, getModelFromPosID(8));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID(0), 6);
    setEndFormation(getModelFromPosID(1), 3);
    setEndFormation(getModelFromPosID(2), 0);
    setEndFormation(getModelFromPosID(3), 7);
    setEndFormation(getModelFromPosID(4), 4);
    setEndFormation(getModelFromPosID(5), 1);
    setEndFormation(getModelFromPosID(6), 8);
    setEndFormation(getModelFromPosID(7), 5);
    setEndFormation(getModelFromPosID(8), 2);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI_2, vec3(0.0f, 0.0f, -1.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[27]);
    activateEnsemble(ensemble1);
}

void Animation::applyRubikCube_B2()
{
    using namespace glm;

    clearTSsModels(28, 28);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id == 0 ||
            model.pos_id == 1 ||
            model.pos_id == 2 ||
            model.pos_id == 3 ||
            model.pos_id == 4 ||
            model.pos_id == 5 ||
            model.pos_id == 6 ||
            model.pos_id == 7 ||
            model.pos_id == 8)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI;
    rotation_axis = AXIS_Z;

    /// which model a subject to rotation
    linkTS(28, getModelFromPosID(0));
    linkTS(28, getModelFromPosID(1));
    linkTS(28, getModelFromPosID(2));
    linkTS(28, getModelFromPosID(3));
    linkTS(28, getModelFromPosID(4));
    linkTS(28, getModelFromPosID(5));
    linkTS(28, getModelFromPosID(6));
    linkTS(28, getModelFromPosID(7));
    linkTS(28, getModelFromPosID(8));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID(0), 8);
    setEndFormation(getModelFromPosID(1), 7);
    setEndFormation(getModelFromPosID(2), 6);
    setEndFormation(getModelFromPosID(3), 5);
    setEndFormation(getModelFromPosID(4), 4);
    setEndFormation(getModelFromPosID(5), 3);
    setEndFormation(getModelFromPosID(6), 2);
    setEndFormation(getModelFromPosID(7), 1);
    setEndFormation(getModelFromPosID(8), 0);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI, vec3(0.0f, 0.0f, 1.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[28]);
    activateEnsemble(ensemble1);
}

void Animation::applyRubikCube_B()
{
    using namespace glm;

    clearTSsModels(27, 27);

    /// rotation setup
    for (auto &model: v_model_attrib)
    {
        if (model.pos_id == 0 ||
            model.pos_id == 1 ||
            model.pos_id == 2 ||
            model.pos_id == 3 ||
            model.pos_id == 4 ||
            model.pos_id == 5 ||
            model.pos_id == 6 ||
            model.pos_id == 7 ||
            model.pos_id == 8)
            model.should_rotate = true;
    }
    rotation_amount = 0.0f;
    rotation_goal = (float) M_PI_2;
    rotation_axis = AXIS_Z;

    /// which model a subject to rotation
    linkTS(27, getModelFromPosID(0));
    linkTS(27, getModelFromPosID(1));
    linkTS(27, getModelFromPosID(2));
    linkTS(27, getModelFromPosID(3));
    linkTS(27, getModelFromPosID(4));
    linkTS(27, getModelFromPosID(5));
    linkTS(27, getModelFromPosID(6));
    linkTS(27, getModelFromPosID(7));
    linkTS(27, getModelFromPosID(8));

    /// where does the model end and in which orientation
    setEndFormation(getModelFromPosID(0), 2);
    setEndFormation(getModelFromPosID(1), 5);
    setEndFormation(getModelFromPosID(2), 8);
    setEndFormation(getModelFromPosID(3), 1);
    setEndFormation(getModelFromPosID(4), 4);
    setEndFormation(getModelFromPosID(5), 7);
    setEndFormation(getModelFromPosID(6), 0);
    setEndFormation(getModelFromPosID(7), 3);
    setEndFormation(getModelFromPosID(8), 6);

    for (auto &model:v_model_attrib)
    {
        if (model.should_rotate)
        {
            //end anim rotation
            glm::mat4 temp_rotation = model.global_rotation_orientation;
            model.global_rotation_orientation = glm::mat4(1.0);
            model.global_rotation_orientation *= rotate(mat4(1.0f), (float) M_PI_2, vec3(0.0f, 0.0f, 1.0f));
            model.global_rotation_orientation *= temp_rotation;
            model.end_formation *= model.global_rotation_orientation;
        }
    }

    ensemble1.clear();
    ensemble1.push_back(&v_transf_serie[27]);
    activateEnsemble(ensemble1);
}
