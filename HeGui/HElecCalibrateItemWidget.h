/***************************************************************************************************
**      2019-10-21  HElecCalibrateItemWidget 电校准配置窗体。
***************************************************************************************************/

#ifndef HELECCALIBRATEITEMWIDGET_H
#define HELECCALIBRATEITEMWIDGET_H

#include "HGuiGlobal.h"
#include "HeData/HDataType.h"
#include <QtWidgets/QWidget>

HE_DATA_BEGIN_NAMESPACE
class IElecCalibrateItem;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

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

HE_GUI_END_NAMESPACE

#endif // HELECCALIBRATEITEMWIDGET_H
