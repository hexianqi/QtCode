/***************************************************************************************************
**      2019-12-20  HShadeWidget 遮罩层。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HShadeWidgetPrivate;

class HShadeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HShadeWidget(QWidget *parent = nullptr);
    ~HShadeWidget() override;

public:
    void addWatched(QWidget *);
    void setBackground(const QColor &value);
    void setOpacity(double value);

protected:
    HShadeWidget(HShadeWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *, QEvent *) override;
    void showEvent(QShowEvent *) override;

protected:
    QScopedPointer<HShadeWidgetPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
