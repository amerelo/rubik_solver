//
// Created by Hugo JEANNIN on 3/11/17.
//

#ifndef CAMERA_HPP
# define CAMERA_HPP
# define GLM_ENABLE_EXPERIMENTAL

# include <iostream>
# include <GLM/ext.hpp>
# include <GLM/vec3.hpp>
# include <GLM/gtx/rotate_vector.hpp>
# include <GLM/gtx/string_cast.hpp>
# include <fstream>
# include <string>
# include <iostream>
# include "../inc/Constant.hpp"

class Camera
{
public:
    glm::mat4       matrix;
    glm::mat4       perspective_matrix;
    glm::vec3       pos;
    glm::vec3       front;
    glm::vec3		pos_and_front;
    glm::vec3       up;
    float           horizontal_angle;
    float           vertical_angle;
    float           center_horizontal_angle;
    float           center_vertical_angle;

    glm::mat4       refl_matrix;
    glm::mat4       refl_perspective_matrix;
    glm::vec3       refl_pos;
    glm::vec3       refl_front;
    glm::vec3		refl_pos_and_front;
    glm::vec3		refl_up;

    float           fixed_refl_pos_y;

	glm::vec3		move_forward;
    glm::vec3		move_left;
	glm::vec3		move_up;

    float           movement_speed;
    float           rotation_speed;
    float           radius;
    glm::vec2       screen_center;
	float 			mouse_speed;
    float           roll;

    bool            rotate_around_mode_on;

    float           fixed_vertical_angle;
    float           fixed_pos_y;

    Camera();
    ~Camera();

    void            init();
    void            switchMode();
    void            updateMouse(double &xpos, double &ypos);
    void            updateMatrix();
    void            moveForward();
    void            moveBackward();
    void            strafeLeft();
    void            strafeRight();
    void            moveUp();
    void            moveDown();
    void            rotateLeft();
    void            rotateRight();
    void            rotateUp();
    void            rotateDown();
    void            rollRight();
    void            rollLeft();

    void            print();
	void 			writeConfig();
	void 			loadConfig();
};

#endif //CAMERA_HPP
