/***************************************************************************************************
**      2019-03-22  HSpecPelsWaveWidget 像元波长配置窗体。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HSpecPelsWave;
class HSpecPelsWaveWidgetPrivate;

class HSpecPelsWaveWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HSpecPelsWaveWidget(QWidget *parent = nullptr);
    ~HSpecPelsWaveWidget() override;

public:
    void setData(HSpecPelsWave *);
    void saveData();
    void showData();

protected:
    void setRowCount(int value);

protected:
    QScopedPointer<HSpecPelsWaveWidgetPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
