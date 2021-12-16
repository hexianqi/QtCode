/***************************************************************************************************
**      2020-07-09  HFFmpegSupportWidget 支持信息。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HFFmpegSupportWidgetPrivate;

class HFFmpegSupportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HFFmpegSupportWidget(QWidget *parent = nullptr);
    ~HFFmpegSupportWidget() override;

protected:
    QScopedPointer<HFFmpegSupportWidgetPrivate> d_ptr;

private:
    void init();
    void showInfo();
    void showProtocol();
    void showInputFormat();
    void showOutputFormat();
    void showCodec();
    void showFilter();
    void showBSF();
};

HE_END_NAMESPACE

