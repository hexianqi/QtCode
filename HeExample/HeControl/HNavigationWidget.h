/***************************************************************************************************
**      2019-12-06  HNavigationWidget 导航栏窗体。
**                  http://www.qtcn.org/bbs/read-htm-tid-65128.html
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HNavigationWidgetPrivate;

class HNavigationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNavigationWidget(QWidget *parent = nullptr);
    ~HNavigationWidget() override;

signals:
    void currentItemChanged(int index);

public:
    void addItem(const QString &value);
    void setWidth(int value);
    void setRowHeight(int value);
    void setBackground(const QColor &value);
    void setSelectColor(const QColor &value);

protected:
    HNavigationWidget(HNavigationWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;

protected:
    QScopedPointer<HNavigationWidgetPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
