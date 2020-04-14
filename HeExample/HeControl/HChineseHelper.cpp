#include "HChineseHelper_p.h"
#include <QtCore/QFile>
#include <QtCore/QRegularExpression>

HE_CONTROL_BEGIN_NAMESPACE

HChineseHelper::HChineseHelper() :
    d_ptr(new HChineseHelperPrivate)
{
    init();
}

HChineseHelper::~HChineseHelper() = default;

void HChineseHelper::loadPingYin(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return;
    d_ptr->pinYins = QString(file.readAll()).split(' ');
    file.close();
}

void HChineseHelper::loadJianPin(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return;
    d_ptr->jianPins = QString(file.readAll()).remove(QRegularExpression("\\s"));
    file.close();
}

QString HChineseHelper::toPingYin(const QString &value)
{
    if (d_ptr->pinYins.isEmpty())
        return value;

    QStringList list;
    for (auto ch : value)
    {
        auto c = QString::number(ch.unicode(), 10).toInt();
        if (c >= 0x4E00 && c <= 0x9FA5 && c - 0x4E00 < d_ptr->pinYins.size())
            list << d_ptr->pinYins.at(c - 0x4E00);
        else
            list << ch;
    }
    return list.join(" ");
}

QString HChineseHelper::toJianPin(const QString &value)
{
    if (d_ptr->jianPins.size() == 0)
        return value;

    QString text;
    for (auto ch : value)
    {
        auto c = ch.unicode();
        if (c >= 0x4E00 && c - 0x4E00 < d_ptr->jianPins.size())
            text.append(d_ptr->jianPins.at(c - 0x4E00));
        else if (c >= 'a' && c <= 'z' )
            text.append(ch.toUpper());
        else
            text.append(ch);
    }
    return text;
}

void HChineseHelper::init()
{
    loadPingYin(":/data/pinyin.dat");
    loadJianPin(":/data/jianpin.dat");
}

HE_CONTROL_END_NAMESPACE
