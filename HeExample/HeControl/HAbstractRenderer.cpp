#include "HAbstractRenderer_p.h"
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>

HE_BEGIN_NAMESPACE

HAbstractRendererPrivate::HAbstractRendererPrivate()
{
    funcs = QOpenGLContext::currentContext()->functions();
}

HAbstractRenderer::HAbstractRenderer(QOpenGLShaderProgram *shader, QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractRendererPrivate)
{
    d_ptr->shader = shader;
}

HAbstractRenderer::HAbstractRenderer(HAbstractRendererPrivate &p, QOpenGLShaderProgram *shader, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
    d_ptr->shader = shader;
}

HAbstractRenderer::~HAbstractRenderer()
{
    d_ptr->vao.destroy();
}

HE_END_NAMESPACE
