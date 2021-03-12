/***************************************************************************************************
**      2019-07-18  HSpliteWidget 分割界面
**                  http://www.qtcn.org/bbs/read-htm-tid-65929-ds-1.html#tpc
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HSpliteWidgetPrivate;

class HSpliteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HSpliteWidget(QWidget *parent = nullptr);
    ~HSpliteWidget() override;

protected:
    HSpliteWidget(HSpliteWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *, QEvent *) override;
    void hideAll();
    void showAll();
    void changeType();
    void showWidget();
    void showWidget(int index, int flag);
    void showWidget6(int index);
    void showWidget8(int index);

protected:
    QScopedPointer<HSpliteWidgetPrivate> d_ptr;

private:
    void init();
    void initLabel();
    void initMenu();
};

HE_CONTROL_END_NAMESPACE
