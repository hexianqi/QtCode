/***************************************************************************************************
**      2019-08-12  HTextSpinBox
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QSpinBox>

HE_BEGIN_NAMESPACE

class HTextSpinBoxPrivate;

class HTextSpinBox : public QSpinBox
{
    Q_OBJECT
    Q_PROPERTY(QStringList items READ items WRITE setItems)

public:
    explicit HTextSpinBox(QWidget *parent = nullptr);
    ~HTextSpinBox() override;

signals:
    void itemsChanged(const QStringList &);

public:
    QValidator::State validate(QString &input, int &pos) const override;
    QStringList items() const;

public slots:
    void setItems(const QStringList &);
    void addItems(const QStringList &);
    void addItem(const QString &);

protected:
    HTextSpinBox(HTextSpinBoxPrivate &p, QWidget *parent = nullptr);

protected:
    QString textFromValue(int value) const override;
    int valueFromText(const QString &text) const override;

protected:
    QScopedPointer<HTextSpinBoxPrivate> d_ptr;
};

HE_END_NAMESPACE
