/***************************************************************************************************
**      2019-10-21  HElecCalibrateDialog 电校准对话框。
***************************************************************************************************/

#ifndef HELECCALIBRATEDIALOG_H
#define HELECCALIBRATEDIALOG_H

#include "HGuiGlobal.h"
#include "HeCore/HActionType.h"
#include "HeData/HDataType.h"
#include <QtWidgets/QDialog>

namespace Ui {
class HElecCalibrateDialog;
}

class QTreeWidgetItem;

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE
class IElecCalibrate;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

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
    void setLoop(HElecType type, bool loop);

protected:
    void done(int result) override;
    QTreeWidgetItem *createItem(QString text, int value, QTreeWidgetItem *parent);
    void createItem(IElecCalibrate *data, HElecType type, int &value, QTreeWidgetItem *parent);

private:
    void init();

private:
    QScopedPointer<HElecCalibrateDialogPrivate> d_ptr;
    Ui::HElecCalibrateDialog *ui;
};

HE_GUI_END_NAMESPACE

#endif // HELECCALIBRATEDIALOG_H
