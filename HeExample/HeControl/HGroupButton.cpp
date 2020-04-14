#include "HGroupButton_p.h"
#include "HStyleHelper.h"
#include <QtCore/QVariant>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QPushButton>

HE_CONTROL_BEGIN_NAMESPACE

HGroupButton::HGroupButton(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HGroupButtonPrivate)
{
    init();
}

HGroupButton::HGroupButton(HGroupButtonPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HGroupButton::~HGroupButton() = default;

void HGroupButton::setButton(QStringList value)
{
    if (value.size() < 2)
        return;

    for (auto w : d_ptr->buttons)
        w->deleteLater();
    d_ptr->buttons.clear();

    for (const auto &step : value)
    {
        auto button = new QPushButton(step);
        button->setProperty("class", "GroupButton");
        button->setCheckable(true);
        d_ptr->buttons << button;
        d_ptr->buttonGroup->addButton(button);
        d_ptr->layout->addWidget(button);
    }
    d_ptr->buttons.first()->setProperty("position", "first");
    d_ptr->buttons.last()->setProperty("position", "last");
    d_ptr->buttons.first()->setChecked(true);
}

void HGroupButton::init()
{
    d_ptr->layout = new QHBoxLayout(this);
    d_ptr->layout->setSpacing(0);
    d_ptr->buttonGroup = new QButtonGroup(this);
    d_ptr->buttonGroup->setExclusive(true);
    setStyleSheet(HStyleHelper::loadStyle(":/qss/stepButton.css"));
}

HE_CONTROL_END_NAMESPACE
