#include "HGradientProgressBar_p.h"
#include <QtWidgets/QStylePainter>
#include <QtWidgets/QStyleOptionProgressBar>

HE_BEGIN_NAMESPACE

HGradientProgressBar::HGradientProgressBar(QWidget *parent) :
    QProgressBar(parent),
    d_ptr(new HGradientProgressBarPrivate)
{
    setMinimumSize(180,150);
    setAlignment(Qt::AlignCenter);
}

HGradientProgressBar::~HGradientProgressBar()
{
}

void HGradientProgressBar::paintEvent(QPaintEvent *)
{
    QStylePainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QStyleOptionProgressBar option, option1, option2;

    initStyleOption(&option);

    option1 = option;
    option1.rect = style()->subElementRect(QStyle::SE_ProgressBarContents, &option1, this);
    QLinearGradient linearGradient(this->rect().topLeft(), this->rect().topRight());
    linearGradient.setColorAt(0.0, Qt::red);
    linearGradient.setColorAt(0.3, Qt::cyan);
    linearGradient.setColorAt(0.7, Qt::green);
    linearGradient.setColorAt(1.0, Qt::blue);

    painter.fillRect(option1.rect.left(), option1.rect.top(), option1.rect.width() * option1.progress / option1.maximum, option1.rect.height(), linearGradient);

    if (option.textVisible)
    {
        option2 = option;
        option2.rect = style()->subElementRect(QStyle::SE_ProgressBarLabel, &option2, this);
        painter.setPen(Qt::red);
        painter.drawControl(QStyle::CE_ProgressBarLabel, option2);
    }
}

HE_END_NAMESPACE

