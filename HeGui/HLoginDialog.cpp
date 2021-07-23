#include "HLoginDialog.h"
#include "ui_HLoginDialog.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HLoginDialog::HLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HLoginDialog)
{
    ui->setupUi(this);
}

HLoginDialog::~HLoginDialog()
{
    delete ui;
}

void HLoginDialog::done(int result)
{
    if (result == QDialog::Accepted)
    {
        _user = ui->lineEdit_01->text().trimmed();
        _password = ui->lineEdit_02->text();
    }
    QDialog::done(result);
}

HE_GUI_END_NAMESPACE
