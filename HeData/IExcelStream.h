/***************************************************************************************************
**      2019-04-10  IExcelStream Excel文件流接口。
***************************************************************************************************/

#ifndef IEXCELSTREAM_H
#define IEXCELSTREAM_H

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"
#include <functional>

class QTextStream;

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IExcelStream : public IInitializeable
{
public:
    // 设置写入内容函数
    virtual void setWriteContent(std::function<void(QTextStream &)> func) = 0;
    // 另存文件
    virtual bool saveAsFile(QString caption = QString(), QString dir = ".", QString *selectedFileName = nullptr) = 0;
    // 写入文件
    virtual bool writeFile(QString fileName) = 0;
    // 写入内容
    virtual bool writeContent(QTextStream &) = 0;
};

HE_DATA_END_NAMESPACE

#endif // IEXCELSTREAM_H
