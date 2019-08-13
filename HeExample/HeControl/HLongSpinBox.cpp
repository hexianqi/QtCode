#include "HLongSpinBox_p.h"
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QStyleOptionSpinBox>

HE_CONTROL_BEGIN_NAMESPACE

HLongSpinBoxValidator::HLongSpinBoxValidator(HLongSpinBox *parent) :
    QValidator(parent)
{
    _spinBox = parent;
}

HLongSpinBoxValidator::~HLongSpinBoxValidator()
{
}

void HLongSpinBoxValidator::fixup(QString &input) const
{
    _spinBox->fixup(input);
}

QValidator::State HLongSpinBoxValidator::validate(QString &input, int &pos) const
{
    if (!_spinBox->prefix().isEmpty() && !input.startsWith(_spinBox->prefix()))
        input.prepend(_spinBox->prefix());
    if (!_spinBox->suffix().isEmpty() && !input.endsWith(_spinBox->suffix()))
        input.append(_spinBox->suffix());
    return _spinBox->validate(input, pos);
}

HLongSpinBox::HLongSpinBox(QWidget *parent) :
    QAbstractSpinBox(parent),
    d_ptr(new HLongSpinBoxPrivate)
{
    init();
}

HLongSpinBox::HLongSpinBox(HLongSpinBoxPrivate &p, QWidget *parent) :
    QAbstractSpinBox(parent),
    d_ptr(&p)
{
    init();
}


HLongSpinBox::~HLongSpinBox()
{
}

qlonglong HLongSpinBox::minimum() const
{
    return d_ptr->minimum;
}

qlonglong HLongSpinBox::maximum() const
{
    return d_ptr->maximum;
}

qlonglong HLongSpinBox::value() const
{
    return d_ptr->value;
}

QString HLongSpinBox::prefix() const
{
    return d_ptr->prefix;
}

QString HLongSpinBox::suffix() const
{
    return d_ptr->suffix;
}

qlonglong HLongSpinBox::singleStep() const
{
    return d_ptr->singleStep;
}

QValidator::State HLongSpinBox::validate(QString &input, int &/*pos*/) const
{
    bool ok;
    auto v = removeFix(input).toLongLong(&ok);
    return (!ok || v < minimum() || v > maximum()) ? QValidator::Invalid : QValidator::Acceptable;
}

void HLongSpinBox::fixup(QString &input) const
{
    input.remove(QLocale().groupSeparator());
}

void HLongSpinBox::stepBy(int steps)
{
    if (steps == 0)
        return;
    auto temp = value() + steps * singleStep();
    if (wrapping())
    {
        auto d1 = temp - maximum();
        auto d2 = temp - minimum();
        if (temp > value() && d1 > 0)
            temp = minimum() + d1 - 1;
        else if (temp < value() && d2 < 0)
            temp = maximum() + d2 + 1;
    }
    else
        temp = qBound(minimum(), temp, maximum());
    setValue(temp);
    selectAll();
}

void HLongSpinBox::setRange(qlonglong minimum, qlonglong maximum)
{
    if (minimum >= maximum)
        qSwap(minimum, maximum);

    d_ptr->minimum = minimum;
    d_ptr->maximum = maximum;
    if (d_ptr->value < minimum || d_ptr->value > maximum)
        setValue(qBound(minimum, d_ptr->value, maximum));
}

void HLongSpinBox::setMinimum(qlonglong value)
{
    setRange(value, d_ptr->maximum);
}

void HLongSpinBox::setMaximum(qlonglong value)
{
    setRange(d_ptr->minimum, value);
}

void HLongSpinBox::setValue(qlonglong value)
{
    if (value < d_ptr->minimum || value > d_ptr-> maximum || value == d_ptr->value)
        return;
    d_ptr->value = value;

    auto text = d_ptr->prefix + textFromValue(value) + d_ptr->suffix;
    updateEdit();
    emit valueChanged(value);
    emit valueChanged(text);
}

void HLongSpinBox::setPrefix(const QString &value)
{
    if (d_ptr->prefix == value)
        return;
    d_ptr->prefix = value;
    updateEdit();
}

void HLongSpinBox::setSuffix(const QString &value)
{
    if (d_ptr->suffix == value)
        return;
    d_ptr->suffix = value;
    updateEdit();
}

void HLongSpinBox::setSingleStep(qlonglong value)
{
    if (d_ptr->singleStep == value)
        return;
    d_ptr->singleStep = value;
}

QString HLongSpinBox::textFromValue(qlonglong value) const
{
    auto text = QLocale().toString(value);
    text.remove(QLocale().groupSeparator());
    return text;
}

qlonglong HLongSpinBox::valueFromText(const QString &text) const
{
    return removeFix(text).toLongLong();
}

QString HLongSpinBox::removeFix(const QString &text) const
{
    QString temp = text;
    if (!d_ptr->prefix.isEmpty() && temp.startsWith(d_ptr->prefix))
        temp.remove(0, d_ptr->prefix.size());
    if (!d_ptr->suffix.isEmpty() && temp.endsWith(d_ptr->suffix))
        temp.chop(d_ptr->suffix.size());
    return temp;
}

QAbstractSpinBox::StepEnabled HLongSpinBox::stepEnabled() const
{
    if (wrapping())
        return StepUpEnabled | StepDownEnabled;
    StepEnabled se = StepNone;
    if (value( ) <maximum())
        se |= StepUpEnabled;
    if ( value() > minimum())
        se |= StepDownEnabled;
    return se;
}

void HLongSpinBox::init()
{
    updateEdit();
    lineEdit()->setValidator(new HLongSpinBoxValidator(this));
    connect(lineEdit(), &QLineEdit::textChanged, this, &HLongSpinBox::handleEditTextChanged);
    setWindowIcon(QIcon(":/image/ww/longspinbox.png"));
}

void HLongSpinBox::updateEdit()
{
    auto edit = lineEdit();
    auto empty = edit->text().isEmpty();
    auto cursor = edit->cursorPosition();
    auto bs = edit->blockSignals(true);
    edit->setText(d_ptr->prefix + textFromValue(d_ptr->value) + d_ptr->suffix);
    cursor = qBound(d_ptr->prefix.size(), cursor, edit->displayText().size() - d_ptr->suffix.size());
    edit->setCursorPosition(empty ? d_ptr->prefix.size() : cursor);
    edit->blockSignals(bs);
    updateButtons();
}

void HLongSpinBox::updateButtons()
{
    QStyleOptionSpinBox option;
    option.init(this);
    option.activeSubControls = QStyle::SC_None;
    option.buttonSymbols = buttonSymbols();
    option.subControls = QStyle::SC_SpinBoxUp | QStyle::SC_SpinBoxDown | QStyle::SC_SpinBoxFrame;
    option.stepEnabled = stepEnabled();
    option.frame = hasFrame();
    update(style()->subControlRect(QStyle::CC_SpinBox, &option, QStyle::SC_SpinBoxUp, this));
    update(style()->subControlRect(QStyle::CC_SpinBox, &option, QStyle::SC_SpinBoxDown, this));
}

void HLongSpinBox::handleEditTextChanged(const QString &value)
{
    auto temp = value;
    auto pos = lineEdit()->cursorPosition();
    if (validate(temp, pos) == QValidator::Acceptable)
        setValue(valueFromText(temp));
}

HE_CONTROL_END_NAMESPACE
