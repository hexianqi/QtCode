#include "HAbstractPrintSettingDialog_p.h"

HE_BEGIN_NAMESPACE

HAbstractPrintSettingDialog::HAbstractPrintSettingDialog(QWidget *parent) :
    IPrintSettingDialog(parent),
    d_ptr(new HAbstractPrintSettingDialogPrivate)
{
}

HAbstractPrintSettingDialog::HAbstractPrintSettingDialog(HAbstractPrintSettingDialogPrivate &p, QWidget *parent) :
    IPrintSettingDialog(parent),
    d_ptr(&p)
{
}

HAbstractPrintSettingDialog::~HAbstractPrintSettingDialog()
{
}

void HAbstractPrintSettingDialog::initialize(QVariantMap /*param*/)
{

}

void HAbstractPrintSettingDialog::setPrintTemplate(IPrintTemplate *p)
{
    d_ptr->printTemplate = p;
    showData();
}

void HAbstractPrintSettingDialog::done(int result)
{
    if (result == QDialog::Accepted)
        saveData();
    QDialog::done(result);
}

HE_END_NAMESPACE
