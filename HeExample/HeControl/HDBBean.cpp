#include "HDBBean.h"
#include "HDBUtil.h"
#include "HSqlStatement.h"
#include <QtCore/QPluginLoader>
#include <QtWidgets/QPushButton>
#include <QtCore/QDebug>

HE_CONTROL_BEGIN_NAMESPACE

const char * const SQL_NAMESPACE_USER = "User";

void HTestThread::run()
{
    qDebug() << HDBUtil::selectInt("select id from user where username='Alice'");
    QThread::sleep(1);
    qDebug() << HDBUtil::selectInt("select id from user where username='Bob'");
}

QString HUser::toString() const
{
    return QString("ID: %1, Username: %2, Password: %3, Email: %4, Mobile: %5")
            .arg(id).arg(username, password, email, mobile);
}

HUser HUserDao::findByUserId(int id)
{
    auto sql = HSqlStatement::instance()->getSql(SQL_NAMESPACE_USER, "findByUserId").arg(id);
    return HDBUtil::selectBean(mapToUser, sql);
}

QList<HUser> HUserDao::findAll()
{
    auto sql = HSqlStatement::instance()->getSql(SQL_NAMESPACE_USER, "findAll");
    return HDBUtil::selectBeans(mapToUser, sql);
}

int HUserDao::insert(const HUser &user)
{
    auto sql = HSqlStatement::instance()->getSql(SQL_NAMESPACE_USER, "insert");
    QVariantMap param;
    param["username"] = user.username;
    param["password"] = user.password;
    param["email"]    = user.email;
    param["mobile"]   = user.mobile;
    return HDBUtil::insert(sql, param);
}

bool HUserDao::update(const HUser &user)
{
    auto sql = HSqlStatement::instance()->getSql(SQL_NAMESPACE_USER, "update");
    QVariantMap param;
    param["id"]       = user.id;
    param["username"] = user.username;
    param["password"] = user.password;
    param["email"]    = user.email;
    param["mobile"]   = user.mobile;
    return HDBUtil::update(sql, param);
}

HUser HUserDao::mapToUser(const QVariantMap &param)
{
    HUser user;
    user.id       = param.value("id", 0).toInt();
    user.username = param.value("username").toString();
    user.password = param.value("password").toString();
    user.email    = param.value("email").toString();
    user.mobile   = param.value("mobile").toString();
    return user;
}

void HDbTest::loadMySqlDriver(const QString &fileName)
{
    auto name = fileName.isEmpty() ? R"(D:\Qt\Qt5.11.3\5.11.3\mingw53_32\plugins\sqldrivers)" : fileName;
    QPluginLoader loader;
    loader.setFileName(name);
    qDebug() << loader.load();
    qDebug() << loader.errorString();
}

void HDbTest::useDBUtil()
{
    // 1. 查找 Alice 的 ID
    qDebug() << "\n1. 查找 Alice 的 ID";
    qDebug() << HDBUtil::selectInt("select id from user where username='Alice'");
    qDebug() << HDBUtil::selectVariant("select id from user where username='Alice'").toInt();

    // 2. 查找 Alice 的密码
    qDebug() << "\n2. 查找 Alice 的密码";
    qDebug() << HDBUtil::selectString("select password from user where username='Alice'");
    qDebug() << HDBUtil::selectMap("select password from user where username='Alice'").value("password").toString();

    // 3. 查找 Alice 的所有信息，如名字，密码，邮件等
    qDebug() << "\n3. 查找 Alice 的所有信息，如名字，密码，邮件等";
    qDebug() << HDBUtil::selectMap("select * from user where username='Alice'");

    // 4. 查找 Alice 和 Bob 的所有信息，如名字，密码，邮件等
    qDebug() << "\n4. 查找 Alice 和 Bob 的所有信息，如名字，密码，邮件等";
    qDebug() << HDBUtil::selectMaps("select * from user where username='Alice' or username='Bob'");

    // 5. 查找 Alice 和 Bob 的密码
    qDebug() << "\n5. 查找 Alice 和 Bob 的密码";
    qDebug() << HDBUtil::selectStrings("select password from user where username='Alice' or username='Bob'");

    // 6. 查询时使用命名参数
    qDebug() << "\n6. 查询时使用命名参数";
    QMap<QString, QVariant> params;
    params["id"] = 1;
    qDebug() << HDBUtil::selectMap("select * from user where id=:id", params);
    qDebug() << HDBUtil::selectString("select username from user where id=:id", params);
}

void HDbTest::useSqlFromFile()
{
    // 读取 namespace 为 User 下，id 为 findByUserId 的 SQL 语句
    qDebug() << HSqlStatement::instance()->getSql("User", "findByUserId");
    qDebug() << HSqlStatement::instance()->getSql("User", "findByUserId-1"); // 找不到这条 SQL 语句会有提示
    qDebug() << HDBUtil::selectMap(HSqlStatement::instance()->getSql("User", "findByUserId").arg(2));
}

void HDbTest::useDao()
{
    // 使用基于 DBUtil 封装好的 DAO 查询数据库
    auto user = HUserDao::findByUserId(1);
    qDebug() << user.username;
    qDebug() << user.toString();

    // 更新数据库
    user.email = "bob@gmail.com";
    qDebug() << "Update: " << HUserDao::update(user);

    auto users = HUserDao::findAll();
    for (const auto &u : users)
        qDebug() << u.toString();
}

void HDbTest::useThread()
{
    for (int i = 0; i < 100; i++)
    {
        auto thread = new HTestThread();
        thread->start();
    }
}

void HDbTest::testOnBorrow()
{
    // 测试步骤:
    // 1. 点击按钮访问数据库: 输出 2
    // 2. 关闭数据库
    // 3. 点击按钮访问数据库: 输出 database not open
    // 4. 启动数据库
    // 5. 点击按钮访问数据库: 输出 2
    auto button = new QPushButton("On Borrow Test");
    QObject::connect(button, &QPushButton::clicked, [] { qDebug() << HDBUtil::selectInt("select id from user where username='Bob'"); });
    button->show();
}

HE_CONTROL_END_NAMESPACE
