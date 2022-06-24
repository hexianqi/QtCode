/***************************************************************************************************
**      2022-06-21  HSpecPrintSettingDialog
***************************************************************************************************/

#pragma once

#include "HAbstractPrintSettingDialog.h"

namespace Ui {
class HSpecPrintSettingDialog;
}

HE_BEGIN_NAMESPACE

class HSpecPrintSettingDialogPrivate;

class HSpecPrintSettingDialog : public HAbstractPrintSettingDialog
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecPrintSettingDialog)

public:
    explicit HSpecPrintSettingDialog(QWidget *parent = nullptr);
    ~HSpecPrintSettingDialog() override;

public:
    QString typeName() override;

protected:
    void showData() override;
    void saveData() override;

private:
    void init();

private:
    Ui::HSpecPrintSettingDialog *ui;
};

HE_END_NAMESPACE

