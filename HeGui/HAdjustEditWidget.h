/***************************************************************************************************
**      2019-04-30  HAdjustEditWidget 调整数据编辑窗体。
***************************************************************************************************/

#ifndef HADJUSTEDITWIDGET_H
#define HADJUSTEDITWIDGET_H

#include "IDataEditWidget.h"
#include "HeData/HDataGlobal.h"

namespace Ui {
class HAdjustEditWidget;
}

HE_DATA_BEGIN_NAMESPACE
class IAdjust;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HAdjustEditWidgetPrivate;

class HAdjustEditWidget : public IDataEditWidget<IAdjust>
{
    Q_OBJECT

public:
    explicit HAdjustEditWidget(QWidget *parent = nullptr);
    ~HAdjustEditWidget();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    IAdjust *createData() override;
    void setData(IAdjust *) override;
    void clearData() override;
    void saveData() override;
    void showData() override;
    void setTestData(QStringList value);

public:
    QStringList selecteds();

protected:
    void initSelected();

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    void init();

private:
    QScopedPointer<HAdjustEditWidgetPrivate> d_ptr;
    Ui::HAdjustEditWidget *ui;
};

HE_GUI_END_NAMESPACE

#endif // HADJUSTEDITWIDGET_H
