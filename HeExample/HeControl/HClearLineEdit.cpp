#include "HClearLineEdit_p.h"
#include <QtWidgets/QToolButton>

HE_CONTROL_BEGIN_NAMESPACE

HClearLineEdit::HClearLineEdit(QWidget *parent) :
    HButtonLineEdit(*new HClearLineEditPrivate, parent)
{
    init();
}

HClearLineEdit::HClearLineEdit(HClearLineEditPrivate &p, QWidget *parent) :
    HButtonLineEdit(p, parent)
{
    init();
}

void HClearLineEdit::setButtonVisible(bool b)
{
    if (isReadOnly())
        return;
    HButtonLineEdit::setButtonVisible(b);
}

void HClearLineEdit::paintEvent(QPaintEvent *e)
{
    Q_D(HClearLineEdit);
    if (!d->vis && isReadOnly())
    {
        d->button->setVisible(false);
        d->vis = true;
    }
    else if (d->vis && !isReadOnly())
    {
        d->button->setVisible(!text().isEmpty());
        d->vis = false;
    }
    HButtonLineEdit::paintEvent(e);
}

void HClearLineEdit::init()
{
    setButtonPosition(Position_None);
    setIcon(QIcon(":/image/ww/closetab.png"));
    setAutoRaise(true);
    setButtonFocusPolicy(Qt::NoFocus);
    connect(this, &HClearLineEdit::buttonClicked, this, [=] { if (!isReadOnly()) clear(); });
    connect(this, &HClearLineEdit::textChanged, this, [=](const QString &value) { setButtonPosition(value.isEmpty() ? Position_None : Position_RightInside); });
}

HE_CONTROL_END_NAMESPACE
