#pragma once

#include "HFreeType.h"
#include <ft2build.h>
#include <freetype/freetype.h>
#include <QtCore/QSize>
#include <QtCore/QHash>


HE_REFERENCE_BEGIN_NAMESPACE

struct HCharacter
{
    unsigned int TextureID; // ID handle of the glyph texture
    QSize Size;             // Size of glyph
    QPoint Bearing;          // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class HFreeTypePrivate
{
public:
    FT_Library ftLib = nullptr;
    FT_Face ftFace = nullptr;
    bool initialized = false;
    QString fontName;
    int pixelSize = 12;
    unsigned int vao = 0;
    unsigned int vbo = 0;
    QHash<QChar, HCharacter *> characterCache;
};

HE_REFERENCE_END_NAMESPACE

