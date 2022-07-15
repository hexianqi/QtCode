#include "frmlogin.h"
#include "ui_frmlogin.h"
#include "unitpublic.h"
#include "qsqldatabase.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "qmessagebox.h"
#include "qdebug.h"

frmlogin::frmlogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmlogin)
{
    ui->setupUi(this);
    ui->edtkey->setEchoMode(QLineEdit::Password);
    this->setWindowTitle("用户登录");
}

frmlogin::~frmlogin()
{
    delete ui;
}

void frmlogin::on_btnok_clicked()
{
//    unitpublic::dbmysql = QSqlDatabase::addDatabase("QODBC");       //利用ODBC连接mysql，注意odbc驱动版本要跟gcc版本一样，都是32位
//    unitpublic::dbmysql.setHostName("127.0.0.1");
//    unitpublic::dbmysql.setPort(3306);
//    unitpublic::dbmysql.setDatabaseName("ledsort-mysql");
//    unitpublic::dbmysql.setUserName("root");
//    unitpublic::dbmysql.setPassword("123456");
//    bool ok = unitpublic::dbmysql.open();
    bool ok = true;
    if (ok){
        QString suser = "admin";//用户
        if(ui->comboBox->currentIndex()==0){
            suser = "operator";}     //登录用户
        else if(ui->comboBox->currentIndex()==1){
            suser = "engineer";
        }
        QString skey = ui->edtkey->text();
        QSqlQuery mysql(unitpublic::dbmysql);
        mysql.exec(QString("select id from userinfo where usercode='%1' and userkey='%2' ").arg(suser).arg(skey));   //查询用户表
        if(!mysql.next()){
            QMessageBox::information(this, "提示", "登录失败，请检查账号密码是否正确？");
            return;
        }
        unitpublic::gsuser = suser; //当前登录账号
       // unitpublic::dbmysql.close();
        done(Accepted); //接受
    }
    else {
        QMessageBox::information(this, "提示", "登录失败，数据库连接异常！");
    }

}

void frmlogin::on_btnno_clicked()
{
    done(Rejected);//取消

}
