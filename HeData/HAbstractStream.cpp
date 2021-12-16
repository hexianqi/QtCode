#include "HAbstractStream_p.h"
#include <QtWidgets/QFileDialog>

HE_BEGIN_NAMESPACE

HAbstractStream::HAbstractStream(QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractStreamPrivate)
{
}

HAbstractStream::HAbstractStream(HAbstractStreamPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractStream::~HAbstractStream()
{
}

void HAbstractStream::initialize(QVariantMap param)
{
    if (param.contains("fileFilter"))
        setFileFilter(param.value("fileFilter").toString());
}

QString HAbstractStream::fileFilter()
{
    return d_ptr->fileFilter;
}

void HAbstractStream::setFileFilter(QString value)
{
    d_ptr->fileFilter = value;
}

bool HAbstractStream::openFile(QString caption, QString dir, QString *selectedFileName)
{
    auto filter = fileFilter();
    auto fileName = QFileDialog::getOpenFileName(nullptr, caption, dir, filter);
    if (fileName.isEmpty())
        return false;
    if (!readFile(fileName))
        return false;
    if (selectedFileName)
        *selectedFileName = fileName;
    return true;
}

bool HAbstractStream::saveAsFile(QString caption, QString dir, QString *selectedFileName)
{
    auto filter = fileFilter();
    auto fileName = QFileDialog::getSaveFileName(nullptr, caption, dir, filter);
    if (fileName.isEmpty())
        return false;
    if (!writeFile(fileName))
        return false;
    if (selectedFileName)
        *selectedFileName = fileName;
    return true;
}

HE_END_NAMESPACE
