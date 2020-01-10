#ifndef HLONGSPINBOX_P_H
#define HLONGSPINBOX_P_H

#include "HLongSpinBox.h"

HE_CONTROL_BEGIN_NAMESPACE

class HLongSpinBoxPrivate
{
public:
    qlonglong minimum = 0;
    qlonglong maximum = 0x7FFFFFFFFFFFFFFF;
    qlonglong value = 0;
    qlonglong singleStep = 1;
    QString prefix;
    QString suffix;

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
