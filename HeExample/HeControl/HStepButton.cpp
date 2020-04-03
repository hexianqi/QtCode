#include "HStepButton_p.h"
#include "HStyleHelper.h"
#include <QtCore/QVariant>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>

HE_CONTROL_BEGIN_NAMESPACE

HStepButton::HStepButton(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HStepButtonPrivate)
{
    init();
}

HStepButton::HStepButton(HStepButtonPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HStepButton::~HStepButton()
{
}

void HStepButton::setButton(QStringList value)
{
    if (value.size() < 2)
        return;

    for (auto w : d_ptr->buttons)
        w->deleteLater();
    d_ptr->buttons.clear();

    for (auto step : value)
    {
        auto button = new QPushButton(step);
        button->setFlat(true);
        button->setProperty("class", "StepButton");
        button->setProperty("status", "middle");
        connect(button, &QPushButton::clicked, this, &HStepButton::updateStatus);
        d_ptr->buttons << button;
        d_ptr->layout->addWidget(button);
    }
    d_ptr->buttons.last()->setProperty("status", "last");
    d_ptr->buttons.first()->click();
}

// 按钮有 5 个状态: middle, last, active-middle, active-last, active-prev
void HStepButton::updateStatus()
{
    auto clickedButton = qobject_cast<QPushButton *>(sender());
    auto clickedIndex = d_ptr->buttons.indexOf(clickedButton);
    auto prevButton = d_ptr->buttons.value(clickedIndex - 1);
    auto isLast = clickedIndex == d_ptr->buttons.size() - 1;
    // 恢复所有按钮初始状态
    for (auto b : d_ptr->buttons)
        b->setProperty("status", "middle");
    d_ptr->buttons.last()->setProperty("status", "last");
    // 设置被点击的按钮的 status 属性为 active，如果是最后一个按钮则为 active-last
    clickedButton->setProperty("status", isLast ? "active-last" : "active-middle");
    // 设置被点击的按钮的前一个按钮的 status 为 active-prev
    if (prevButton)
        prevButton->setProperty("status", "active-prev");
    // 属性变化后，使属性选择器的 QSS 生效
    setStyleSheet(d_ptr->qss);
}

void HStepButton::init()
{
    d_ptr->qss = HStyleHelper::loadStyle(":/qss/stepButton.css");
    d_ptr->layout = new QHBoxLayout(this);
    d_ptr->layout->setSpacing(0);
    setStyleSheet(d_ptr->qss);
}

HE_CONTROL_END_NAMESPACE
