#include "HTextSpinBox_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HTextSpinBox::HTextSpinBox(QWidget *parent) :
    QSpinBox(parent),
    d_ptr(new HTextSpinBoxPrivate)
{
}

HTextSpinBox::HTextSpinBox(HTextSpinBoxPrivate &p, QWidget *parent) :
    QSpinBox(parent),
    d_ptr(&p)
{
}

HTextSpinBox::~HTextSpinBox()
{
}

QValidator::State HTextSpinBox::validate(QString &input, int &/*pos*/) const
{
    for (auto s : d_ptr->strings)
    {
        if (s == input)
            return QValidator::Acceptable;
        if (s.contains(input))
            return QValidator::Intermediate;
    }
    return QValidator::Invalid;
}

QStringList HTextSpinBox::stringList() const
{
    return d_ptr->strings;
}

void HTextSpinBox::setStringList(const QStringList &value)
{
    if (d_ptr->strings == value)
        return;
    d_ptr->strings = value;
    setRange(0, value.size() - 1);
    emit stringListChanged(value);
    interpretText();
}


QString HTextSpinBox::textFromValue(int value) const
{
    if (d_ptr->strings.size() <= value)
        return "";
    return d_ptr->strings.at(value);
}

int HTextSpinBox::valueFromText(const QString &text) const
{
    return d_ptr->strings.indexOf(text);
}


HE_CONTROL_END_NAMESPACE
