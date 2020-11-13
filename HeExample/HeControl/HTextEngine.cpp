#include "HTextEngine_p.h"
#include <QtCore/QTemporaryFile>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLTexture>
#include <QtGui/QOpenGLBuffer>
#include <QtCore/QDebug>

HE_CONTROL_BEGIN_NAMESPACE

HTextEnginePrivate::HTextEnginePrivate()
{
    funcs = QOpenGLContext::currentContext()->functions();
}

HCharacter *HTextEnginePrivate::findCharacter(QChar key)
{
    if (characterCache.contains(key))
        return characterCache.value(key);

    funcs->glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    if (FT_Load_Char(ftFace, key.unicode(), FT_LOAD_RENDER))
    {
        qDebug() << "ERROR::FREETYTPE: Failed to load Glyph " << QString(key);
        funcs->glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        return nullptr;
    }

    auto glyph = ftFace->glyph;
    auto bitmap = glyph->bitmap;
    auto character = new HCharacter();
    character->Size = QSize(bitmap.width, bitmap.rows);
    character->Bearing = QPoint(glyph->bitmap_left, glyph->bitmap_top);
    character->Advance = glyph->advance.x;
    character->Texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
    character->Texture->setSize(bitmap.width, bitmap.rows);
    character->Texture->setFormat(QOpenGLTexture::R8_UNorm);
    character->Texture->setWrapMode(QOpenGLTexture::ClampToEdge);
    character->Texture->setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);
    character->Texture->allocateStorage();
    character->Texture->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, bitmap.buffer);
    characterCache.insert(key, character);
    funcs->glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    return character;
}

HTextEngine::HTextEngine(QObject *parent) :
    QObject(parent),
    d_ptr(new HTextEnginePrivate)
{
}

HTextEngine::HTextEngine(HTextEnginePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HTextEngine::~HTextEngine()
{
    clear();
    if (d_ptr->ftLib != nullptr)
        FT_Done_FreeType(d_ptr->ftLib);
    if (d_ptr->vbo != nullptr)
        d_ptr->vbo->destroy();
    d_ptr->vao.destroy();
}

bool HTextEngine::setFont(const QString &fontName, int pixelSize)
{
    if (fontName == d_ptr->fontName && pixelSize == d_ptr->pixelSize)
        return true;

    if (!initialize())
        return false;

    clear();
    bool b = false;
    QString fileName = fontName;
    QTemporaryFile *file = nullptr;
    if (fontName.startsWith(":/"))
    {
        file = QTemporaryFile::createNativeFile(fontName);
        file->open();
        fileName = file->fileName();
    }

    if (FT_New_Face(d_ptr->ftLib, fileName.toStdString().c_str(), 0, &d_ptr->ftFace) == 0)
    {
        FT_Set_Pixel_Sizes(d_ptr->ftFace, 0, 64);
        FT_Select_Charmap(d_ptr->ftFace, FT_ENCODING_UNICODE);
        d_ptr->fontName = fontName;
        d_ptr->pixelSize = pixelSize;
        b = true;
    }
    else
        qDebug() << "ERROR::FREETYPE: Failed to load font";

    if (file)
    {
        file->close();
        delete file;
    }

    return b;
}

void HTextEngine::render(const QString &text, QVector2D position, int pixelSize, int space)
{
    if (!d_ptr->initialized)
        return;

    auto state  = d_ptr->funcs->glIsEnabled(GL_BLEND);
    auto scale = pixelSize < 1 ? 1.0f : 1.0f * pixelSize / d_ptr->pixelSize;
    auto x = position.x();
    auto y = position.y();
    auto maxH = 0;

    if (state == GL_FALSE)
        d_ptr->funcs->glEnable(GL_BLEND);
    d_ptr->funcs->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    QOpenGLVertexArrayObject::Binder binder(&d_ptr->vao);
    for (auto c : text)
    {
        if (c == '\n')
        {
            x = position.x();
            y -= space * scale + maxH;
            continue;
        }

        auto ch = d_ptr->findCharacter(c);
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
            ch->Texture->bind(0);
            d_ptr->vbo->bind();
            d_ptr->vbo->write(0, vertices, sizeof(vertices));
            d_ptr->funcs->glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch->Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    if (state == GL_FALSE)
        d_ptr->funcs->glDisable(GL_BLEND);
}

bool HTextEngine::initialize()
{
    if (d_ptr->initialized)
        return true;
    if (FT_Init_FreeType(&d_ptr->ftLib))
    {
        qDebug() << "FREETYPE: Could not init FreeType Library";
        return false;
    }

    QOpenGLVertexArrayObject::Binder binder(&d_ptr->vao);
    d_ptr->vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    d_ptr->vbo->create();
    d_ptr->vbo->bind();
    d_ptr->vbo->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    d_ptr->vbo->allocate(sizeof(float) * 6 * 4);
    d_ptr->funcs->glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    d_ptr->funcs->glEnableVertexAttribArray(0);
    d_ptr->initialized = true;
    return true;
}

void HTextEngine::clear()
{
    qDeleteAll(d_ptr->characterCache);
    d_ptr->characterCache.clear();
    if (d_ptr->ftFace != nullptr)
        FT_Done_Face(d_ptr->ftFace);
}

HE_CONTROL_END_NAMESPACE
