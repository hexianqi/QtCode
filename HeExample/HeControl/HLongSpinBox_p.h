#ifndef HLONGSPINBOX_P_H
#define HLONGSPINBOX_P_H

#include "HLongSpinBox.h"

HE_CONTROL_BEGIN_NAMESPACE

class HLongSpinBoxPrivate
{
public:
    qlonglong minimum = 0;
    qlonglong maximum = 99;
    qlonglong value = 0;
    QString prefix;
    QString suffix;
    qlonglong singleStep = 1;
};

class HLongSpinBoxValidator : public QValidator
{
    Q_OBJECT

public:
    explicit HLongSpinBoxValidator(HLongSpinBox *parent = nullptr);
    ~HLongSpinBoxValidator() override;

public:
    void fixup(QString & input) const override;
    State validate(QString &input, int &pos ) const override;

private:
    HLongSpinBox *_spinBox;
};

HE_CONTROL_END_NAMESPACE

#endif // HLONGSPINBOX_P_H
