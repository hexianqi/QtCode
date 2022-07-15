#include "HHelper.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HLogRedirectService.h"
#include "HeCore/HKeepLogFile.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>

HE_USE_NAMESPACE

QSqlDatabase HHelper::mysql;
HKeepLogFile *logFile = nullptr;

bool HHelper::initialize()
{
//    mysql = createConnectMySql("mysql");
//    if (!mysql.isOpen())
//    {
//        QMessageBox::information(nullptr, "提示", "MySQL数据库连接失败，程序无法启动！");
//        return false;
//    }

    auto service = HLogRedirectService::instance();
    service->setUseContext(false);
    logFile = new HKeepLogFile;
    QObject::connect(service, SIGNAL(output(QString)), logFile, SLOT(append(QString)));


    HAppContext::setContextValue("Settings", QString("Ini\\%1.ini").arg(QApplication::applicationName()));
    HAppContext::setContextValue("Profile", QString("%1.db").arg(QApplication::applicationName()));
    return true;
}

QSqlDatabase HHelper::createConnectMySql(const QString &connectionName)
{
    auto db = QSqlDatabase::addDatabase("QODBC", connectionName);
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("ledsort-mysql");
    db.setUserName("root");
    db.setPassword("123456");
    db.setConnectOptions("CLIENT_INTERACTIVE=31536000");
    db.open();
    return db;
}

