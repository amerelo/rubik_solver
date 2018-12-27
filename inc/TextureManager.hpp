//
// Created by hjeannin on 28/07/17.
//

#ifndef TEXTURE_HPP
# define TEXTURE_HPP
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
# include <GLM/glm.hpp>
# include <iostream>
# define STB_IMAGE_IMPLEMENTATION
# define STB_IMAGE_STATIC
# include "stb_image.h"
# include <vector>

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    void    generateDefaultTexture(GLuint textureID, GLuint t_width, GLuint t_height);
    void    loadImageFile(GLuint textureID, const char * file, int wanted_bpp = 3);
    void    loadAlphaTexture(GLuint textureID, const char * file);
    void    loadCubemap(GLuint textureID, std::vector<const GLchar*> faces, int wanted_bpp = 3);
    void    loadAtlas(GLuint textureID, char const *filename, int count, int wanted_bpp = 3);
};

#endif // TEXTURE_HPP