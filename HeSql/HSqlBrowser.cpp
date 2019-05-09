#include "HSqlBrowser_p.h"
#include <QtCore/QDebug>

HE_SQL_BEGIN_NAMESPACE

HSqlBrowser::HSqlBrowser(QWidget *parent) :
    ISqlBrowser(parent),
    d_ptr(new HSqlBrowserPrivate)
{
    init();
}

HSqlBrowser::HSqlBrowser(HSqlBrowserPrivate &p, QWidget *parent) :
    ISqlBrowser(parent),
    d_ptr(&p)
{
    init();
}

HSqlBrowser::~HSqlBrowser()
{
    qDebug() << __func__;
}

void HSqlBrowser::initialize(QVariantMap /*param*/)
{

}

QString HSqlBrowser::typeName()
{
    return "HSqlBrowser";
}

void HSqlBrowser::init()
{
    setWindowTitle(tr("数据库浏览"));
}

HE_SQL_END_NAMESPACE
