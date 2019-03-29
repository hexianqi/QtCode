/***************************************************************************************************
**      2018-07-09  IFileStream 文件流接口。
***************************************************************************************************/

#ifndef IFILESTREAM_H
#define IFILESTREAM_H

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"
#include <functional>

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IFileStream : public IInitializeable
{
public:
    // 设置Magic数
    virtual void setMagicNumber(quint32 value) = 0;
    // 设置文件版本
    virtual void setFileVersion(quint32 value) = 0;
    // 设置文件过滤
    virtual void setFileFilter(QString value) = 0;
    // 设置读取内容函数
    virtual void setReadContent(std::function<void(QDataStream &)> func) = 0;
    // 设置写入内容函数
    virtual void setWriteContent(std::function<void(QDataStream &)> func) = 0;
    // 获取文件版本
    virtual quint32 fileVersion() = 0;
    // 获取文件过滤
    virtual QString fileFilter() = 0;

public:
    // 打开文件
    virtual bool openFile(QString caption = QString(), QString dir = ".", QString *selectedFileName = nullptr) = 0;
    // 另存文件
    virtual bool saveAsFile(QString caption = QString(), QString dir = ".", QString *selectedFileName = nullptr) = 0;
    // 读取文件
    virtual bool readFile(QString fileName) = 0;
    // 写入文件
    virtual bool writeFile(QString fileName) = 0;
    // 读取内容
    virtual bool readContent(QDataStream &) = 0;
    // 写入内容
    virtual bool writeContent(QDataStream &) = 0;
};

HE_DATA_END_NAMESPACE

#endif // IFILESTREAM_H
