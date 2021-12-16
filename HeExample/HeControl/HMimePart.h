/***************************************************************************************************
**      2019-12-25  HMimePart
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HMimePartPrivate;

class HMimePart : public QObject
{
    Q_OBJECT

public:
    enum Encoding
    {
        _7Bit,
        _8Bit,
        Base64,
        QuotedPrintable
    };

public:
    explicit HMimePart(QObject *parent = nullptr);
    ~HMimePart() override;

public:
    QString header() const;
    QByteArray content() const;
    QString contentId() const;
    QString contentName() const;
    QString contentType() const;
    QString contentCharset() const;
    Encoding contentEncoding() const;

public:
    void setHeader(const QString &value);
    void addHeaderLine(const QString &value);
    void setContent(const QByteArray &value);
    void setContentId(const QString &value);
    void setContentName(const QString &value);
    void setContentType(const QString &value);
    void setContentCharset(const QString &value);
    void setContentEncoding(Encoding value);

public:
    virtual QString toString();
    virtual void prepare();

protected:
    HMimePart(HMimePartPrivate &p, QObject *parent = nullptr);

protected:
    QString format(const QString &content, bool quotedPrintable = false, int maxLength = 76);

protected:
    QScopedPointer<HMimePartPrivate> d_ptr;
};

HE_END_NAMESPACE
