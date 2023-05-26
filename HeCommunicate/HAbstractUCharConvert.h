/***************************************************************************************************
**      2023-05-25  HAbstractUCharConvert
***************************************************************************************************/

#pragma once

#include "IUCharConvert.h"

HE_BEGIN_NAMESPACE

class HAbstractUCharConvertPrivate;

class HAbstractUCharConvert : public QObject, public IUCharConvert
{
    Q_OBJECT

public:
    explicit HAbstractUCharConvert(QObject *parent = nullptr);
    ~HAbstractUCharConvert() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;

public:
    void setDigits(QVariant::Type, int) override;
    int digits(QVariant::Type) override;

public:
    QVector<uchar> toUChar(QVariant value) override;
    QVector<uchar> toUChar(QVariantList value) override;
    QVector<uchar> toUChar(uchar value) override;

public:
    QVariant toValue(QVariant::Type type, QVector<uchar> data, int pos = 0) override;
    QVariantList toValues(QVariant::Type type, QVector<uchar> data, int size) override;
    uchar toValue(QVector<uchar> data) override;

protected:
    HAbstractUCharConvert(HAbstractUCharConvertPrivate &p, QObject *parent = nullptr);

protected:
    virtual QVector<uchar> toVector(int value) = 0;
    virtual QVector<uchar> toVector(double value) = 0;
    virtual QVector<uchar> toVector(uint value) = 0;
    virtual int toInt(QVector<uchar> data, int pos = 0) = 0;
    virtual double toDouble(QVector<uchar> data, int pos = 0) = 0;
    virtual uint toUInt(QVector<uchar> data, int pos = 0) = 0;

protected:
    QScopedPointer<HAbstractUCharConvertPrivate> d_ptr;
};

HE_END_NAMESPACE

