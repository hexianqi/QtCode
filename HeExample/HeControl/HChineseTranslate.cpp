#include "HChineseTranslate_p.h"
#include <QtCore/QFile>
#include <QtCore/QRegularExpression>

HE_BEGIN_NAMESPACE

HChineseTranslate::HChineseTranslate(QObject *parent) :
    QObject(parent),
    d_ptr(new HChineseTranslatePrivate)
{
    loadPinYin(":/Resources/data/pinyin.dat");
    loadJianPin(":/Resources/data/jianpin.dat");
}

HChineseTranslate::~HChineseTranslate() = default;

void HChineseTranslate::loadPinYin(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return;
    d_ptr->pinYins = QString(file.readAll()).split(' ');
    file.close();
}

void HChineseTranslate::loadJianPin(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return;
    d_ptr->jianPins = QString(file.readAll()).remove(QRegularExpression("\\s"));
    file.close();
}

QString HChineseTranslate::toPingYin(const QString &value)
{
    if (d_ptr->pinYins.isEmpty() || value.isEmpty())
        return value;

    QStringList list;
    for (auto ch : value)
    {
        auto unicode = QString::number(ch.unicode(), 10).toInt();
        auto index = unicode - 0x4E00;
        if (unicode >= 0x4E00 && unicode <= 0x9FA5 && index < d_ptr->pinYins.size())
            list << d_ptr->pinYins.at(index);
        else
            list << ch;
    }
    return list.join(" ");
}

QString HChineseTranslate::toJianPin(const QString &value)
{
    if (d_ptr->jianPins.isEmpty() || value.isEmpty())
        return value;

    QString text;
    for (auto ch : value)
    {
        auto unicode = ch.unicode();
        if ((unicode >= 'a' && unicode <= 'z' ) || (unicode >= 'A' && unicode <= 'Z'))
            text.append(ch.toUpper());
        else if (unicode >= '0' && unicode <= '9')
            text.append(ch);
        else
        {
            auto index = unicode - 0x4E00;
            if (index >= 0 && index < d_ptr->jianPins.size())
                text.append(d_ptr->jianPins.at(index));
        }
    }
    return text;
}

QString HChineseTranslate::toShouZhiMu(const QString &value)
{
    return toJianPin(value).at(0);
}

HE_END_NAMESPACE
