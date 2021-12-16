#pragma once

#include "HOpenGLTexture2D.h"
#include "glad/glad.h"

HE_BEGIN_NAMESPACE

class HOpenGLTexture2DPrivate
{
public:
    unsigned int textureID = 0;
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int internalFormat = GL_RGB;
    unsigned int imageFormat = GL_RGB;
    unsigned int wrapS = GL_REPEAT;
    unsigned int wrapT = GL_REPEAT;
    unsigned int minFilter = GL_LINEAR;
    unsigned int magFilter = GL_LINEAR;
};

HE_END_NAMESPACE

