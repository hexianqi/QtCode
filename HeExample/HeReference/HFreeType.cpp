#include "HFreeType_p.h"
#include "HOpenGLShaderProgram.h"
#include "glad/glad.h"
#include <QtCore/QTemporaryFile>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

HFreeType::HFreeType(QObject *parent) :
    QObject(parent),
    d_ptr(new HFreeTypePrivate)
{
}

HFreeType::HFreeType(HFreeTypePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HFreeType::~HFreeType()
{
    qDeleteAll(d_ptr->characterCache);
    d_ptr->characterCache.clear();
    if (d_ptr->ftFace != nullptr)
        FT_Done_Face(d_ptr->ftFace);
    if (d_ptr->ftLib != nullptr)
        FT_Done_FreeType(d_ptr->ftLib);
}

bool HFreeType::setFont(const QString &fontName, int pixelSize)
{
    if (fontName == d_ptr->fontName && pixelSize == d_ptr->pixelSize)
        return true;

    if (!initialize())
        return false;

    qDeleteAll(d_ptr->characterCache);
    d_ptr->characterCache.clear();
    if (d_ptr->ftFace != nullptr)
        FT_Done_Face(d_ptr->ftFace);

    QString fileName = fontName;
    QTemporaryFile *file = nullptr;
    if (fontName.startsWith(":/"))
    {
        file = QTemporaryFile::createNativeFile(fontName);
        file->open();
        fileName = file->fileName();
    }

    if (FT_New_Face(d_ptr->ftLib, fileName.toStdString().c_str(), 0, &d_ptr->ftFace))
    {
        qDebug() << "ERROR::FREETYPE: Failed to load font";
        return false;
    }

    FT_Set_Pixel_Sizes(d_ptr->ftFace, 0, 64);
    FT_Select_Charmap(d_ptr->ftFace, FT_ENCODING_UNICODE);
    d_ptr->fontName = fontName;
    d_ptr->pixelSize = pixelSize;

    if (file)
    {
        file->close();
        delete file;
    }

    return true;
}

void HFreeType::renderText(const QString &text, QVector2D position, int pixelSize, int space)
{
    if (!d_ptr->initialized)
        return;

    auto scale = pixelSize < 1 ? 1.0f : 1.0f * pixelSize / d_ptr->pixelSize;
    auto x = position.x();
    auto y = position.y();
    auto maxH = 0;
    auto state  = glIsEnabled(GL_BLEND);
    if (state == GL_FALSE)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(d_ptr->vao);
    for (auto c : text)
    {
        if (c == '\n')
        {
            x = position.x();
            y -= space * scale + maxH;
            continue;
        }

        auto ch = findCharacter(c);
        if (ch == nullptr)
            continue;
        if (c != ' ')
        {
            float xpos = x + ch->Bearing.x() * scale;
            float ypos = y - (ch->Size.height() - ch->Bearing.y()) * scale;
            float w = ch->Size.width() * scale;
            float h = ch->Size.height() * scale;
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };
            if (ch->Size.height() > maxH)
                maxH = ch->Size.height();
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch->TextureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, d_ptr->vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch->Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    if (state == GL_FALSE)
        glDisable(GL_BLEND);
}

bool HFreeType::initialize()
{
    if (d_ptr->initialized)
        return true;
    if (FT_Init_FreeType(&d_ptr->ftLib))
    {
        qDebug() << "FREETYPE: Could not init FreeType Library";
        return false;
    }

    glGenVertexArrays(1, &d_ptr->vao);
    glBindVertexArray(d_ptr->vao);
    glGenBuffers(1, &d_ptr->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, d_ptr->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    d_ptr->initialized = true;
    return true;
}

HCharacter *HFreeType::findCharacter(QChar key)
{
    if (d_ptr->characterCache.contains(key))
        return d_ptr->characterCache.value(key);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    if (FT_Load_Char(d_ptr->ftFace, key.unicode(), FT_LOAD_RENDER))
    {
        qDebug() << "ERROR::FREETYTPE: Failed to load Glyph";
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        return nullptr;
    }

    auto glyph = d_ptr->ftFace->glyph;
    auto bitmap = glyph->bitmap;
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, bitmap.width, bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap.buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    auto character = new HCharacter();
    character->TextureID = texture;
    character->Size = QSize(bitmap.width, bitmap.rows);
    character->Bearing = QPoint(glyph->bitmap_left, glyph->bitmap_top);
    character->Advance = glyph->advance.x;
    d_ptr->characterCache.insert(key, character);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    return character;
}

HE_REFERENCE_END_NAMESPACE
