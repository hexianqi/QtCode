/***************************************************************************************************
**      2019-05-06  HQualityEditWidget 品质数据编辑窗体。
***************************************************************************************************/

#ifndef HQUALITYEDITWIDGET_H
#define HQUALITYEDITWIDGET_H

#include "IDataEditWidget.h"
#include "HeData/HDataGlobal.h"

namespace Ui {
class HQualityEditWidget;
}

HE_DATA_BEGIN_NAMESPACE
class IQuality;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HQualityEditWidgetPrivate;

class HQualityEditWidget : public IDataEditWidget<IQuality>
{
    Q_OBJECT

public:
    explicit HQualityEditWidget(QWidget *parent = nullptr);
    ~HQualityEditWidget() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    IQuality *createData() override;
    void setData(IQuality *) override;
    void clearData() override;
    void saveData() override;
    void showData() override;

protected:
    void showPushButton();

protected slots:
    void on_pushButton_01_clicked();
    void on_pushButton_02_clicked();
    void on_pushButton_03_clicked();
    void on_pushButton_04_clicked();

private:
    void init();

private:
    QScopedPointer<HQualityEditWidgetPrivate> d_ptr;
    Ui::HQualityEditWidget *ui;
};

HE_GUI_END_NAMESPACE

#endif // HQUALITYEDITWIDGET_H
