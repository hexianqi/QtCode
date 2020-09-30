#include "HXlsxStream_p.h"
#include "xlsxdocument.h"

HE_DATA_BEGIN_NAMESPACE

HXlsxStreamPrivate::HXlsxStreamPrivate()
{
    fileFilter = "Excel files (*.xlsx)";
}


HXlsxStream::HXlsxStream(QObject *parent) :
    IXlsxStream(*new HXlsxStreamPrivate, parent)
{
}

HXlsxStream::HXlsxStream(HXlsxStreamPrivate &p, QObject *parent) :
    IXlsxStream(p, parent)
{
}

HXlsxStream::~HXlsxStream()
{
}

QString HXlsxStream::typeName()
{
    return "HXlsxStream";
}

void HXlsxStream::setReadContent(std::function<void (QXlsx::Document *)> func)
{
    Q_D(HXlsxStream);
    d->readContent = func;
}

void HXlsxStream::setWriteContent(std::function<void (QXlsx::Document *)> func)
{
    Q_D(HXlsxStream);
    d->writeContent = func;
}

bool HXlsxStream::readFile(QString fileName)
{
    if (fileName.isEmpty())
        return false;
    QXlsx::Document doc(fileName);
    if (!doc.isLoadPackage())
        return false;
    return readContent(&doc);
}

bool HXlsxStream::writeFile(QString fileName)
{
    if (fileName.isEmpty())
        return false;
    QXlsx::Document doc(fileName);
    if (!doc.isLoadPackage())
        return false;
    return writeContent(&doc);
}

bool HXlsxStream::readContent(QXlsx::Document *p)
{
    Q_D(HXlsxStream);
    if (d->readContent == nullptr)
        return false;
    d->readContent(p);
    return true;
}

bool HXlsxStream::writeContent(QXlsx::Document *p)
{
    Q_D(HXlsxStream);
    if (d->writeContent == nullptr)
        return false;
    d->writeContent(p);
    return true;
}

HE_DATA_END_NAMESPACE
