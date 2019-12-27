#include "HQuotedPrintable.h"
#include <QtCore/QString>

HE_CONTROL_BEGIN_NAMESPACE

QString HQuotedPrintable::encode(const QByteArray &value)
{
    QString result;
    const char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    for (auto byte : value)
    {
        if ((byte == 0x20) || ((byte >= 0x21) && (byte <= 0x7E) && (byte != 0x3D)))
        {
            result.append(byte);
        }
        else
        {
            result.append('=');
            result.append(hex[(byte >> 4) & 0x0F]);
            result.append(hex[byte & 0x0F]);
        }
    }
    return result;
}

QByteArray HQuotedPrintable::decode(const QString &value)
{
    //                     0  1  2  3  4  5  6  7  8  9  :  ;  <  =  >  ?  @  A   B   C   D   E   F
    const int hexVal[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 10, 11, 12, 13, 14, 15 };

    QByteArray result;
    for (int i = 0; i < value.length(); ++i)
    {
        if (value.at(i).toLatin1() == '=')
        {
            result.append(static_cast<char>((hexVal[value.at(i + 1).toLatin1() - '0'] << 4) + hexVal[value.at(i + 2).toLatin1() - '0']));
            i += 2;
        }
        else
        {
            result.append(value.at(i).toLatin1());
        }
    }
    return result;
}

HE_CONTROL_END_NAMESPACE
