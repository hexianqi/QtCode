/***************************************************************************************************
**      2019-08-12  HTextSpinBox
***************************************************************************************************/

#ifndef HTEXTSPINBOX_H
#define HTEXTSPINBOX_H

#include "HControlGlobal.h"
#include <QtGui/QIcon>
#include <QtWidgets/QSpinBox>

HE_CONTROL_BEGIN_NAMESPACE

class HTextSpinBoxPrivate;

class HTextSpinBox : public QSpinBox
{
    Q_OBJECT
    Q_PROPERTY(QStringList stringList READ stringList WRITE setStringList)

public:
    explicit HTextSpinBox(QWidget *parent = nullptr);
    ~HTextSpinBox() override;

signals:
    void stringListChanged(const QStringList &);

public:
    QValidator::State validate(QString &input, int &pos) const override;
    QStringList stringList() const;

public slots:
    void setStringList(const QStringList &);

protected:
    HTextSpinBox(HTextSpinBoxPrivate &p, QWidget *parent = nullptr);

protected:
    QString textFromValue(int value) const override;
    int valueFromText(const QString &text) const override;

protected:
    QScopedPointer<HTextSpinBoxPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HTEXTSPINBOX_H
