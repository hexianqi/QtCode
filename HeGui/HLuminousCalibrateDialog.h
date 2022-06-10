/***************************************************************************************************
**      2020-05-26  HLuminousCalibrateDialog 光校准对话框。
***************************************************************************************************/

#pragma once

#include "HeCore/HActionType.h"
#include <QtWidgets/QDialog>

namespace Ui {
class HLuminousCalibrateDialog;
}

class QTreeWidgetItem;

HE_BEGIN_NAMESPACE

class ILuminousCalibrate;
class ILuminousCalibrateItem;
class HLuminousCalibrateDialogPrivate;

class HLuminousCalibrateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HLuminousCalibrateDialog(QWidget *parent = nullptr);
    ~HLuminousCalibrateDialog() override;

protected slots:
    void on_treeWidget_itemSelectionChanged();
    void on_pushButton_1_clicked();
    void on_checkBox_clicked(bool b);
    void handleAction(HActionType action);
    void setOutputCurrent(double value);
    void setGears(int value);
    void setTest(bool b);

protected:
    void done(int result) override;
    QTreeWidgetItem *createItem(const QString &text, int value, QTreeWidgetItem *parent);
    void createItem(ILuminousCalibrate *data, int &value, QTreeWidgetItem *parent);
    void addStackedWidget(ILuminousCalibrateItem *data, QString type);

private:
    void init();

private:
    QScopedPointer<HLuminousCalibrateDialogPrivate> d_ptr;
    Ui::HLuminousCalibrateDialog *ui;
};

HE_END_NAMESPACE

