#include "HDBLoginDialog.h"
#include "ui_HDBLoginDialog.h"
#include "HHelper.h"
#include "HeCore/HAppContext.h"
#include <QtWidgets/QMessageBox>
#include <QtSql/QSqlQuery>

HE_USE_NAMESPACE

HDBLoginDialog::HDBLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HDBLoginDialog)
{
    ui->setupUi(this);
    ui->comboBox->addItem(tr("操作员"), "operator");
    ui->comboBox->addItem(tr("工程师"), "engineer");
    ui->comboBox->addItem(tr("管理员"), "admin");
    setWindowTitle(tr("登录"));
}

HDBLoginDialog::~HDBLoginDialog()
{
    delete ui;
}

void HDBLoginDialog::done(int result)
{
    if (result == QDialog::Accepted)
    {
        auto user = ui->comboBox->currentData().toString();
        auto password = ui->lineEdit->text();
        QSqlQuery sql(HHelper::mysql);
        sql.exec(QString("select id from userinfo where usercode='%1' and userkey='%2' ").arg(user, password));
        if (!sql.next())
        {
            QMessageBox::information(this, tr("提示"), tr("用户名密码错误！请重新输入。"));
            return;
        }
        HAppContext::setContextValue("Authority", user);
        HAppContext::setContextValue("User", ui->comboBox->currentText());
    }
    QDialog::done(result);
}
