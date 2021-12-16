#include "HChangePasswordDialog.h"
#include "ui_HChangePasswordDialog.h"
#include "HGuiHelper.h"
#include <QtWidgets/QMessageBox>

HE_BEGIN_NAMESPACE

HChangePasswordDialog::HChangePasswordDialog(QString password, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HChangePasswordDialog)
{
    _password = password;
    ui->setupUi(this);
}

HChangePasswordDialog::~HChangePasswordDialog()
{
    delete ui;
}

QString HChangePasswordDialog::password()
{
    return _password;
}

void HChangePasswordDialog::done(int result)
{
    if (result == QDialog::Accepted)
    {
        if (HGuiHelper::encodePassword(ui->lineEdit_1->text()) != _password)
        {
            QMessageBox::critical(this, tr("错误"), tr("旧密码错误！"), QMessageBox::Ok);
            ui->lineEdit_1->setFocus();
            return;
        }
        if (ui->lineEdit_2->text() != ui->lineEdit_3->text())
        {
            QMessageBox::critical(this, tr("错误"), tr("新密码不相同！"), QMessageBox::Ok);
            ui->lineEdit_2->setFocus();
            return;
        }
        _password = HGuiHelper::encodePassword(ui->lineEdit_2->text());
    }
    QDialog::done(result);
}

HE_END_NAMESPACE
