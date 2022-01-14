#include "HStandardPixmapWidget.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStyle>

HStandardPixmapWidget::HStandardPixmapWidget(QWidget *parent) : QWidget(parent)
{
    init();
}

HStandardPixmapWidget::~HStandardPixmapWidget() = default;

void HStandardPixmapWidget::init()
{
    auto layout = new QGridLayout(this);
    for (int i = 0; i < 71; i++)
    {
        auto pixmap = this->style()->standardPixmap(static_cast<QStyle::StandardPixmap>(i));
        auto label = new QLabel;
        label->setPixmap(pixmap);
        layout->addWidget(label, i / 7, i % 7);
    }
}
