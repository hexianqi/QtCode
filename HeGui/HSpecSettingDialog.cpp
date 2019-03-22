#include "HSpecSettingDialog_p.h"
#include "ui_HSpecSettingDialog.h"

HE_GUI_BEGIN_NAMESPACE

HeGui::HSpecSettingDialog::HSpecSettingDialog(HSpecSetting *data, QWidget *parent)
    : QDialog(parent), ui(new Ui::HSpecSettingDialog), d_ptr(new HSpecSettingDialogPrivate)
{
    ui->setupUi(this);
    d_ptr->data = data;
    init();
    showData();
}

HSpecSettingDialog::~HSpecSettingDialog()
{
    delete ui;
}

void HSpecSettingDialog::done(int result)
{
    if (result == QDialog::Accepted)
        saveData();
    QDialog::done(result);
}

void HSpecSettingDialog::showData()
{

}

void HSpecSettingDialog::saveData()
{

}

void HSpecSettingDialog::init()
{
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
}

HE_GUI_END_NAMESPACE
