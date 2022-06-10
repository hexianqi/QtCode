#include "HTestDir.h"
#include <QtCore/QDir>
#include <QtCore/QDebug>

void HTestDir::findUnUsedFile()
{
    QDir dir(R"(E:\GitHub\QtCode\HeExample\HeControl)");
    dir.setFilter(QDir::Files);
    QString content;
    auto contentFiles = dir.entryInfoList(QStringList () << "*.pri" << "*.pro");
    auto checkFiles = dir.entryInfoList(QStringList () << "*.h" << "*.cpp" << "*.ui" << "*.pri" << "*.qrc");
    for (auto info : contentFiles)
    {
        QFile file(info.filePath());
        file.open(QIODevice::ReadOnly);
        content += file.readAll();
        file.close();
    }
    for (auto info : checkFiles)
    {
        if (!content.contains(info.fileName()))
            qDebug() << info.fileName();
    }
}

QFileInfoList getFileListUnderDir(const QString &dirPath)
{
    QFileInfoList list;
    QDir dir(dirPath);
    auto fileInfoList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Dirs);
    for (auto fileInfo : fileInfoList)
    {
        if (fileInfo.isDir())
            list << getFileListUnderDir(fileInfo.absoluteFilePath());
        if(fileInfo.isFile())
            list << fileInfo;
    }
    return list;
}

void HTestDir::findUnUsedQrc()
{
    QDir dir(R"(E:\GitHub\QtCode\HeExample\HeControl)");
    QString content;
    QFileInfoList checkFiles;
    auto contentFiles = dir.entryInfoList(QStringList () << "*.qrc", QDir::Files);
    auto checkDir = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (auto f : checkDir)
        checkFiles << getFileListUnderDir(f.absoluteFilePath());
    for (auto info : contentFiles)
    {
        QFile file(info.filePath());
        file.open(QIODevice::ReadOnly);
        content += file.readAll();
        file.close();
    }
    for (auto info : checkFiles)
    {
        if (!content.contains(info.fileName()))
            qDebug() << info.filePath();
    }
}
