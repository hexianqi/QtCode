#include "HTextSpinBox_p.h"

HE_BEGIN_NAMESPACE

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

HTextSpinBox::~HTextSpinBox() = default;

QValidator::State HTextSpinBox::validate(QString &input, int &/*pos*/) const
{
    for (const auto &text : d_ptr->items)
    {
        if (text == input)
            return QValidator::Acceptable;
        if (text.contains(input))
            return QValidator::Intermediate;
    }
    return QValidator::Invalid;
}

QStringList HTextSpinBox::items() const
{
    return d_ptr->items;
}

void HTextSpinBox::setItems(const QStringList &value)
{
    if (d_ptr->items == value)
        return;
    d_ptr->items = value;
    setRange(0, value.size() - 1);
    emit itemsChanged(value);
    interpretText();
}

void HTextSpinBox::addItems(const QStringList &value)
{
    setItems(QStringList() << d_ptr->items << value);
}

void HTextSpinBox::addItem(const QString &value)
{
    setItems(QStringList() << d_ptr->items << value);
}

QString HTextSpinBox::textFromValue(int value) const
{
    if (d_ptr->items.size() <= value || value < 0)
        return "";
    return d_ptr->items.at(value);
}

int HTextSpinBox::valueFromText(const QString &text) const
{
    return d_ptr->items.indexOf(text);
}

HE_END_NAMESPACE
