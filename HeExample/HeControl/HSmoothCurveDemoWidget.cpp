#include "HSmoothCurveDemoWidget_p.h"
#include "ui_HSmoothCurveDemoWidget.h"
#include "HDrawHelper.h"
#include <QtCore/QDateTime>
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HSmoothCurveDemoWidgetPrivate::HSmoothCurveDemoWidgetPrivate()
{
    srand(QDateTime::currentDateTime().toMSecsSinceEpoch());

    int x = -300;
    while (x < 300)
    {
        datas << QPointF(x, rand() % 300 - 100);
        x += qMin(rand() % 30 + 5, 300);
    }

    pathNormal.moveTo(datas.at(0));
    for (int i = 1; i < datas.size(); i++)
        pathNormal.lineTo(datas.at(i));
    pathSmooth1 = HDrawHelper::createSmoothCurve(datas);
    pathSmooth2 = HDrawHelper::createSmoothCurve2(datas);
}

HSmoothCurveDemoWidget::HSmoothCurveDemoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HSmoothCurveDemoWidget),
    d_ptr(new HSmoothCurveDemoWidgetPrivate)
{
    ui->setupUi(this);
    ui->checkBox->setChecked(true);
    connect(ui->checkBox, &QCheckBox::clicked, this, &HSmoothCurveDemoWidget::updateCurve);
    connect(ui->radioButton_1, &QRadioButton::clicked, this, &HSmoothCurveDemoWidget::updateCurve);
    connect(ui->radioButton_2, &QRadioButton::clicked, this, &HSmoothCurveDemoWidget::updateCurve);
    connect(ui->radioButton_3, &QRadioButton::clicked, this, &HSmoothCurveDemoWidget::updateCurve);
}

HSmoothCurveDemoWidget::~HSmoothCurveDemoWidget()
{
    delete ui;
}

void HSmoothCurveDemoWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(1, -1);

    // 画坐标轴
    painter.setPen(QColor(180, 180, 180));
    painter.drawLine(-250, 0, 250, 0);
    painter.drawLine(0, 150, 0, -150);

    // 根据选择绘制不同的曲线路径
    painter.setPen(QPen(QColor(80, 80, 80), 2));
    if (ui->radioButton_2->isChecked())
        painter.drawPath(d_ptr->pathSmooth1);
    else if (ui->radioButton_3->isChecked())
        painter.drawPath(d_ptr->pathSmooth2);
    else
        painter.drawPath(d_ptr->pathNormal);

    // 如果曲线上的点可见则显示出来
    if (ui->checkBox->isChecked())
    {
        painter.setPen(Qt::black);
        painter.setBrush(Qt::gray);
        for (auto point : d_ptr->datas)
            painter.drawEllipse(point, 3, 3);
    }
}

void HSmoothCurveDemoWidget::updateCurve()
{
    update();
}

HE_END_NAMESPACE
