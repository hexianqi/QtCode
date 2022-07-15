#include "HTestSql.h"
#include <QtSql/QSqlDatabase>
#include <QtCore/QDebug>

void HTestSql::drivers()
{
    for (auto d : QSqlDatabase::drivers())
        qDebug() << d;
}

void HTestSql::testMysql()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("ledsort-sml");
    db.setUserName("root");
    db.setPassword("123456");
    db.open();
    qDebug() << db.isOpen();
}
