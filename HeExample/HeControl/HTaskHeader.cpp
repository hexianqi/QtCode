#include "HTaskHeader_p.h"
#include <QtGui/QPainter>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QBoxLayout>

HE_CONTROL_BEGIN_NAMESPACE

HTaskHeader::HTaskHeader(QWidget *parent) :
    QFrame(parent),
    d_ptr(new HTaskHeaderPrivate)
{
    init();
}

HTaskHeader::HTaskHeader(HTaskHeaderPrivate &p, QWidget *parent) :
    QFrame(parent),
    d_ptr(&p)
{
    init();
}


HTaskHeader::~HTaskHeader()
{
}

QToolButton *HTaskHeader::toggleButton() const
{
    return d_ptr->button;
}

void HTaskHeader::setToggleIcon(const QIcon &value)
{
    d_ptr->button->setIcon(value);
    if (value.isNull())
        d_ptr->button->setArrowType(d_ptr->button->isChecked() ? Qt::UpArrow : Qt::DownArrow);
    else
        d_ptr->button->setArrowType(Qt::NoArrow);
}

void HTaskHeader::setName(const QString &value)
{
    d_ptr->label->setText(value);
    layout()->invalidate();
    update();
}

void HTaskHeader::setIcon(const QIcon &value)
{
    d_ptr->icon = value;
    if (value.isNull())
        d_ptr->spacer->changeSize(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    else
        d_ptr->spacer->changeSize(50, 16, QSizePolicy::Fixed, QSizePolicy::Fixed);
    d_ptr->spacer->invalidate();
    layout()->invalidate();
    update();
}

void HTaskHeader::paintEvent(QPaintEvent *e)
{
    QFrame::paintEvent(e);
    QPainter print(this);
    d_ptr->icon.paint(&print, QRect(6, (height() - 32) / 2 , 32, 32), Qt::AlignCenter,
                 isEnabled() ? QIcon::Normal : QIcon::Disabled,
                 toggleButton()->isChecked() ? QIcon::On : QIcon::Off);
}

void HTaskHeader::init()
{
    d_ptr->spacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    d_ptr->label = new QLabel;
    auto f = d_ptr->label->font();
    f.setBold(true);
    d_ptr->label->setFont(f);
    d_ptr->button = new QToolButton;
    d_ptr->button->setAutoRaise(true);
    d_ptr->button->setCheckable(true);
    d_ptr->button->setArrowType(Qt::DownArrow);
    auto l = new QHBoxLayout(this);
    l->addItem(d_ptr->spacer);
    l->addWidget(d_ptr->label);
    l->addWidget(d_ptr->button);
    setFrameShape(QFrame::StyledPanel);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
}

HE_CONTROL_END_NAMESPACE
