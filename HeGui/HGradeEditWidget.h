/***************************************************************************************************
**      2019-04-30  HGradeEditWidget 分级数据编辑窗体。
***************************************************************************************************/

#ifndef HGRADEEDITWIDGET_H
#define HGRADEEDITWIDGET_H

#include "IDataEditWidget.h"
#include "HeData/HDataGlobal.h"

namespace Ui {
class HGradeEditWidget;
}

HE_DATA_BEGIN_NAMESPACE
class IGrade;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HGradeEditWidgetPrivate;

class HGradeEditWidget : public IDataEditWidget<IGrade>
{
    Q_OBJECT

public:
    explicit HGradeEditWidget(QWidget *parent = nullptr);
    ~HGradeEditWidget() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    IGrade *createData() override;
    void setData(IGrade *) override;
    void clearData() override;
    void saveData() override;
    void showData() override;

protected:
    bool editData(const QString &type);
    void showConfig();
    void showPreview();

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    QScopedPointer<HGradeEditWidgetPrivate> d_ptr;
    Ui::HGradeEditWidget *ui;
};

HE_GUI_END_NAMESPACE

#endif // HGRADEEDITWIDGET_H
