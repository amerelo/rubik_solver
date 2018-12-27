//
// Created by Hugo JEANNIN on 3/11/17.
//

#include <cmath>

#include "../inc/Camera.hpp"

Camera::Camera()
{
    std::cerr << "Camera() constructor called." << std::endl;
}

Camera::~Camera()
{
    std::cerr << "Camera() destructor called." << std::endl;
}

void
Camera::init()
{
    rotate_around_mode_on = CAMERA_ROTATE_AROUND_ON;
    fixed_refl_pos_y = -2.5f;
    fixed_pos_y = 2.4f;
    fixed_vertical_angle = -0.52f;
    roll = 0.0f;
    up = {0.0f, 1.0f, 0.0f};
    if (DEMO_ON_STARTUP)
    {
        roll = 0.0f;
        fixed_vertical_angle = 0.78f;
        pos = {0.0f, 3.0f, 8.0f};
        front = {0.0f, 0.0f, -1.0f};
        horizontal_angle = 1.66f; // 1.58 is centered it is not for style.
        vertical_angle = 0.0f;
        center_horizontal_angle = 0.0f;
        center_vertical_angle = 0.0f;
    }
    else
    {
        pos = {2.588088f, 3.000000f, 5.413114f};
        front = {-0.447564, -0.479426, -0.754876};
        horizontal_angle = 0.535181f;
        vertical_angle = 0.0f;
        center_horizontal_angle = 1.12961f;
        center_vertical_angle = 0.0f;
    }
    movement_speed = 12.0f / TPS;
    rotation_speed = 1.2f / TPS;
    mouse_speed = 0.002f;
    radius = 6.0f;
    perspective_matrix = glm::perspective(1.20f, 16.0f / 9.0f, 0.1f, 100.0f);
    screen_center.x = INITIAL_RES_X / 2;
    screen_center.y = INITIAL_RES_Y / 2;
    if (CAMERA_CFG_AUTO_LOAD)
        loadConfig();

    /// Reflection:
    refl_up = {0.0f, -1.0f, 0.0f};
    refl_pos = pos;
    refl_pos.y = fixed_refl_pos_y;
    refl_front = front;
    refl_perspective_matrix = glm::perspective(2.2f, 1.0f / 1.0f, 0.1f, 100.0f);
}

void
Camera::switchMode()
{
    if (rotate_around_mode_on)
    {
        loadConfig();
        rotate_around_mode_on = false;
    }
    else if (!rotate_around_mode_on)
    {
        init();
        rotate_around_mode_on = true;
    }
    else
        std::cerr << "Something went wrong switching mode." << std::endl;
}

void
Camera::updateMouse(double &xpos, double &ypos)
{
    /// Need to recompute screen_center if resolution changes.
    if (rotate_around_mode_on)
    {
        center_horizontal_angle += (screen_center.x - xpos) * mouse_speed;
        center_vertical_angle += (screen_center.y - ypos) * mouse_speed;
        horizontal_angle -= (screen_center.x - xpos) * mouse_speed;
        vertical_angle -= (screen_center.y - ypos) * mouse_speed;
    }
    else
    {
        horizontal_angle += (screen_center.x - xpos) * mouse_speed;
        vertical_angle += (screen_center.y - ypos) * mouse_speed;
    }
}

void
Camera::updateMatrix()
{
    front = {0.0f, 0.0f, -1.0f};
    if (rotate_around_mode_on)
    {
        front = glm::rotateX(front, fixed_vertical_angle);
        front = glm::rotateY(front, horizontal_angle);
        pos.x = radius * std::cos(center_horizontal_angle);
        pos.z = radius * std::sin(center_horizontal_angle);
        pos.y = fixed_pos_y;
    }
    else
    {
        front = glm::rotateX(front, vertical_angle);
        front = glm::rotateY(front, horizontal_angle);
    }
    pos_and_front = pos;
    pos_and_front += front;
    matrix = glm::lookAt(pos, pos_and_front, up);
    matrix = glm::rotate(matrix, roll, pos_and_front);

    /// Reflection:
    refl_front = {0.0f, 0.0f, -1.0f};
    if (rotate_around_mode_on)
    {
        refl_front = glm::rotateX(refl_front, fixed_vertical_angle * -1.0f);
        refl_front = glm::rotateY(refl_front, horizontal_angle - 0.08f); /// Because I did not centered the fucking original camera angle
    }
    else
    {
        refl_front = glm::rotateX(refl_front, vertical_angle * -1.0f);
        refl_front = glm::rotateY(refl_front, horizontal_angle - 0.08f);/// Because I did not centered the fucking original camera angle
    }
    refl_pos = pos;
    refl_pos.y = fixed_refl_pos_y - (pos.y - fixed_refl_pos_y);
    refl_pos_and_front = refl_pos;
    refl_pos_and_front += refl_front;
    refl_matrix = glm::lookAt(refl_pos, refl_pos_and_front, refl_up);
}

void
Camera::moveForward()
{
    if (!rotate_around_mode_on)
    {
        move_forward = front;
        move_forward *= movement_speed;
        pos += move_forward;
    }
}

void
Camera::moveBackward()
{
    if (!rotate_around_mode_on)
    {
        move_forward = front;
        move_forward *= movement_speed;
        pos -= move_forward;
    }
}

void
Camera::strafeLeft()
{
    if (!rotate_around_mode_on)
    {
        move_left = glm::normalize(glm::cross(front, up));
        move_left *= movement_speed;
        pos -= move_left;
    }
}

void
Camera::strafeRight()
{
    if (!rotate_around_mode_on)
    {
        move_left = glm::normalize(glm::cross(front, up));
        move_left *= movement_speed;
        pos += move_left;
    }
}

void
Camera::moveUp()
{
    if (!rotate_around_mode_on)
    {
        move_up = up;
        move_up *= movement_speed;
        pos += move_up;
    }
}

void
Camera::moveDown()
{
    if (!rotate_around_mode_on)
    {
        move_up = up;
        move_up *= movement_speed;
        pos -= move_up;
    }
}

void
Camera::rotateLeft()
{
    if (!rotate_around_mode_on)
    {
        horizontal_angle += rotation_speed;
    }
    else
    {
        center_horizontal_angle += rotation_speed;
        horizontal_angle -= rotation_speed;
    }

}

void
Camera::rotateRight()
{
    if (!rotate_around_mode_on)
    {
        horizontal_angle -= rotation_speed;
    }
    else
    {
        center_horizontal_angle -= rotation_speed;
        horizontal_angle += rotation_speed;
    }
}

void
Camera::rotateUp()
{
    if (!rotate_around_mode_on)
    {
        vertical_angle += rotation_speed;
        if (vertical_angle >= 1.4f)
            vertical_angle = 1.4f;
    }
    else
    {
        vertical_angle += rotation_speed;
        center_vertical_angle -= rotation_speed;
    }

}

void
Camera::rotateDown()
{
    if (!rotate_around_mode_on)
    {
        vertical_angle -= rotation_speed;
        if (vertical_angle <= -1.4f)
            vertical_angle = -1.4f;
    }
    else
    {
        vertical_angle -= rotation_speed;
        center_vertical_angle += rotation_speed;
    }
}

void
Camera::rollRight()
{
    roll += rotation_speed;
}

void
Camera::rollLeft()
{
    roll -= rotation_speed;
}

void
Camera::print()
{
    std::cout << "pos   : " << glm::to_string(pos) << std::endl;
    std::cout << "front : " << glm::to_string(front) << std::endl;
    std::cout << "up    : " << glm::to_string(up) << std::endl;
    std::cout << "hor   : " << horizontal_angle << std::endl;
    std::cout << "ver   : " << vertical_angle << std::endl;
    std::cout << "c how : " << center_horizontal_angle << std::endl;
    std::cout << "c ver : " << center_vertical_angle << std::endl;
    std::cout << "matrix:" << glm::to_string(perspective_matrix) << std::endl;
}

void Camera::writeConfig()
{
    std::ofstream cacfg;

    cacfg.open("../config/camera.cfg");
    if (cacfg.is_open())
    {
        cacfg << pos.x << std::endl;
        cacfg << pos.y << std::endl;
        cacfg << pos.z << std::endl;
        cacfg << front.x << std::endl;
        cacfg << front.y << std::endl;
        cacfg << front.z << std::endl;
        cacfg << horizontal_angle << std::endl;
        cacfg << vertical_angle << std::endl;
        cacfg.close();
    }
    else
    {
        std::cerr << "Failed to write Camera config." << std::endl;
    }
}

void Camera::loadConfig()
{
    std::string line;
    std::ifstream cacfg("../config/camera.cfg");

    if (cacfg.is_open())
    {
        getline(cacfg, line);
        pos.x = std::stof(line, 0);
        getline(cacfg, line);
        pos.y = std::stof(line, 0);
        getline(cacfg, line);
        pos.z = std::stof(line, 0);
        getline(cacfg, line);
        front.x = std::stof(line, 0);
        getline(cacfg, line);
        front.y = std::stof(line, 0);
        getline(cacfg, line);
        front.z = std::stof(line, 0);
        getline(cacfg, line);
        horizontal_angle = std::stof(line, 0);
        getline(cacfg, line);
        vertical_angle = std::stof(line, 0);
        cacfg.close();
    }
    else
    {
        std::cerr << "Failed to load Camera config." << std::endl;
    }
}
