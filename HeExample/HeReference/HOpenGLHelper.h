/***************************************************************************************************
**      2020-10-14  HOpenGLHelper 帮助类。
***************************************************************************************************/

#pragma once

#include "HReferenceGlobal.h"

class QStringList;

HE_REFERENCE_BEGIN_NAMESPACE

class HOpenGLHelper
{
public:
    static unsigned int loadTexture(const QString &fileName, bool gamma = false);
    static unsigned int loadCubemap(const QStringList &fileNames);
};

HE_REFERENCE_END_NAMESPACE

