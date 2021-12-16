#pragma once

#include "HTextEngine.h"
#include <ft2build.h>
#include <freetype/freetype.h>
#include <QtCore/QSize>
#include <QtCore/QHash>
#include <QtGui/QOpenGLVertexArrayObject>

class QOpenGLFunctions;
class QOpenGLBuffer;
class QOpenGLTexture;

HE_BEGIN_NAMESPACE

struct HCharacter
{
    QOpenGLTexture *Texture;    // Glyph texture
    QSize Size;                 // Size of glyph
    QPoint Bearing;             // Offset from baseline to left/top of glyph
    unsigned int Advance;       // Horizontal offset to advance to next glyph
};

class HTextEnginePrivate
{
public:
    HTextEnginePrivate();

public:
    HCharacter *findCharacter(QChar key);

public:
    QOpenGLFunctions *funcs;
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer *vbo = nullptr;

public:
    FT_Library ftLib = nullptr;
    FT_Face ftFace = nullptr;
    bool initialized = false;
    QString fontName;
    int pixelSize = 64;
    QHash<QChar, HCharacter *> characterCache;
};

HE_END_NAMESPACE

