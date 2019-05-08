/***************************************************************************************************
**      2019-05-06  HQualityEditWidget 品质数据编辑窗体。
***************************************************************************************************/

#ifndef HQUALITYEDITWIDGET_H
#define HQUALITYEDITWIDGET_H

#include "IDataEditWidget.h"
#include "HeData/IQuality.h"

namespace Ui {
class HQualityEditWidget;
}

HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HQualityEditWidgetPrivate;

class HQualityEditWidget : public IDataEditWidget<IQuality>
{
    Q_OBJECT

public:
    explicit HQualityEditWidget(QWidget *parent = nullptr);
    ~HQualityEditWidget();

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
    void initSelected(IQuality::QualityType type);
    void showTable(IQuality::QualityType type);
    void saveTable(IQuality::QualityType type);
    void addItem(IQuality::QualityType type);
    void removeItem(IQuality::QualityType type);
    void editColor(IQuality::QualityType type, int row, int column);

protected slots:
    void on_pushButton_01_clicked();
    void on_pushButton_02_clicked();
    void on_pushButton_03_clicked();
    void on_pushButton_04_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_21_clicked();
    void on_pushButton_22_clicked();
    void on_tableWidget_11_cellDoubleClicked(int row, int column);
    void on_tableWidget_21_cellDoubleClicked(int row, int column);

private:
    void init();

private:
    QScopedPointer<HQualityEditWidgetPrivate> d_ptr;
    Ui::HQualityEditWidget *ui;
};

HE_GUI_END_NAMESPACE

#endif // HQUALITYEDITWIDGET_H
