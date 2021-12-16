/***************************************************************************************************
**      2020-11-05  HOpenGLWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QOpenGLWidget>

HE_BEGIN_NAMESPACE

class HOpenGLWidgetPrivate;

class HOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit HOpenGLWidget(QWidget *parent = nullptr);
    ~HOpenGLWidget() override;

public:
    void setDisplay(const QString &);
    void setLineMode(bool b);
    void setLightPosLoop(bool b);
    void setLightColorLoop(bool b);
    void setLinearize(bool b);
    void setBlinn(bool b);
    void setGamma(bool b);
    void setHdr(bool b);
    void setBloom(bool b);
    void setShadows(bool b);
    void setExposure(double value);
    void setHeightScale(double value);

protected:
    HOpenGLWidget(HOpenGLWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

protected:
    QVector3D lightPos();
    QVector3D lightColor();

protected:
    QScopedPointer<HOpenGLWidgetPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE

