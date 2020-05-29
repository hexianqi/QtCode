/***************************************************************************************************
**      2020-05-27  HLuminousCalibrateItemWidget 光校准配置窗体。
***************************************************************************************************/

#pragma once

#include "HGuiGlobal.h"
#include "HeData/HDataType.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HLuminousCalibrateItemWidget;
}

HE_DATA_BEGIN_NAMESPACE
class ILuminousCalibrateItem;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HLuminousCalibrateItemWidgetPrivate;

class HLuminousCalibrateItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HLuminousCalibrateItemWidget(QWidget *parent = nullptr);
    ~HLuminousCalibrateItemWidget() override;

signals:
    void gearsChanged(int gears);

public:
    QString type();
    void setData(ILuminousCalibrateItem *data, QString type);
    void updateData(double value, int gears);
    void showData();
    void saveData(int gears);

protected slots:
    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

protected:
    void initWidget();

private:
    QScopedPointer<HLuminousCalibrateItemWidgetPrivate> d_ptr;
    Ui::HLuminousCalibrateItemWidget *ui;
};

HE_GUI_END_NAMESPACE

