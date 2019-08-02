#include "HButtonLineEdit_p.h"
#include <QtGui/QActionEvent>
#include <QtGui/QRegExpValidator>
#include <QtWidgets/QToolButton>

HE_CONTROL_BEGIN_NAMESPACE

HButtonLineEdit::HButtonLineEdit(QWidget *parent) :
    QLineEdit(parent),
    d_ptr(new HButtonLineEditPrivate)
{
    init();
}

HButtonLineEdit::HButtonLineEdit(HButtonLineEditPrivate &p, QWidget *parent) :
    QLineEdit(parent),
    d_ptr(&p)
{
    init();
}

HButtonLineEdit::~HButtonLineEdit()
{
}

QIcon HButtonLineEdit::icon() const
{
    return d_ptr->button ? d_ptr->button->icon() : QIcon();
}

bool HButtonLineEdit::isAutoRaise() const
{
    return d_ptr->button->autoRaise();
}

HButtonLineEdit::Position HButtonLineEdit::buttonPosition() const
{
    return d_ptr->position;
}

bool HButtonLineEdit::isButtonVisible() const
{
    return d_ptr->visible;
}

QString HButtonLineEdit::regularExpression() const
{
    auto v = qobject_cast<const QRegExpValidator *>(validator());
    if (!v)
        return ".*";
    return v->regExp().pattern();
}

Qt::FocusPolicy HButtonLineEdit::buttonFocusPolicy() const
{
    return d_ptr->button->focusPolicy();
}

void HButtonLineEdit::setIcon(QIcon value)
{
    d_ptr->button->setIcon(value);
}

void HButtonLineEdit::setAutoRaise(bool b)
{
    d_ptr->button->setAutoRaise(b);
}

void HButtonLineEdit::setButtonPosition(Position value)
{
    if (d_ptr->position == value)
        return;
    d_ptr->position = value;

    auto w = qMin(d_ptr->button->sizeHint().width(), testAttribute(Qt::WA_Resized) ? height() : sizeHint().height());
    switch (value)
    {
    case None:
        setTextMargins(0, 0, 0, 0);
        setContentsMargins(0, 0, 0, 0);
        break;
    case RightOutside:
        setTextMargins(0, 0, 0, 0);
        setContentsMargins(0, 0, w + 2, 0);
        break;
    case RightInside:
        setContentsMargins(0, 0, 0, 0);
        setTextMargins(0, 0, w, 0);
        break;
    case LeftOutside:
        setTextMargins(0, 0, 0, 0);
        setContentsMargins(w + 2, 0, 0, 0);
        break;
    case LeftInside:
        setContentsMargins(0, 0, 0, 0);
        setTextMargins(w, 0, 0, 0);
        break;
    }
    updateButtonPosition(w);
    update();
}

void HButtonLineEdit::setButtonVisible(bool b)
{
    d_ptr->visible = b;
    d_ptr->button->setVisible(b && d_ptr->position != None);
}

void HButtonLineEdit::setRegularExpression(const QString &value)
{
    setRegularExpression(QRegularExpression(value));
}

void HButtonLineEdit::setRegularExpression(const QRegularExpression &value)
{
    auto v = qobject_cast<QRegularExpressionValidator *>(const_cast<QValidator *>(validator()));
    if (v && v->regularExpression() == value)
        return;
    if (value.pattern() == ".*")
    {
        setValidator(nullptr);
        emit validatorChanged(".*");
        return;
    }
    if (v)
        v->setRegularExpression(value);
    else
        setValidator(new QRegularExpressionValidator(value, this));
    emit validatorChanged(value.pattern());
}

void HButtonLineEdit::setButtonFocusPolicy(Qt::FocusPolicy value)
{
    d_ptr->button->setFocusPolicy(value);
}

void HButtonLineEdit::resizeEvent(QResizeEvent *e)
{
    int w = qMin(d_ptr->button->sizeHint().width(), height());
    updateButtonPosition(w);
    QLineEdit::resizeEvent(e);
}

void HButtonLineEdit::actionEvent(QActionEvent *e)
{
    if (e->type() == QEvent::ActionAdded)
    {
        d_ptr->button->insertAction(e->before(), e->action());
        return;
    }
    if (e->type() == QEvent::ActionRemoved)
    {
        d_ptr->button->removeAction(e->action());
        return;
    }
    QLineEdit::actionEvent(e);
}

void HButtonLineEdit::updateButtonPosition(int w)
{
    if (d_ptr->position == None)
        d_ptr->button->hide();
    else if (d_ptr->visible)
        d_ptr->button->show();

    if(d_ptr->position == RightInside)
        d_ptr->button->setGeometry(rect().right() - w + 3, rect().top() + 2, w - 4, rect().height() - 4);
    else if (d_ptr->position == RightOutside)
        d_ptr->button->setGeometry(rect().right() - w + 1, rect().top(), w, rect().height());
    else if(d_ptr->position == LeftInside)
        d_ptr->button->setGeometry(rect().left() + 2, rect().top() + 2, w - 4, rect().height() - 4);
    else
        d_ptr->button->setGeometry(rect().left(), rect().top(), w, rect().height());
}

void HButtonLineEdit::init()
{
    d_ptr->button = new QToolButton(this);
    d_ptr->button->setText("...");
    d_ptr->button->setCursor(Qt::ArrowCursor);
    connect(d_ptr->button, &QToolButton::clicked, this, &HButtonLineEdit::buttonClicked);
    setButtonPosition(RightOutside);
}

HE_CONTROL_END_NAMESPACE
