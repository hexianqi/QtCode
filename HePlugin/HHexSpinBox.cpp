#include "HHexSpinBox_p.h"

HHexSpinBox::HHexSpinBox(QWidget *parent) :
    QSpinBox(parent),
    d_ptr(new HHexSpinBoxPrivate)
{
    init();
}

HHexSpinBox::HHexSpinBox(HHexSpinBoxPrivate &p, QWidget *parent) :
    QSpinBox(parent),
    d_ptr(&p)
{
    init();
}

HHexSpinBox::~HHexSpinBox() = default;

QValidator::State HHexSpinBox::validate(QString &text, int &pos) const
{
    return d_ptr->validator->validate(text, pos);
}

int HHexSpinBox::valueFromText(const QString &text) const
{
    bool ok;
    return text.toInt(&ok, 16);
}

QString HHexSpinBox::textFromValue(int value) const
{
    return QString::number(value, 16).toUpper();
}

void HHexSpinBox::init()
{
    d_ptr->validator = new QRegularExpressionValidator(QRegularExpression("[0-9A-Fa-f]{1,8}"), this);
}
