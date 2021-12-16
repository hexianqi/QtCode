/***************************************************************************************************
**      2019-06-25  HAbstractProgressBar 抽象进度控件。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HAbstractProgressPrivate;

class HAbstractProgress : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(double maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(int decimal READ decimal WRITE setDecimal)

public:
    explicit HAbstractProgress(QWidget *parent = nullptr);
    ~HAbstractProgress() override;

signals:
    void valueChanged(double value);

public:
    double minimum() const;
    double maximum() const;
    double value() const;
    int decimal() const;

public slots:
    virtual void setRange(double minimum, double maximum);
    virtual void setMinimum(double value);
    virtual void setMaximum(double value);
    virtual void setValue(double value);
    virtual void setDecimal(int value);

protected:
    HAbstractProgress(HAbstractProgressPrivate &p, QWidget *parent = nullptr);

protected:
    double range();
    double toRatio(double value);
    double fromRatio(double value);

protected:
    QScopedPointer<HAbstractProgressPrivate> d_ptr;
};

HE_END_NAMESPACE
