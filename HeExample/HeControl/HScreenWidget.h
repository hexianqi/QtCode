/***************************************************************************************************
**      2020-01-02  HScreenWidget 截屏控件
**                  https://gitee.com/feiyangqingyun/QWidgetDemo
**                  1:支持鼠标右键选择菜单
**                  2:支持全局截屏和局部截屏
**                  3:支持图片另存为
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QDialog>

HE_BEGIN_NAMESPACE

class HScreenWidgetPrivate;

class HScreenWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HScreenWidget(QWidget *parent = nullptr);
    ~HScreenWidget() override;

protected:
    HScreenWidget(HScreenWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void contextMenuEvent(QContextMenuEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void showEvent(QShowEvent *) override;

protected slots:
    void saveScreen();
    void saveFullScreen();
    void saveAsScreen();
    void saveAsFullScreen();

protected:
    QScopedPointer<HScreenWidgetPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
