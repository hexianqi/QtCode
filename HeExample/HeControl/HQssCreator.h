/***************************************************************************************************
**      2019-07-19  HQssCreator Qss样式展示
**                  https://gitee.com/feiyangqingyun/QWidgetDemo
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QMainWindow>

namespace Ui {
class HQssCreator;
}

HE_BEGIN_NAMESPACE

class HQssCreatorPrivate;

class HQssCreator : public QMainWindow
{
    Q_OBJECT

public:
    explicit HQssCreator(QWidget *parent = nullptr);
    ~HQssCreator();

private:
    Ui::HQssCreator *ui;
    QScopedPointer<HQssCreatorPrivate> d_ptr;

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
