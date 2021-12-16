#include "HBreakoutWidget_p.h"
#include "HGameManager.h"
#include <QtCore/QTimer>
#include <QtGui/QOpenGLFunctions_3_3_Core>

HE_BEGIN_NAMESPACE

HBreakoutWidget::HBreakoutWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    d_ptr(new HBreakoutWidgetPrivate)
{
}

HBreakoutWidget::~HBreakoutWidget()
{
}

void HBreakoutWidget::keyPressEvent(QKeyEvent *event)
{
    d_ptr->game->handleKeyPressEvent(event);
}

void HBreakoutWidget::keyReleaseEvent(QKeyEvent *event)
{
    d_ptr->game->handleKeyReleaseEvent(event);
}

void HBreakoutWidget::initializeGL()
{
    d_ptr->funcs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    d_ptr->funcs->initializeOpenGLFunctions();
    d_ptr->funcs->glClearColor(0.1, 0.1, 0.1, 1);
    d_ptr->funcs->glEnable(GL_BLEND);
    d_ptr->funcs->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    d_ptr->game = new HGameManager(this);
    d_ptr->game->init(800, 600);
    d_ptr->timer = new QTimer(this);
    connect(d_ptr->timer, &QTimer::timeout, this, QOverload<>::of(&HBreakoutWidget::update));
    connect(this, &HBreakoutWidget::frameSwapped, d_ptr->game, &HGameManager::update);
    d_ptr->timer->start(18);
}

void HBreakoutWidget::resizeGL(int w, int h)
{
    d_ptr->funcs->glViewport(0, 0, w, h);
}

void HBreakoutWidget::paintGL()
{
    d_ptr->game->render();
}

HE_END_NAMESPACE
