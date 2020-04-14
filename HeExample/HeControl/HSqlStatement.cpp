#include "HSqlStatement_p.h"
#include "HDBConfig.h"
#include <QtXml/QXmlDefaultHandler>
#include <QtCore/QDebug>

HE_CONTROL_BEGIN_NAMESPACE

static const char * const SQL_ID                 = "id";
static const char * const SQL_INCLUDED_DEFINE_ID = "defineId";
static const char * const SQL_TAGNAME_SQL        = "sql";
static const char * const SQL_TAGNAME_SQLS       = "sqls";
static const char * const SQL_TAGNAME_DEFINE     = "define";
static const char * const SQL_TAGNAME_INCLUDE    = "include";
static const char * const SQL_NAMESPACE          = "namespace";

QString buildKey(const QString &sqlNamespace, const QString &id)
{
    return sqlNamespace + "::" + id;
}

class HXmlSqlHandler : public QXmlDefaultHandler
{
public:
    QHash<QString, QString> parse(const QString &fileName);

protected:
    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &attributes) override;
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName) override;
    bool characters(const QString &ch) override;
    bool fatalError(const QXmlParseException &exception) override;

private:
    QHash<QString, QString> _sqls;
    QHash<QString, QString> _defines;
    QString _sqlNamespace;
    QString _currentDefineId;
    QString _currentSqlId;
    QString _currentIncludedDefineId;
    QString _currentText;
};

QHash<QString, QString> HXmlSqlHandler::parse(const QString &fileName)
{
    _sqls.clear();
    _defines.clear();
    QFile file(fileName);
    QXmlInputSource inputSource(&file);
    QXmlSimpleReader reader;
    reader.setContentHandler(this);
    reader.setErrorHandler(this);
    reader.parse(inputSource);
    return _sqls;
}

bool HXmlSqlHandler::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &attributes)
{
    Q_UNUSED(namespaceURI)
    Q_UNUSED(localName)
    // 1. 取得 SQL 得 xml 文档中得 namespace, sql id, include 的 defineId, include 的 id
    // 2. 如果是 <sql> 或 <define> 标签，清空 currentText
    if (qName == SQL_TAGNAME_SQLS)
    {
        _sqlNamespace = attributes.value(SQL_NAMESPACE);
    }
    else if (qName == SQL_TAGNAME_DEFINE)
    {
        _currentDefineId = attributes.value(SQL_ID);
        _currentText = "";
    }
    else if (qName == SQL_TAGNAME_SQL)
    {
        _currentSqlId = attributes.value(SQL_ID);
        _currentText = "";
    }
    else if (qName == SQL_TAGNAME_INCLUDE)
    {
        _currentIncludedDefineId = attributes.value(SQL_INCLUDED_DEFINE_ID);
    }
    return true;
}

bool HXmlSqlHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    Q_UNUSED(namespaceURI)
    Q_UNUSED(localName)

    // 1. 如果是 <define> 标签，则存入 defines
    // 2. 如果是 <sql> 标签，则插入 sqls
    // 3. 如果是 <include> 标签，则从 defines 里取其内容加入 sql
    if (qName == SQL_TAGNAME_DEFINE)
    {
        _defines.insert(buildKey(_sqlNamespace, _currentDefineId), _currentText.simplified());
    }
    else if (qName == SQL_TAGNAME_SQL)
    {
        _sqls.insert(buildKey(_sqlNamespace, _currentSqlId), _currentText.simplified());
        _currentText = "";
    }
    else if (qName == SQL_TAGNAME_INCLUDE)
    {
        auto key = buildKey(_sqlNamespace, _currentIncludedDefineId);
        auto value = _defines.value(key);
        if (!value.isEmpty())
            _currentText += value;
        else
            qDebug() << "Cannot find define: " << key;
    }
    return true;
}

bool HXmlSqlHandler::characters(const QString &ch)
{
    _currentText += ch;
    return true;
}

bool HXmlSqlHandler::fatalError(const QXmlParseException &exception)
{
    qDebug() << QString("Parse error at line %1, column %2, message: %3")
                .arg(exception.lineNumber())
                .arg(exception.columnNumber())
                .arg(exception.message());
    return false;
}

HSqlStatement::HSqlStatement() :
    d_ptr(new HSqlStatementPrivate)
{
    init();
}

HSqlStatement::HSqlStatement(HSqlStatementPrivate &p) :
    d_ptr(&p)
{
    init();
}

HSqlStatement::~HSqlStatement() = default;

QString HSqlStatement::getSql(const QString &sqlNamespace, const QString &id)
{
    auto sql = d_ptr->statements.value(buildKey(sqlNamespace, id));
    if (sql.isEmpty())
        qDebug() << QString("Cannot find SQL for %1::%2").arg(sqlNamespace, id);
    return sql;
}

void HSqlStatement::addSql(const QString &sqlNamespace, const QString &id, const QString &value)
{
    d_ptr->statements.insert(buildKey(sqlNamespace, id), value);
}

void HSqlStatement::addSqlFile(const QString &fileName)
{
    auto sqls = d_ptr->handler->parse(fileName);
    for (auto i = sqls.begin(); i != sqls.end(); i++)
        d_ptr->statements.insert(i.key(), i.value());
}

void HSqlStatement::init()
{
    d_ptr->handler = new HXmlSqlHandler;
    for (const auto &fileName : HDBConfig::instance()->sqlFiles())
        addSqlFile(fileName);
}

HE_CONTROL_END_NAMESPACE
