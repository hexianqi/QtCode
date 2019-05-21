/***************************************************************************************************
**      2019-05-20  HChromatismEditWidget 色容差数据编辑窗体。
***************************************************************************************************/

#ifndef HCHROMATISMEDITWIDGET_H
#define HCHROMATISMEDITWIDGET_H

#include "IDataEditWidget.h"
#include "HeData/HDataGlobal.h"

namespace Ui {
class HChromatismEditWidget;
}

HE_DATA_BEGIN_NAMESPACE
class IChromatism;
class IChromatismItem;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HChromatismEditWidgetPrivate;

class HChromatismEditWidget : public IDataEditWidget<IChromatism>
{
    Q_OBJECT

public:
    explicit HChromatismEditWidget(QWidget *parent = nullptr);
    ~HChromatismEditWidget();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
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
    void showTable(int row, QString key, IChromatismItem *value);

private:
    QScopedPointer<HChromatismEditWidgetPrivate> d_ptr;
    Ui::HChromatismEditWidget *ui;
};

HE_GUI_END_NAMESPACE

#endif // HCHROMATISMEDITWIDGET_H
