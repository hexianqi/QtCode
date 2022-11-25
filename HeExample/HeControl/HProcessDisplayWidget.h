/***************************************************************************************************
**      2022-11-22  HProcessDisplayWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HProcessDisplayWidgetPrivate;

class HProcessDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HProcessDisplayWidget(QWidget *parent = nullptr);
    ~HProcessDisplayWidget() override;

public:
    void setProcess(const QStringList &);
    void setCurrentStep(int);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawSmallCircle(QPainter * , int x, int y,int radius,const QColor &color,const QString &text);

protected:
    QScopedPointer<HProcessDisplayWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE
