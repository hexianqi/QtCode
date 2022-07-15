#include "frmedtkey.h"
#include "ui_frmedtkey.h"
#include "unitpublic.h"
#include "qsqlquery.h"
#include "qmessagebox.h"
#include "qdebug.h"

Frmedtkey::Frmedtkey(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Frmedtkey)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("修改密码，用户：%1").arg(unitpublic::gsuser));
    ui->edtoldkey->setEchoMode(QLineEdit::Password);
    ui->edtnewkey->setEchoMode(QLineEdit::Password);
    ui->edtverkey->setEchoMode(QLineEdit::Password);
}

Frmedtkey::~Frmedtkey()
{
    delete ui;
}

void Frmedtkey::on_btnno_clicked()
{
    this->close();
}

void Frmedtkey::on_btnok_clicked()
{
    QString skey = ui->edtoldkey->text();
    QSqlQuery mysql(unitpublic::dbmysql);
    QString ssql=QString("select id from userinfo where usercode='%1' and userkey='%2' ").arg(unitpublic::gsuser).arg(skey);
    mysql.exec(ssql);   //查询用户表
    if(!mysql.next()){
        QMessageBox::information(this, "提示", "旧密码是输入错误！");
        return;
    }
    if(ui->edtnewkey->text() != ui->edtverkey->text()){
        QMessageBox::information(this, "提示", "新密码确认不正确！");
        return;
    }
    mysql.exec(QString("update userinfo set userkey='%1' where usercode='%2' ").arg(ui->edtnewkey->text()).arg(unitpublic::gsuser));   //查询用户表
    QMessageBox::information(this, "提示", "密码修改成功，下次登录生效！");
    this->close();
}
