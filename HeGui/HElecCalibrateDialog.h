/***************************************************************************************************
**      2019-10-21  HElecCalibrateDialog 电校准对话框。
***************************************************************************************************/

#pragma once

#include "HeCore/HActionType.h"
#include "HeData/HDataType.h"
#include <QtWidgets/QDialog>

namespace Ui {
class HElecCalibrateDialog;
}

class QTreeWidgetItem;

HE_BEGIN_NAMESPACE

class IElecCalibrate;
class IElecCalibrateItem;
class HElecCalibrateItemWidget;
class HElecCalibrateDialogPrivate;

class HElecCalibrateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HElecCalibrateDialog(QWidget *parent = nullptr);
    ~HElecCalibrateDialog() override;

protected slots:
    void on_treeWidget_itemSelectionChanged();
    void on_pushButton_1_clicked();
    void handleAction(HActionType action);
    void setElec(HElecType type, double value);
    void setGears(HElecType type, int value);
    void setLoop(HElecType type, bool loop);

protected:
    void done(int result) override;
    QTreeWidgetItem *createItem(const QString &text, int value, QTreeWidgetItem *parent);
    void createItem(IElecCalibrate *data, HElecType type, int &value, QTreeWidgetItem *parent);
    HElecCalibrateItemWidget *createItemWidget(HElecType type);
    void addStackedWidget(IElecCalibrateItem *data, HElecType type, int gears);

private:
    void init();

private:
    QScopedPointer<HElecCalibrateDialogPrivate> d_ptr;
    Ui::HElecCalibrateDialog *ui;
};

HE_END_NAMESPACE
