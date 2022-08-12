/***************************************************************************************************
**      2019-07-19  HQssCreator Qss样式展示
**                  https://gitee.com/feiyangqingyun/QWidgetDemo
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QMainWindow>

namespace Ui {
class HQssStyleWindow;
}

HE_BEGIN_NAMESPACE

class HQssStyleWindowPrivate;

class HQssStyleWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HQssStyleWindow(QWidget *parent = nullptr);
    ~HQssStyleWindow();

private:
    Ui::HQssStyleWindow *ui;
    QScopedPointer<HQssStyleWindowPrivate> d_ptr;

private slots:
    void init();
    void initStyle();
    void initAction();
    void initTableWidget();
    void initTreeWidget();
    void initListWidget();
    void initOther();
    void changeStyle(QAction *);
};

HE_END_NAMESPACE
