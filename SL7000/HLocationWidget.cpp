#include "HLocationWidget_p.h"
#include "HeCore/HCore.h"
#include "HeCore/HAppContext.h"
#include "HePlugin/HProgressBar.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>

HLocationWidgetPrivate::HLocationWidgetPrivate()
{
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
}

HLocationWidget::HLocationWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HLocationWidgetPrivate)
{
    init();
}

HLocationWidget::~HLocationWidget()
{
}

void HLocationWidget::setPolygon(const QPolygon &value)
{
    if (d_ptr->polygon == value)
        return;
    d_ptr->polygon = value;
    resetLayout();
}

void HLocationWidget::setColor(const QColor &invalid, const QColor &spacer)
{
    if (d_ptr->colorInvalid != invalid)
    {
        d_ptr->colorInvalid = invalid;
        for (auto label : d_ptr->labelTests)
            label->setStyleSheet(d_ptr->css.arg(d_ptr->colorInvalid.name()));
    }
    if (d_ptr->colorSpacer != spacer)
    {
        d_ptr->colorSpacer = spacer;
        for (auto label : d_ptr->labelSpacers)
            label->setStyleSheet(d_ptr->css.arg(d_ptr->colorSpacer.name()));
    }
}

void HLocationWidget::clearResult()
{
    for (auto label : d_ptr->labelTests)
    {
        label->setStyleSheet(d_ptr->css.arg(d_ptr->colorInvalid.name()));
        label->setToolTip("");
    }
}

void HLocationWidget::refreshResult()
{
    auto point = d_ptr->testData->data("[电机定位]").toPoint();
    auto color = d_ptr->testData->data("[品质颜色]").value<QColor>();
    auto label = d_ptr->labelTests.value(point);
    if (label != nullptr)
        label->setStyleSheet(d_ptr->css.arg(color.name()));
    d_ptr->progressBar->setValue(d_ptr->testData->data("[光谱采样比率]").toDouble());
}

void HLocationWidget::init()
{
    d_ptr->css = QString("background-color: %1;\nborder: 2px solid rgb(0, 0, 0);");
    d_ptr->colorSpacer = Qt::transparent;
    d_ptr->colorInvalid = Qt::blue;
    d_ptr->labelError = new QLabel;
    d_ptr->labelError->setAlignment(Qt::AlignCenter);
    d_ptr->labelError->setText(tr("请先配置布局！"));
    d_ptr->progressBar = new HProgressBar;
    d_ptr->progressBar->setOrientation(Qt::Vertical);
    d_ptr->progressBar->setRange(0, 100);
    d_ptr->progressBar->setValue(0);
    d_ptr->progressBar->setToolTip(HCore::toCaption("[光谱采样比率]"));
    d_ptr->layout = new QGridLayout;
    d_ptr->layout->setSpacing(9);
    d_ptr->layout->addWidget(d_ptr->labelError);
    auto layout = new QGridLayout(this);
    layout->addWidget(d_ptr->progressBar, 0, 0);
    layout->addLayout(d_ptr->layout, 0, 1);
    layout->setSpacing(9);
}

void HLocationWidget::resetLayout()
{
    d_ptr->layout->removeWidget(d_ptr->labelError);
    for (auto label : d_ptr->labelTests)
        d_ptr->layout->removeWidget(label);
    for (auto label : d_ptr->labelSpacers)
        d_ptr->layout->removeWidget(label);
    qDeleteAll(d_ptr->labelTests);
    qDeleteAll(d_ptr->labelSpacers);
    d_ptr->labelTests.clear();
    d_ptr->labelSpacers.clear();

    auto rect = d_ptr->polygon.boundingRect();
    if (rect.isEmpty())
    {
        d_ptr->layout->addWidget(d_ptr->labelError);
        return;
    }

    for (int row = rect.top(); row <= rect.bottom(); row++)
    {
        for (int column = rect.left(); column <= rect.bottom(); column++)
        {
            auto point = QPoint(row, column);
            auto label = new QLabel;
            label->setFrameShape(QFrame::Panel);
            label->setAlignment(Qt::AlignCenter);
            label->setText(QString("%1:%2").arg(row).arg(column));
            d_ptr->layout->addWidget(label, row, column);
            if (d_ptr->polygon.contains(point))
            {
                label->setStyleSheet(d_ptr->css.arg(d_ptr->colorInvalid.name()));
                d_ptr->labelTests.insert(point, label);
            }
            else
            {
                label->setStyleSheet(d_ptr->css.arg(d_ptr->colorSpacer.name()));
                d_ptr->labelSpacers.insert(point, label);
            }
        }
    }
}
