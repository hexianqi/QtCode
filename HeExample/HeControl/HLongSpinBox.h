/***************************************************************************************************
**      2019-08-06  HLongSpinBox
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QAbstractSpinBox>

HE_BEGIN_NAMESPACE

class HLongSpinBoxPrivate;

class HLongSpinBox : public QAbstractSpinBox
{
    Q_OBJECT
    Q_PROPERTY(qlonglong minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(qlonglong maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(qlonglong value READ value WRITE setValue NOTIFY valueChanged USER true)
    Q_PROPERTY(QString prefix READ prefix WRITE setPrefix)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix)
    Q_PROPERTY(qlonglong singleStep READ singleStep WRITE setSingleStep)

public:
    explicit HLongSpinBox(QWidget *parent = nullptr);
    ~HLongSpinBox() override;

signals:
    void valueChanged(qlonglong value);
    void valueChanged(const QString &value);

public:
    qlonglong minimum() const;
    qlonglong maximum() const;
    qlonglong value() const;
    QString prefix() const;
    QString suffix() const;
    qlonglong singleStep() const;
    QValidator::State validate(QString &input, int &pos) const override;
    void fixup(QString &input) const override;
    void stepBy(int steps) override;

public slots:
    void setRange(qlonglong minimum, qlonglong maximum);
    void setMinimum(qlonglong value);
    void setMaximum(qlonglong value);
    void setValue(qlonglong value);
    void setPrefix(const QString &value);
    void setSuffix(const QString &value);
    void setSingleStep(qlonglong value);

protected:
    HLongSpinBox(HLongSpinBoxPrivate &p, QWidget *parent = nullptr);

protected:
    QString textFromValue(qlonglong value) const;
    qlonglong valueFromText(const QString &text) const;
    QString removeFix(const QString &text) const;
    StepEnabled stepEnabled() const override;

protected:
    QScopedPointer<HLongSpinBoxPrivate> d_ptr;

private:
    void init();
    void updateEdit();
    void updateButtons();
    void handleEditTextChanged(const QString &value);
};

HE_END_NAMESPACE
