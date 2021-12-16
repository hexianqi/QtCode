#include "HAbnormityButton_p.h"
#include "HStyleHelper.h"
#include <QtCore/QVariant>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>

HE_BEGIN_NAMESPACE

HAbnormityButton::HAbnormityButton(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HAbnormityButtonPrivate)
{
    init();
}

HAbnormityButton::HAbnormityButton(HAbnormityButtonPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HAbnormityButton::~HAbnormityButton() = default;

void HAbnormityButton::init()
{
    auto layout = new QGridLayout(this);
    auto topButton = new QPushButton;
    auto bottomButton = new QPushButton;
    auto leftButton = new QPushButton;
    auto rightButton = new QPushButton;
    auto centerButton = new QPushButton;
    topButton->setObjectName("topButton");
    bottomButton->setObjectName("bottomButton");
    leftButton->setObjectName("leftButton");
    rightButton->setObjectName("rightButton");
    centerButton->setObjectName("centerButton");
    layout->addWidget(topButton, 0, 1, Qt::AlignBottom | Qt::AlignHCenter);
    layout->addWidget(leftButton, 1, 0, Qt::AlignRight | Qt::AlignVCenter);
    layout->addWidget(centerButton, 1, 1, Qt::AlignCenter);
    layout->addWidget(rightButton, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);
    layout->addWidget(bottomButton, 2, 1, Qt::AlignTop | Qt::AlignHCenter);
    setStyleSheet(HStyleHelper::loadStyle(":/qss/abnormityButton.css"));
}

HE_END_NAMESPACE
