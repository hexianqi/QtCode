#include "HDetailWidgetSpec_p.h"
#include "ui_HDetailWidgetSpec.h"
#include "HeController/ITestData.h"

HDetailWidgetSpec::HDetailWidgetSpec(QWidget *parent) :
    HAbstractDetailWidget(*new HDetailWidgetSpecPrivate, parent),
    ui(new Ui::HDetailWidgetSpec)
{
    ui->setupUi(this);
    refreshWidget();
}

HDetailWidgetSpec::~HDetailWidgetSpec()
{
    delete ui;
}

QString HDetailWidgetSpec::typeName()
{
    return "HDetailWidgetSpec";
}

void HDetailWidgetSpec::refreshWidget()
{
    Q_D(HDetailWidgetSpec);

    QString text;
    ui->lineEdit_001->setText(d->testData->toString(("[峰值波长]")));
    ui->lineEdit_002->setText(d->testData->toString(("[主波长]")));
    ui->lineEdit_003->setText(d->testData->toString(("[色温]")));
    ui->lineEdit_004->setText(d->testData->toString(("[色坐标]")));
    ui->lineEdit_005->setText(d->testData->toString(("[显色指数]")));
    auto rx = d->testData->toString("[显色指数Rx]");
    if (!rx.isEmpty())
    {
        auto list = rx.split(QRegExp("\\s+"));
        for (int i = 0; i < list.size(); i++)
            text += QString("<body><center> R%1 = %2 </center></body>").arg(i+1, 2, 10, QChar('0')).arg(list[i]);
        ui->textBrowser->setText(text);
    }
}
