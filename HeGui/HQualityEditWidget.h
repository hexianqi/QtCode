/***************************************************************************************************
**      2019-05-06  HQualityEditWidget 品质数据编辑窗体。
***************************************************************************************************/

#pragma once

#include "IDataEditer.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HQualityEditWidget;
}

HE_BEGIN_NAMESPACE

class IQuality;
class HQualityEditWidgetPrivate;

class HQualityEditWidget : public QWidget, public IDataEditer<IQuality>
{
    Q_OBJECT

public:
    explicit HQualityEditWidget(QWidget *parent = nullptr);
    ~HQualityEditWidget() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    QWidget *widget() override;
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
    void on_pushButton_05_clicked();

private:
    void init();

private:
    QScopedPointer<HQualityEditWidgetPrivate> d_ptr;
    Ui::HQualityEditWidget *ui;
};

HE_END_NAMESPACE
