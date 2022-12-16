#include "HJsonTextEdit_p.h"
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QMimeData>
#include <QtGui/QtEvents>

HE_BEGIN_NAMESPACE

HJsonTextEdit::HJsonTextEdit(QWidget *parent) :
    QTextEdit(parent),
    d_ptr(new HJsonTextEditPrivate)
{
    auto font = this->font();
    font.setPixelSize(28);
    setFont(font);
}

HJsonTextEdit::~HJsonTextEdit()
{
}

void HJsonTextEdit::setJson(const QString &text)
{
    clear();
    QJsonParseError err;

    auto document = QJsonDocument::fromJson(text.toUtf8(), &err);
    if (document.isNull())
    {
        append(err.errorString());
        return;
    }
    if(document.isObject())
    {
        auto object = document.object();
        parseJson(object, 1);
    }
    else if(document.isArray())
    {
        auto array = document.array();
        parseJson(array, 1);
    }
}

void HJsonTextEdit::parseJson(const QJsonObject &object, const int numberOfLayers)
{
    QString spacing;
    for (int i = 0; i < numberOfLayers; i++)
        spacing.append("    ");

    QString spacingBeforeBrackets;
    for (int i = 0; i < numberOfLayers - 1; i++)
        spacingBeforeBrackets.append("    ");
    append(spacingBeforeBrackets + "{");

    int index = 1;
    int length = object.length();
    int nextLayers = numberOfLayers + 1;
    QString endingSymbol;
    for (auto it = object.constBegin(); it != object.constEnd(); it++)
    {
        endingSymbol = index < length ? QStringLiteral(",") : QStringLiteral("");
        auto value = it.value();
        if (value.isString())
        {
            auto str = value.toString();
            auto document = QJsonDocument::fromJson(str.toUtf8());
            if (document.isNull())
            {
                append(QString("<span style='white-space:pre;color:#9C278F;'>%1\"%2\"</span>:<span style='color:#54B54A;'>\"%3\"</span>%4").arg(spacing, it.key(), str, endingSymbol));
            }
            else if(document.isObject())
            {
                append(QString("<span style='white-space:pre;color:#9C278F;'>%1\"%2\"</span>:").arg(spacing, it.key()));
                parseJson(document.object(), nextLayers);
            }
            else if(document.isArray())
            {
                append(QString("<span style='white-space:pre;color:#9C278F;'>%1\"%2\"</span>:").arg(spacing, it.key()));
                parseJson(document.array(), nextLayers);
            }
        }
        else if(value.isDouble())
        {
            append(QString("<span style='white-space:pre;color:#9C278F;'>%1\"%2\"</span>:<span style='color:#128BF1;'>%3</span>%4").arg(spacing).arg(it.key()).arg(value.toDouble()).arg(endingSymbol));
        }
        else if(value.isBool())
        {
            append(QString("<span style='white-space:pre;color:#9C278F;'>%1\"%2\"</span>:%3%4").arg(spacing, it.key()).arg(value.toBool() ? "true" : "false").arg(endingSymbol));
        }
        else if(value.isObject())
        {
            append(QString("<span style='white-space:pre;color:#9C278F;'>%1\"%2\"</span>:").arg(spacing, it.key()));
            parseJson(value.toObject(), nextLayers);
        }
        else if(value.isArray())
        {
            append(QString("<span style='white-space:pre;color:#9C278F;'>%1\"%2\"</span>:").arg(spacing, it.key()));
            parseJson(value.toArray(), nextLayers);
        }
        else
        {
            append(QString("<span style='white-space:pre;color:#9C278F;'>%1\"%2\"</span>:<span style='color:#128BF1;'>%3</span>%4").arg(spacing, it.key()).arg(value.toInt()).arg(endingSymbol));
        }
        ++index;
    }

    append(spacingBeforeBrackets + "}");
}

void HJsonTextEdit::parseJson(const QJsonArray &array, const int numberOfLayers)
{
    QString spacing;
    for (int i = 0; i < numberOfLayers; i++)
        spacing.append("    ");

    QString spacingBeforeBrackets;
    for (int i = 0; i < numberOfLayers - 1; i++)
        spacingBeforeBrackets.append("    ");
    append(spacingBeforeBrackets + "[");

    int index = 1;
    int length = array.size();
    int nextLayers = numberOfLayers + 1;
    QString endingSymbol;
    for (auto it = array.constBegin(); it != array.constEnd(); it++)
    {
        endingSymbol = index < length ? QStringLiteral(",") : QStringLiteral("");
        if (it->type() == QJsonValue::String)
        {
            auto str = it->toString();
            auto document = QJsonDocument::fromJson(str.toUtf8());
            if (document.isNull())
                append(QString("<span style='white-space:pre;color:#54B54A;'>%1\"%2\"</span>%3").arg(spacing, str, endingSymbol));
            else if(document.isObject())
                parseJson(document.object(), nextLayers);
            else if(document.isArray())
                parseJson(document.array(), nextLayers);
        }
        else if (it->type() == QJsonValue::Bool)
            append(QString("%1%2%3").arg(spacing).arg(it->toBool() ? "true" : "false").arg(endingSymbol));
        else if (it->type() == QJsonValue::Double)
            append(QString("<span style='white-space:pre;color:#128BF1;'>%1%2</span>%3").arg(spacing).arg(it->toDouble()).arg(endingSymbol));
        else if(it->type() == QJsonValue::Array)
            parseJson(it->toArray(), nextLayers);
        else if(it->type() == QJsonValue::Object)
            parseJson(it->toObject(), nextLayers);
        else
            append(QString("<span style='white-space:pre;color:#128BF1;'>%1%2</span>%3").arg(spacing).arg(it->toInt()).arg(endingSymbol));
        index++;
    }
    append(spacingBeforeBrackets + "]");
}

void HJsonTextEdit::insertFromMimeData(const QMimeData *source)
{
    if (source->hasText())
        setJson(source->text().trimmed());
    else
        QTextEdit::insertFromMimeData(source);
}

void HJsonTextEdit::keyPressEvent(QKeyEvent *event)
{
    auto keyNumber = event->key();
    if (keyNumber != Qt::Key_Delete && keyNumber != Qt::Key_Backspace)
        return;
    QTextEdit::keyPressEvent(event);
}

HE_END_NAMESPACE
