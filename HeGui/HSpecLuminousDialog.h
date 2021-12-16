/***************************************************************************************************
**      2020-03-23  HSpecLuminousDialog 光谱光通量调整对话框。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QDialog>

namespace Ui {
class HSpecLuminousDialog;
}

HE_BEGIN_NAMESPACE

class HSpecLuminous;
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

HE_END_NAMESPACE
