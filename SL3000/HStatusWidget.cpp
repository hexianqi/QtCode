#include "HStatusWidget_p.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>

HStatusWidgetPrivate::HStatusWidgetPrivate()
{
    grey.load(":/image/circle_grey.png");
    green.load(":/image/circle_green.png");
    red.load(":/image/circle_red.png");
}

HStatusWidget::HStatusWidget(const QString &text, QVector<int> indexs, QWidget *parent) :
    QWidget(parent),
    d_ptr(new HStatusWidgetPrivate)
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(6, 0, 6, 1);
    auto label = new QLabel(text);
    label->setAlignment(Qt::AlignRight | Qt:: AlignVCenter);
    layout->addWidget(label);
    for (auto i : indexs)
    {
        auto lamp = new QLabel;
        lamp->setMaximumSize(24, 24);
        lamp->setScaledContents(true);
        lamp->setToolTip(QString::number(i+1));
        lamp->setPixmap(d_ptr->grey);
        layout->addWidget(lamp);
        d_ptr->lamps.insert(i, lamp);
    }
}

HStatusWidget::~HStatusWidget() = default;

void HStatusWidget::setStatus(int index, bool b)
{
    if (!d_ptr->lamps.contains(index))
        return;
    d_ptr->lamps.value(index)->setPixmap(b ? d_ptr->green : d_ptr->red);
}
