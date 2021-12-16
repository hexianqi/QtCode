/***************************************************************************************************
**      2020-12-08  HOpenGLTexture2D
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QScopedPointer>

HE_BEGIN_NAMESPACE

class HOpenGLTexture2DPrivate;

class HOpenGLTexture2D
{
public:
    explicit HOpenGLTexture2D();
    virtual ~HOpenGLTexture2D();

public:
    unsigned int textureID();

public:
    void setFormat(unsigned int internalFormat, unsigned imageFormat);

public:
    void generate(unsigned int width, unsigned int height, unsigned char* data);
    void bind();
    void bind(uint unit);

protected:
    QScopedPointer<HOpenGLTexture2DPrivate> d_ptr;
};

HE_END_NAMESPACE

