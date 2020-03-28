/***************************************************************************************************
**      2020-03-23  HSpecLuminousDialog 光谱光通量调整对话框。
***************************************************************************************************/

#ifndef HSPECLUMINOUSDIALOG_H
#define HSPECLUMINOUSDIALOG_H

#include "HGuiGlobal.h"
#include "HeData/HDataGlobal.h"
#include <QtWidgets/QDialog>

HE_DATA_BEGIN_NAMESPACE
class HSpecLuminous;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

namespace Ui {
class HSpecLuminousDialog;
}

HE_GUI_BEGIN_NAMESPACE

class HSpecLuminousDialogPrivate;

class HSpecLuminousDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HSpecLuminousDialog(QWidget *parent = nullptr);
    ~HSpecLuminousDialog() override;

public:
    void setData(HSpecLuminous *);

protected slots:
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();

protected:
    void done(int result) override;
    void showData();
    void saveData();

private:
    void init();

protected:
    QScopedPointer<HSpecLuminousDialogPrivate> d_ptr;

private:
    Ui::HSpecLuminousDialog *ui;
};

HE_GUI_END_NAMESPACE

#endif // HSPECLUMINOUSDIALOG_H
