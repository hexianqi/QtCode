/***************************************************************************************************
**      2020-12-22  HBreakoutWidget
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QOpenGLWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HBreakoutWidgetPrivate;

class HE_CONTROL_EXPORT HBreakoutWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit HBreakoutWidget(QWidget *parent = nullptr);
    ~HBreakoutWidget() override;

protected:
    void keyPressEvent(QKeyEvent *) override;
    void keyReleaseEvent(QKeyEvent *) override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

protected:
    QScopedPointer<HBreakoutWidgetPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

