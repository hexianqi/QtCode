/***************************************************************************************************
**      2019-04-22  HGradeDetailWidget 分级数据窗口部件。
***************************************************************************************************/

#ifndef HGRADEDETAILWIDGET_H
#define HGRADEDETAILWIDGET_H

#include "IItemDetailWidget.h"
#include "HeData/HDataGlobal.h"

namespace Ui {
class HGradeDetailWidget;
}

HE_DATA_BEGIN_NAMESPACE
class IGrade;
class IGradeCollection;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HGradeDetailWidgetPrivate;

class HE_GUI_EXPORT HGradeDetailWidget : public IItemDetailWidget
{
    Q_OBJECT

public:
    explicit HGradeDetailWidget(QWidget *parent = nullptr);
    ~HGradeDetailWidget();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void start() override;
    void importFile() override;
    void exportFile() override;
    void addItem(QString name) override;
    void delItem(QString name) override;
    void setCurrentItem(QString name) override;

public:
    void setData(IGradeCollection *);
    void setOptionals(QStringList value);

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

protected:
    void clearData();
    void showData();
    bool editGradeItem(QString type);

protected:
    QScopedPointer<HGradeDetailWidgetPrivate> d_ptr;

private:
    Ui::HGradeDetailWidget *ui;
};

HE_GUI_END_NAMESPACE

#endif // HGRADEDETAILWIDGET_H
