/***************************************************************************************************
**      2019-08-08  HResetLineEdit
***************************************************************************************************/

#pragma once

#include "HButtonLineEdit.h"

HE_CONTROL_BEGIN_NAMESPACE

class HResetLineEditPrivate;

class HResetLineEdit : public HButtonLineEdit
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HResetLineEdit)
    Q_PROPERTY(QString defaultText READ defaultText)

public:
    explicit HResetLineEdit(QWidget *parent = nullptr);

public:
    QString defaultText() const;

public slots:
    void setDefaultText(const QString &);
    void resetText();

protected:
    HResetLineEdit(HResetLineEditPrivate &p, QWidget *parent = nullptr);

private:
    void init();
    void handleTextChanged(const QString &);
};

HE_CONTROL_END_NAMESPACE
