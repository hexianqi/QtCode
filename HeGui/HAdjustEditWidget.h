/***************************************************************************************************
**      2019-04-30  HAdjustEditWidget 调整数据编辑窗体。
***************************************************************************************************/

#pragma once

#include "IDataEditer.h"
#include "HeCore/HActionType.h"
#include "HeData/HDataGlobal.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HAdjustEditWidget;
}

HE_DATA_BEGIN_NAMESPACE
class IAdjust;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HAdjustEditWidgetPrivate;

class HAdjustEditWidget : public QWidget, public IDataEditer<IAdjust>
{
    Q_OBJECT

public:
    explicit HAdjustEditWidget(QWidget *parent = nullptr);
    ~HAdjustEditWidget() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    QWidget *widget() override;
    IAdjust *createData() override;
    void setData(IAdjust *) override;
    void clearData() override;
    void saveData() override;
    void showData() override;

protected:
    void handleAction(HActionType action);
    void handleStateChanged(bool b);
    void handleResultChanged();

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    void init();
    void initSelected();

private:
    QScopedPointer<HAdjustEditWidgetPrivate> d_ptr;
    Ui::HAdjustEditWidget *ui;
};

HE_GUI_END_NAMESPACE
