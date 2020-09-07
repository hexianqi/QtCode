/***************************************************************************************************
**      2020-09-04  HOpenGLWidget_1
***************************************************************************************************/

#pragma once

#include "HReferenceGlobal.h"
#include <QtWidgets/QOpenGLWidget>

HE_REFERENCE_BEGIN_NAMESPACE

class HOpenGLWidget_1Private;

class HE_REFERENCE_EXPORT HOpenGLWidget_1 : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit HOpenGLWidget_1(QWidget *parent = nullptr);
    ~HOpenGLWidget_1() override;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

protected:
    QScopedPointer<HOpenGLWidget_1Private> d_ptr;

private:
    void init();
    void rotate();
};

HE_REFERENCE_END_NAMESPACE

