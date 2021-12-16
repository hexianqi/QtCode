#include "HLoginDialog.h"
#include "ui_HLoginDialog.h"
#include "HChangePasswordDialog.h"
#include "HGuiHelper.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QSettings>
#include <QtWidgets/QMessageBox>

HE_BEGIN_NAMESPACE

HLoginDialog::HLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HLoginDialog)
{
    ui->setupUi(this);
    readSettings();
}

HLoginDialog::~HLoginDialog()
{
    delete ui;
}

void HLoginDialog::on_pushButton_03_clicked()
{
    HChangePasswordDialog dlg(_password, this);
    if (!dlg.exec())
        return;
    _password = dlg.password();
    writeSettings();
}

void HLoginDialog::done(int result)
{
    if (result == QDialog::Accepted)
    {
        if (ui->lineEdit_01->text().trimmed() != _user || HGuiHelper::encodePassword(ui->lineEdit_02->text()) != _password)
        {
            QMessageBox::critical(this, tr("错误"), tr("用户名密码错误！"), QMessageBox::Ok);
            return;
        }
    }
    QDialog::done(result);
}

void HLoginDialog::readSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("Account");
    _user = settings->value("User", "SongLang").toString();
    _password = settings->value("Password", HGuiHelper::encodePassword("SL!@#$%^")).toString();
    settings->endGroup();
}

void HLoginDialog::writeSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("Account");
    settings->setValue("User", _user);
    settings->setValue("Password", _password);
    settings->endGroup();
}

HE_END_NAMESPACE
