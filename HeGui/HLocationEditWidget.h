/***************************************************************************************************
**      2022-01-28
***************************************************************************************************/

#pragma once

#include "IDataEditer.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HLocationEditWidget;
}

HE_BEGIN_NAMESPACE

class ILocation;
class HLocationEditWidgetPrivate;

class HLocationEditWidget : public QWidget, public IDataEditer<ILocation>
{
    Q_OBJECT

public:
    explicit HLocationEditWidget(QWidget *parent = nullptr);
    ~HLocationEditWidget() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    QWidget *widget() override;
    ILocation *createData() override;
    void setData(ILocation *) override;
    void clearData() override;
    void saveData() override;
    void showData() override;

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    void init();

private:
    QScopedPointer<HLocationEditWidgetPrivate> d_ptr;
    Ui::HLocationEditWidget *ui;
};

HE_END_NAMESPACE

