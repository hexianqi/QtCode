#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HQualityItemCollectionWidget;
}

HE_BEGIN_NAMESPACE

class IQualityItemCollection;
class HQualityItemCollectionPrivate;

class HQualityItemCollectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HQualityItemCollectionWidget(QWidget *parent = nullptr);
    ~HQualityItemCollectionWidget();

public:
    void setOptional(QStringList);
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

HE_END_NAMESPACE
