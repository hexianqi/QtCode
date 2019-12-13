/***************************************************************************************************
**      2019-06-06  HGifWidget GIF录屏控件
**                  https://gitee.com/feiyangqingyun/QWidgetDemo
**                  1：可设置要录制屏幕的宽高,支持右下角直接拉动改变
**                  2：可设置变宽的宽度
**                  3：可设置录屏控件的背景颜色
**                  4：可设置录制的帧数
**                  5：录制区域可自由拖动选择
***************************************************************************************************/

#ifndef HGIFWIDGET_H
#define HGIFWIDGET_H

#include "HControlGlobal.h"
#include <QtWidgets/QDialog>

namespace Ui {
class HGifWidget;
}

HE_CONTROL_BEGIN_NAMESPACE

class HGifWidgetPrivate;

class HGifWidget : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth)
    Q_PROPERTY(QColor background READ background WRITE setBackground)

public:
    explicit HGifWidget(QWidget *parent = nullptr);
    ~HGifWidget() override;

public slots:
    void setBorderWidth(int);
    void setBackground(QColor);

public:
    int borderWidth() const;
    QColor background() const;

protected:
    void resizeEvent(QResizeEvent *) override;
    void paintEvent(QPaintEvent *) override;

protected:
    void saveImage();
    void closeAll();
    void record();
    void resizeScreenshot();
    void clearWriter();

private:
    void init();

private:
    Ui::HGifWidget *ui;
    QScopedPointer<HGifWidgetPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HGIFWIDGET_H
