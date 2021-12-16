/***************************************************************************************************
**      2020-10-14  HOpenGLHelper 帮助类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"

class QString;
class QStringList;

HE_BEGIN_NAMESPACE

class HOpenGLHelper
{
public:
    static unsigned int loadTexture(const QString &fileName, bool gamma = false);
    static unsigned int loadTextureFromHdr(const QString &fileName);
    static unsigned int createTexture(int width, int height);
    static unsigned int createTextureDepth(int width, int height);
    static unsigned int createTextureF(int width, int height);
    static unsigned int loadCubemap(const QStringList &fileNames);
    static unsigned int createCubemap(int width, int height, int magFilter = 0x2601);
    static unsigned int createCubemapDepth(int width, int height);
    static unsigned int createRenderDepth(int width, int height);
};

HE_END_NAMESPACE

