#include "HSpecDetailWidget_p.h"
#include "ui_HSpecDetailWidget.h"
#include "HeData/ITestData.h"

HE_BEGIN_NAMESPACE

HSpecDetailWidget::HSpecDetailWidget(QWidget *parent) :
    HAbstractTestDetailWidget(*new HSpecDetailWidgetPrivate, parent),
    ui(new Ui::HSpecDetailWidget)
{
    ui->setupUi(this);
    init();
    setWindowTitle(tr("光谱数据"));
}

HSpecDetailWidget::~HSpecDetailWidget()
{
    delete ui;
}

QString HSpecDetailWidget::typeName()
{
    return "HDetailWidgetSpec";
}

void HSpecDetailWidget::refreshWidget()
{
    Q_D(HSpecDetailWidget);
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

void HSpecDetailWidget::initHash()
{
    Q_D(HSpecDetailWidget);
    d->lineEdits.insert("[峰值波长]",   ui->lineEdit_001);
    d->lineEdits.insert("[主波长]",     ui->lineEdit_002);
    d->lineEdits.insert("[色温]",       ui->lineEdit_003);
    d->lineEdits.insert("[色坐标]",     ui->lineEdit_004);
    d->lineEdits.insert("[显色指数Ra]", ui->lineEdit_005);
}

HE_END_NAMESPACE
