/***************************************************************************************************
**      2022-06-21  HAbstractPrintSettingDialog
***************************************************************************************************/

#pragma once

#include "IPrintSettingDialog.h"

HE_BEGIN_NAMESPACE

class HAbstractPrintSettingDialogPrivate;

class HAbstractPrintSettingDialog : public IPrintSettingDialog
{
    Q_OBJECT

public:
    explicit HAbstractPrintSettingDialog(QWidget *parent = nullptr);
    ~HAbstractPrintSettingDialog() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;

public:
    void setPrintTemplate(IPrintTemplate *) override;

protected:
    HAbstractPrintSettingDialog(HAbstractPrintSettingDialogPrivate &p, QWidget *parent = nullptr);

protected:
    void done(int result) override;
    virtual void showData() = 0;
    virtual void saveData() = 0;

protected:
    QScopedPointer<HAbstractPrintSettingDialogPrivate> d_ptr;
};

HE_END_NAMESPACE

