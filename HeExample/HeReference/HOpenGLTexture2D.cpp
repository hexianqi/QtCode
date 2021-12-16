#include "HOpenGLTexture2D_p.h"

HE_BEGIN_NAMESPACE

HOpenGLTexture2D::HOpenGLTexture2D() :
    d_ptr(new HOpenGLTexture2DPrivate)
{
    glGenTextures(1, &d_ptr->textureID);
}

HOpenGLTexture2D::~HOpenGLTexture2D()
{
    glDeleteTextures(1, &d_ptr->textureID);
}

unsigned int HOpenGLTexture2D::textureID()
{
    return d_ptr->textureID;
}

void HOpenGLTexture2D::setFormat(unsigned int internalFormat, unsigned imageFormat)
{
    d_ptr->internalFormat = internalFormat;
    d_ptr->imageFormat = imageFormat;
}

void HOpenGLTexture2D::generate(unsigned int width, unsigned int height, unsigned char *data)
{
    d_ptr->width = width;
    d_ptr->height = height;
    // create Texture
    glBindTexture(GL_TEXTURE_2D, d_ptr->textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, d_ptr->internalFormat, width, height, 0, d_ptr->imageFormat, GL_UNSIGNED_BYTE, data);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, d_ptr->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, d_ptr->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, d_ptr->minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, d_ptr->magFilter);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void HOpenGLTexture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, d_ptr->textureID);
}

void HOpenGLTexture2D::bind(uint unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, d_ptr->textureID);
}

HE_END_NAMESPACE
