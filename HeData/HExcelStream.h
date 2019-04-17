/***************************************************************************************************
**      2019-04-10  HExcelStream Excel文件流类。
***************************************************************************************************/

#ifndef HEXCELSTREAM_H
#define HEXCELSTREAM_H

#include "IExcelStream.h"
#include <QtCore/QObject>

HE_DATA_BEGIN_NAMESPACE

class HExcelStreamPrivate;

class HExcelStream : public QObject, public IExcelStream
{
    Q_OBJECT

public:
    explicit HExcelStream(QObject *parent = nullptr);
    ~HExcelStream() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setWriteContent(std::function<void(QTextStream &)> func) override;
    void setWriteContent(QString value) override;
    QString fileFilter() override;

public:
    bool saveAsFile(QString caption = QString(), QString dir = ".", QString *selectedFileName = nullptr) override;
    bool writeFile(QString fileName) override;
    bool writeContent(QTextStream &) override;

protected:
    HExcelStream(HExcelStreamPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HExcelStreamPrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HEXCELSTREAM_H
