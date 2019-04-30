/***************************************************************************************************
**      2019-04-28  HAdjustDetailWidget 调整数据窗口部件
***************************************************************************************************/

#ifndef HADJUSTDETAILWIDGET_H
#define HADJUSTDETAILWIDGET_H

#include "IItemDetailWidget.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IAdjustCollection;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HAdjustDetailWidgetPrivate;

class HAdjustDetailWidget : public IItemDetailWidget
{
    Q_OBJECT

public:
    explicit HAdjustDetailWidget(QWidget *parent = nullptr);
    ~HAdjustDetailWidget();

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
    void setData(IAdjustCollection *);

protected:
    void clearData();
    void showData();
    void editData();

protected:
    QScopedPointer<HAdjustDetailWidgetPrivate> d_ptr;

private:
    void init();
};

HE_GUI_END_NAMESPACE

#endif // HADJUSTDETAILWIDGET_H
