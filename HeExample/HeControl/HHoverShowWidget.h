/***************************************************************************************************
**      2022-11-09  HGeneralControlWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HHoverShowWidgetPrivate;

class HHoverShowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HHoverShowWidget(QWidget *parent = nullptr);
    ~HHoverShowWidget() override;

public:
    QSize sizeHint() const override;

public:
    void setInfoText(const QString &text);

protected:
    HHoverShowWidget(HHoverShowWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void init();

protected:
    QScopedPointer<HHoverShowWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE




