/***************************************************************************************************
**      2020-03-31  HDBBean
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QThread>

HE_CONTROL_BEGIN_NAMESPACE

class HUser
{
public:
    int id = 0;
    QString username;
    QString password;
    QString email;
    QString mobile;

public:
    QString toString() const;
};

class HUserDao
{
public:
    static HUser findByUserId(int id);
    static QList<HUser> findAll();
    static int insert(const HUser &);
    static bool update(const HUser &);

private:
    static HUser mapToUser(const QVariantMap &);
};

class HTestThread : public QThread
{
    Q_OBJECT

protected:
    void run() override;
};

class HDbTest
{
public:
    static void loadMySqlDriver(const QString &fileName = QString());
    static void useDBUtil();
    static void useSqlFromFile();
    static void useDao();
    static void useThread();
    static void testOnBorrow();
};

HE_CONTROL_END_NAMESPACE
