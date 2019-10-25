#ifndef HQUALITYITEMCOLLECTIONWIDGET_H
#define HQUALITYITEMCOLLECTIONWIDGET_H

#include "HGuiGlobal.h"
#include "HeData/HDataGlobal.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HQualityItemCollectionWidget;
}

HE_DATA_BEGIN_NAMESPACE
class IQualityItemCollection;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HQualityItemCollectionPrivate;

class HQualityItemCollectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HQualityItemCollectionWidget(QWidget *parent = nullptr);
    ~HQualityItemCollectionWidget();

public:
    void setData(IQualityItemCollection *);
    void clearData();
    void showData();
    void saveData();

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    void init();
    void initSelected();

private:
    QScopedPointer<HQualityItemCollectionPrivate> d_ptr;
    Ui::HQualityItemCollectionWidget *ui;
};

HE_GUI_END_NAMESPACE

#endif // HQUALITYITEMCOLLECTIONWIDGET_H
