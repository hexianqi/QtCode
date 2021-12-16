/***************************************************************************************************
**      2019-10-21  HElecCalibrateItemWidget 电校准配置窗体。
***************************************************************************************************/

#pragma once

#include "HeData/HDataType.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class IElecCalibrateItem;
class HElecCalibrateItemWidgetPrivate;

class HElecCalibrateItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HElecCalibrateItemWidget(QWidget *parent = nullptr);

signals:
    void elecChanged(HElecType type, double value);
    void loopChanged(HElecType type, bool loop);

public:
    HElecType type();
    int gears();

public:
    void setData(IElecCalibrateItem *, HElecType type, int gears);
    virtual void setLoop(bool b);
    virtual void updateData(double value);
    virtual void showData() = 0;
    virtual void saveData() = 0;

protected:
    HElecCalibrateItemWidget(HElecCalibrateItemWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HElecCalibrateItemWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE
