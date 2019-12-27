#include "HResetLineEdit_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HResetLineEdit::HResetLineEdit(QWidget *parent) :
    HButtonLineEdit(*new HResetLineEditPrivate, parent)
{
    init();
}

HResetLineEdit::HResetLineEdit(HResetLineEditPrivate &p, QWidget *parent) :
    HButtonLineEdit(p, parent)
{
    init();
}

HResetLineEdit::~HResetLineEdit()
{
}

QString HResetLineEdit::defaultText() const
{
    Q_D(const HResetLineEdit);
    return d->defaultText;
}

void HResetLineEdit::setDefaultText(const QString &value)
{
    Q_D(HResetLineEdit);
    if (d->defaultText == value)
        return;
    d->defaultText = value;
    setButtonVisible(d->defaultText != value);
}

void HResetLineEdit::resetText()
{
    Q_D(HResetLineEdit);
    setText(d->defaultText);
}

void HResetLineEdit::init()
{
    setButtonPosition(Position_RightInside);
    setIcon(QIcon(":/image/ww/wrap.png"));
    setAutoRaise(true);
    setButtonVisible(false);
    setButtonFocusPolicy(Qt::NoFocus);
    connect(this, &HResetLineEdit::textChanged, this, &HResetLineEdit::handleTextChanged);
    connect(this, &HResetLineEdit::buttonClicked, this, &HResetLineEdit::resetText);
}

void HResetLineEdit::handleTextChanged(const QString &value)
{
    Q_D(HResetLineEdit);
    setButtonVisible(d->defaultText != value);
}

HE_CONTROL_END_NAMESPACE
