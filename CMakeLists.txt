cmake_minimum_required(VERSION 3.5)
project(rubik)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
        src/main.cpp
        src/Core.cpp
        src/Camera.cpp
        src/ShaderManager.cpp
        src/Animation.cpp
        src/Animation_RubikCubeMoves.cpp
        src/TextureManager.cpp
        src/ObjectLoader.cpp
        src/Resolver.cpp
        src/Skybox.cpp
        )

set(HEADERS
        inc/Core.hpp
        inc/Camera.hpp
        inc/ShaderManager.hpp
        inc/Constant.hpp
        inc/Animation.hpp
        inc/TextureManager.hpp
        inc/ObjectLoader.hpp
        inc/Resolver.hpp
        inc/Skybox.hpp
        inc/stb_image.h
        )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(rubik ${SOURCES} ${HEADERS})
target_link_libraries(rubik ${CMAKE_SOURCE_DIR}/algo/target/release/libalgo.a "-framework Security")

# Adding GLI and GLM header only library
include_directories(lib/)

# Adding GLFW for build
add_subdirectory(lib/GLFW)

target_link_libraries(rubik glfw ${GLFW_LIBRARIES})

if (APPLE)
    target_link_libraries(rubik "-framework OpenGL")
endif()

if (UNIX)
    find_package(OpenGL REQUIRED)
    target_link_libraries(rubik ${OPENGL_LIBRARY})
endif()
