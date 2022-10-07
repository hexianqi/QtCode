#include "HSpecCalibrateDetailWidget_p.h"
#include "ui_HSpecCalibrateDetailWidget.h"
#include "HeData/ITestData.h"

HE_BEGIN_NAMESPACE

HSpecCalibrateDetailWidget::HSpecCalibrateDetailWidget(QWidget *parent) :
    HAbstractTestDetailWidget(*new HSpecCalibrateDetailWidgetPrivate, parent),
    ui(new Ui::HSpecCalibrateDetailWidget)
{
    ui->setupUi(this);
    init();
    setWindowTitle(tr("光谱数据"));
}

HSpecCalibrateDetailWidget::~HSpecCalibrateDetailWidget()
{
    delete ui;
}

QString HSpecCalibrateDetailWidget::typeName()
{
    return "HDetailWidgetSpec";
}

void HSpecCalibrateDetailWidget::refreshWidget()
{
    Q_D(HSpecCalibrateDetailWidget);
    HAbstractTestDetailWidget::refreshWidget();
    auto rx = d->testData->toString("[显色指数Rx]");
    if (!rx.isEmpty())
    {
        QString text;
        auto list = rx.split(QRegExp("\\s+"));
        for (int i = 0; i < list.size(); i++)
            text += QString("<body><center> R%1 = %2 </center></body>").arg(i+1, 2, 10, QChar('0')).arg(list[i]);
        ui->textBrowser->setText(text);
    }
}

void HSpecCalibrateDetailWidget::initHash()
{
    Q_D(HSpecCalibrateDetailWidget);
    d->lineEdits.insert("[峰值波长]",   ui->lineEdit_001);
    d->lineEdits.insert("[主波长]",     ui->lineEdit_002);
    d->lineEdits.insert("[色温]",       ui->lineEdit_003);
    d->lineEdits.insert("[色坐标]",     ui->lineEdit_004);
    d->lineEdits.insert("[显色指数Ra]", ui->lineEdit_005);
    d->lineEdits.insert("[光谱光通量]", ui->lineEdit_006);
}

HE_END_NAMESPACE
