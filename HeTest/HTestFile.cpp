#include "HTestFile.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>

void HTestFile::toHex(QString ifileName, QString ofileName)
{
    QFile ifile(ifileName);
    QFile ofile(ofileName);

    ifile.open(QFile::ReadWrite | QFile::Text);
    ofile.open(QFile::ReadWrite | QFile::Text);

    QTextStream out(&ofile);

    auto data = ifile.readAll();
    for (int i = 0; i < data.size(); i++)
    {
        if (i % 10 == 0)
            out << endl;
        out << QString("0x%1, ").arg(data.at(i), 2, 16, QChar('0'));
    }

    ifile.close();
    ofile.close();
}

void HTestFile::toString(QString ifileName, QString ofileName)
{
    QFile ifile(ifileName);
    QFile ofile(ofileName);

    ifile.open(QFile::ReadWrite | QFile::Text);
    ofile.open(QFile::ReadWrite | QFile::Text | QIODevice::Truncate);

    QTextStream out(&ofile);

    while (!ifile.atEnd())
    {
        auto line = QString(ifile.readLine()).trimmed();
        out << QString("\"%1\\n\"").arg(line) << endl;

    }
    ifile.close();
    ofile.close();
}
