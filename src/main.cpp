//
// Created by Hugo JEANNIN on 3/10/17.
//

#include "../inc/Core.hpp"

static void
keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    (void) scancode;
    (void) mods;

    Core *core = reinterpret_cast<Core *>(glfwGetWindowUserPointer(window));

    if (glfwGetTime() > 21.0)
    {

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        if (key == GLFW_KEY_L && action == GLFW_PRESS)
        {
            core->light_pos = core->camera.pos;
        }
        if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS)
        {
//        core->tweakcore += 0.05f;
        }
        if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS)
        {
//        core->tweakcore -= 0.05f;
        }
        if (key == GLFW_KEY_R && action == GLFW_PRESS)
        {
            core->addRandomMoves(3);
        }
        if (key == GLFW_KEY_M && action == GLFW_RELEASE)
        {
            core->camera.switchMode();
        }
//    if (key == GLFW_KEY_O && action == GLFW_RELEASE)
//    {
//        core->resolver.switchAlgo();
//    }
        if (key == GLFW_KEY_P && action == GLFW_RELEASE)
        {
            core->resolver.prettyRubikCubePrint(core->resolver.current_state);
        }
        if (key == GLFW_KEY_X && action == GLFW_RELEASE)
        {
            core->render_axes_on = !core->render_axes_on;
        }
        if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE)
        {
            core->anim_queue_is_running = !core->anim_queue_is_running;
        }
        if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
        {
            core->resolveRubik();
        }
        if (!core->anim_queue_is_running && core->anim_queue.size() == 0)
        {
            if (key == GLFW_KEY_1 && action == GLFW_RELEASE)
                core->createPlayList(core->raw_play_list_sequence[0]);
            if (key == GLFW_KEY_2 && action == GLFW_RELEASE)
                core->createPlayList(core->raw_play_list_sequence[1]);
            if (key == GLFW_KEY_3 && action == GLFW_RELEASE)
                core->createPlayList(core->raw_play_list_sequence[2]);
            if (key == GLFW_KEY_4 && action == GLFW_RELEASE)
                core->createPlayList(core->raw_play_list_sequence[3]);
            if (key == GLFW_KEY_5 && action == GLFW_RELEASE)
                core->createPlayList(core->raw_play_list_sequence[4]);
            if (key == GLFW_KEY_6 && action == GLFW_RELEASE)
                core->createPlayList(core->raw_play_list_sequence[5]);
            if (key == GLFW_KEY_7 && action == GLFW_RELEASE)
                core->createPlayList(core->raw_play_list_sequence[6]);
            if (key == GLFW_KEY_8 && action == GLFW_RELEASE)
                core->createPlayList(core->raw_play_list_sequence[7]);
            if (key == GLFW_KEY_9 && action == GLFW_RELEASE)
                core->createPlayList(core->raw_play_list_sequence[8]);
            if (key == GLFW_KEY_0 && action == GLFW_RELEASE)
                core->createPlayList(core->raw_play_list_sequence[9]);
            if (key == GLFW_KEY_B && action == GLFW_RELEASE)
            {
                core->animation.changeRotationSpeed();
            }
        }
        if (key == GLFW_KEY_KP_ENTER && action == GLFW_RELEASE)
        {
            core->animation.initRubikCube();
            core->resolver.createResolvedState(core->resolver.current_state);
        }
        if (!core->animation.isAnyAnimationOn())
        {
            if (!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && !glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
            {
                if (key == GLFW_KEY_KP_4 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_L();
                    core->resolver.apply_L(core->resolver.current_state, core->resolver.current_state);
                }
                if (key == GLFW_KEY_KP_6 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_R();
                    core->resolver.apply_R(core->resolver.current_state, core->resolver.current_state);
                }
                if (key == GLFW_KEY_KP_8 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_U();
                    core->resolver.apply_U(core->resolver.current_state, core->resolver.current_state);
                }
                if (key == GLFW_KEY_KP_2 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_D();
                    core->resolver.apply_D(core->resolver.current_state, core->resolver.current_state);
                }
                if (key == GLFW_KEY_KP_5 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_B();
                    core->resolver.apply_B(core->resolver.current_state, core->resolver.current_state);
                }
                if (key == GLFW_KEY_KP_0 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_F();
                    core->resolver.apply_F(core->resolver.current_state, core->resolver.current_state);
                }
            }
            if (!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
            {
                if (key == GLFW_KEY_KP_4 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_L2();
                    core->resolver.apply_L2(core->resolver.current_state, core->resolver.current_state);
                }
                if (key == GLFW_KEY_KP_6 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_R2();
                    core->resolver.apply_R2(core->resolver.current_state, core->resolver.current_state);
                }
                if (key == GLFW_KEY_KP_8 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_U2();
                    core->resolver.apply_U2(core->resolver.current_state, core->resolver.current_state);
                }
                if (key == GLFW_KEY_KP_2 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_D2();
                    core->resolver.apply_D2(core->resolver.current_state, core->resolver.current_state);
                }
                if (key == GLFW_KEY_KP_5 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_B2();
                    core->resolver.apply_B2(core->resolver.current_state, core->resolver.current_state);
                }
                if (key == GLFW_KEY_KP_0 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_F2();
                    core->resolver.apply_F2(core->resolver.current_state, core->resolver.current_state);
                }
            }
            if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
            {
                if (key == GLFW_KEY_KP_4 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_Lprime();
                    core->resolver.apply_Lprime(core->resolver.current_state, core->resolver.current_state);
                }
                if (key == GLFW_KEY_KP_6 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_Rprime();
                    core->resolver.apply_Rprime(core->resolver.current_state, core->resolver.current_state);
                }
                if (key == GLFW_KEY_KP_8 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_Uprime();
                    core->resolver.apply_Uprime(core->resolver.current_state, core->resolver.current_state);
                }
                if (key == GLFW_KEY_KP_2 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_Dprime();
                    core->resolver.apply_Dprime(core->resolver.current_state, core->resolver.current_state);
                }
                if (key == GLFW_KEY_KP_5 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_Bprime();
                    core->resolver.apply_Bprime(core->resolver.current_state, core->resolver.current_state);
                }
                if (key == GLFW_KEY_KP_0 && action == GLFW_PRESS)
                {
                    core->animation.applyRubikCube_Fprime();
                    core->resolver.apply_Fprime(core->resolver.current_state, core->resolver.current_state);
                }
            }
        }
    }
}

static void
cursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
    Core *core = reinterpret_cast<Core *>(glfwGetWindowUserPointer(window));

    core->camera.updateMouse(xpos, ypos);
    glfwSetCursorPos(window, core->res_x / 2, core->res_y / 2);
}

static void
updateCamera(Camera &camera, GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.moveForward();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.moveBackward();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.strafeLeft();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.strafeRight();
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.rollLeft();
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.rollRight();
    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        camera.moveUp();
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        camera.moveDown();
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.rotateLeft();
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.rotateRight();
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.rotateUp();
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.rotateDown();
}

static int
initGLFW(Core &core)
{
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, SAMPLE_RATE);
    if (FULL_SCREEN)
        core.window = glfwCreateWindow(core.res_x, core.res_y, "Minimal_OpenGL", glfwGetPrimaryMonitor(), nullptr);
    else
        core.window = glfwCreateWindow(core.res_x, core.res_y, "Minimal_OpenGL", nullptr, nullptr);

    if (!core.window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(core.window);
    glfwSetKeyCallback(core.window, keyCallback);
    glfwSetCursorPosCallback(core.window, cursorPosCallback);
    glfwSetWindowUserPointer(core.window, &core);
    glfwSetInputMode(core.window, GLFW_CURSOR, CURSOR_MODE);
    return 0;
}

static int
mainLoop(Core &core)
{
    double begin_time, update_time, frame_time;
    double next_string_update, next_env_update;
    double frame_counter, update_counter;
    double tick_length;
    int loops;
    int max_frame_skip;
    uint32_t current_tick;
    std::string title;
    float modifier = (float) (0.1 / TPS);

    update_time = 0.0f;
    frame_counter = 0.0f;
    update_counter = 0.0f;
    tick_length = 1.0f / TICK_PER_SECOND;
    max_frame_skip = 5;
    next_env_update = glfwGetTime();
    next_string_update = glfwGetTime();
    current_tick = 0;
    srand((unsigned int) glfwGetTime());

    while (!glfwWindowShouldClose(core.window))
    {
        ////////////
        // Update //
        ////////////

        loops = 0;
        // Tant que tu depasse le timing d'update tu skip des frames et au max 5 frame.
        while (glfwGetTime() > next_env_update && loops < max_frame_skip)
        {
            begin_time = glfwGetTime();

            glfwPollEvents();
            update_counter++;
            next_env_update += tick_length;
            loops++;
            if (core.animation.camera_demo_is_on)
            {
                if (core.camera.fixed_vertical_angle > -0.52f)
                {
                    core.camera.fixed_vertical_angle -= 0.2 / TPS - modifier;
                    modifier -= 0.001 / TPS;
                    core.camera.roll -= 0.04 / TPS;
//                    std::cerr << core.camera.roll << std::endl;
                }
                core.camera.roll = 0.0f;
                core.camera.center_horizontal_angle += 0.096f / TPS;
                core.camera.horizontal_angle -= 0.096f / TPS;
            }
            if (core.anim_queue_is_running)
            {
                core.runPlayList();
            }
            core.animation.update();
            updateCamera(core.camera, core.window);
            core.camera.updateMatrix();
            current_tick++;
            update_time = glfwGetTime();
            update_time -= begin_time;
        }

        //////////////////
        // Render Frame //
        //////////////////

        begin_time = glfwGetTime();

        core.renderImage();
        glfwSwapBuffers(core.window);

        frame_counter++;
        frame_time = glfwGetTime();
        frame_time -= begin_time;

        //////////////////
        // Title Update //
        //////////////////

        if (glfwGetTime() - next_string_update >= 1.0f)
        {
            next_string_update += 1.0f;
            title.clear();
            title.append("FPS: ");
            title.append(std::to_string((int) frame_counter));
            title.append(" - ");
            title.append(std::to_string(frame_time));
            title.append("ms");
            title.append(" ");
            title.append("UPS: ");
            title.append(std::to_string((int) update_counter));
            title.append(" - ");
            title.append(std::to_string(update_time));
            title.append("ms");
            title.append(" ");
            title.append("Camera: [");
            title.append(std::to_string(core.camera.pos.x));
            title.append(", ");
            title.append(std::to_string(core.camera.pos.y));
            title.append(", ");
            title.append(std::to_string(core.camera.pos.z));
            title.append("][");
            title.append(std::to_string(core.camera.vertical_angle));
            title.append("][");
            title.append(std::to_string(core.camera.center_horizontal_angle));
            title.append("] ");
            title.append(" Time: ");
            title.append(std::to_string(glfwGetTime()));
            title.append(" Rotation Amount: ");
            title.append(std::to_string(core.animation.rotation_amount));
            title.append(" Alpha Indice: ");
            title.append(std::to_string(core.animation.alpha_indice));
            if (core.animation.iter_alpha_indice)
                title.append(" ON ");
            else
                title.append(" OFF ");
            glfwSetWindowTitle(core.window, title.c_str());
            frame_counter = 0.0;
            update_counter = 0.0;
        }
    }
    return 0;
}

static void displayCommands(void)
{
    std::cout << "--------------" << std::endl;
    std::cout << "-- COMMANDS --" << std::endl;
    std::cout << "--------------" << std::endl;
    std::cout << "[1][2][3][4][5][6][7][8][9][0]" << std::endl;
    std::cout << "to Load pre-configured shuffle from ./config/rubik_shuffles.cfg." << std::endl;
    std::cout << std::endl;
    std::cout << "[return] run animation." << std::endl;
    std::cout << "[spacebar] run resolution algo." << std::endl;
    std::cout << std::endl;
    std::cout << "Keypad:    [ ][8][ ][ ]       U " << std::endl;
    std::cout << "           [4][5][6][ ]     L B R" << std::endl;
    std::cout << "           [ ][2][ ][ ]       D" << std::endl;
    std::cout << "           [   0][ ][ ]       F" << std::endl;
    std::cout << "                [enter]       to reset the cube." << std::endl;
    std::cout << std::endl;
    std::cout << "Use [shift] to do U2 F2 etc..." << std::endl;
    std::cout << "Use [control] to do U' F' etc..." << std::endl;
    std::cout << std::endl;
    std::cout << "[R] add 3 random moves to playlist" << std::endl;
//    std::cout << "[O] to switch algo" << std::endl;
    std::cout << std::endl;
    std::cout << "[L] place light" << std::endl;
    std::cout << "[B] change rotation speed" << std::endl;
    std::cout << "    [ ]" << std::endl;
    std::cout << "[<-][ ][->] rotate camera around the cube" << std::endl;
    std::cout << "--------------" << std::endl;
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    displayCommands();
    Core core;

    core.init();

    core.object_cube_rubik = new ObjectLoader("../assets/obj/rubik.obj");
    core.object_cube_rubik->makeOpenGLBuffer();
    core.object_cube_rubik_low_poly = new ObjectLoader("../assets/obj/rubik_low_poly.obj");
    core.object_cube_rubik_low_poly->makeOpenGLBuffer();
    core.object_cube_block = new ObjectLoader("../assets/obj/cube_simpleUV.obj");
    core.object_cube_block->makeOpenGLBuffer();
    core.object_square = new ObjectLoader("../assets/obj/square.obj");
    core.object_square->makeOpenGLBuffer();
    initGLFW(core);
    core.createBuffers();
    core.loadTextures();
    if (!core.loadShaders())
    {
        std::cerr << "Failed to load shaders." << std::endl;
        return 1;
    }
    core.getShadersLocations();
    glEnable(GL_DEPTH_TEST);

    // Face Culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mainLoop(core);

    delete core.object_cube_rubik;
    delete core.object_cube_rubik_low_poly;
    delete core.object_cube_block;
    delete core.object_square;
    glfwDestroyWindow(core.window);
    glfwTerminate();
    return 0;
}