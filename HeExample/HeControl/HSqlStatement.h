/***************************************************************************************************
**      2020-03-31  HSqlStatement SQL语句。
**                  SQL 文件的定义
**                  1. <sqls> 必须有 namespace
**                  2. <define> 必须在 <sql> 前定义，必须有 id 属性才有意义，否则不能被引用
**                  3. <sql> 必须有 id 属性才有意义，<sql> 里可以用 <include defineId="define_id"> 引用 <define> 的内容
**
**                  Demo:
**                  <sqls namespace="User">
**                      <define id="fields">id, username, password, email, mobile</define>
**                      <sql id="findByUserId">
**                          SELECT <include defineId="fields"/> FROM user WHERE id=%1
**                      </sql>
**                      <sql id="findAll">
**                          SELECT id, username, password, email, mobile FROM user
**                      </sql>
**                      <sql id="insert">
**                          INSERT INTO user (username, password, email, mobile)
**                          VALUES (:username, :password, :email, :mobile)
**                      </sql>
**                      <sql id="update">
**                          UPDATE user SET username=:username, password=:password, email=:email, mobile=:mobile WHERE id=:id
**                      </sql>
**                  </sqls>
***************************************************************************************************/

#ifndef HSQLSTATEMENT_H
#define HSQLSTATEMENT_H

#include "HControlGlobal.h"
#include "HeCore/HSingleton3.h"

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

class HSqlStatementPrivate;

class HSqlStatement
{
    H_SINGLETON3(HSqlStatement)

private:
    explicit HSqlStatement();
    virtual ~HSqlStatement();

public:
    QString getSql(const QString &sqlNamespace, const QString &id);
    void addSql(const QString &sqlNamespace, const QString &id, const QString &value);
    void addSqlFile(const QString &fileName);

protected:
    HSqlStatement(HSqlStatementPrivate &);

protected:
    QScopedPointer<HSqlStatementPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HSQLSTATEMENT_H
