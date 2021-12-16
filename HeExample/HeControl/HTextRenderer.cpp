#include "HTextRenderer_p.h"
#include "HTextEngine.h"
#include <QtGui/QOpenGLShaderProgram>

HE_BEGIN_NAMESPACE

HTextRenderer::HTextRenderer(QOpenGLShaderProgram *shader, QObject *parent) :
    HAbstractRenderer(*new HTextRendererPrivate, shader, parent)
{
    Q_D(HTextRenderer);
    d->engine = new HTextEngine(this);
}

HTextRenderer::~HTextRenderer() = default;

bool HTextRenderer::setFont(const QString &fileName, int pixelSize)
{
    Q_D(HTextRenderer);
    return d->engine->setFont(fileName, pixelSize);
}

void HTextRenderer::draw(const QString &text, QVector2D position, int pixelSize, QVector3D color)
{
    Q_D(HTextRenderer);
    d->shader->bind();
    d->shader->setUniformValue("color", color);
    d->engine->render(text, position, pixelSize);
}

HE_END_NAMESPACE
