/***************************************************************************************************
**      2019-05-20  HChromatismEditWidget 色容差数据编辑窗体。
***************************************************************************************************/

#pragma once

#include "IDataEditer.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HChromatismEditWidget;
}

HE_BEGIN_NAMESPACE

class IChromatism;
class IChromatismItem;
class HChromatismEditWidgetPrivate;

class HChromatismEditWidget : public QWidget, public IDataEditer<IChromatism>
{
    Q_OBJECT

public:
    explicit HChromatismEditWidget(QWidget *parent = nullptr);
    ~HChromatismEditWidget();

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    QWidget *widget() override;
    IChromatism *createData() override;
    void setData(IChromatism *) override;
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
    void showTable(int row, const QString &key, IChromatismItem *value);

private:
    QScopedPointer<HChromatismEditWidgetPrivate> d_ptr;
    Ui::HChromatismEditWidget *ui;
};

HE_END_NAMESPACE
