#include "HTextRenderer_p.h"
#include "HOpenGLShaderProgram.h"
#include "HFreeType.h"

HE_REFERENCE_BEGIN_NAMESPACE

HTextRenderer::HTextRenderer(HOpenGLShaderProgram *shader, QObject *parent) :
    QObject(parent),
    d_ptr(new HTextRendererPrivate)
{
    d_ptr->shader = shader;
    d_ptr->freeType = new HFreeType(this);
}

HTextRenderer::~HTextRenderer()
{
}

bool HTextRenderer::setFont(const QString &fileName, int pixelSize)
{
    return d_ptr->freeType->setFont(fileName, pixelSize);
}

void HTextRenderer::draw(const QString &text, QVector2D position, int pixelSize, QVector3D color)
{
    d_ptr->shader->bind();
    d_ptr->shader->setUniformValue("color", color);
    d_ptr->freeType->renderText(text, position, pixelSize);
}

HE_REFERENCE_END_NAMESPACE
