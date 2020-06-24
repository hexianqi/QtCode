/***************************************************************************************************
**      2020-06-12  HFFmpegWidget 实时视频显示窗体类。
**                  https://gitee.com/feiyangqingyun/QWidgetDemo
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HFFmpegWidgetPrivate;

class HFFmpegWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HFFmpegWidget(QWidget *parent = nullptr);
    ~HFFmpegWidget() override;

public slots:
    void setUrl(const QString &value);
    void open();
    void pause();
    void next();
    void close();
    void clear();

protected:
    HFFmpegWidget(HFFmpegWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;

protected slots:
    void updateImage(const QImage &);

protected:
    QScopedPointer<HFFmpegWidgetPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

