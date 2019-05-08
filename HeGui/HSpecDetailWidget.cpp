#include "HSpecDetailWidget_p.h"
#include "ui_HSpecDetailWidget.h"
#include "HeData/ITestData.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecDetailWidget::HSpecDetailWidget(QWidget *parent) :
    HAbstractTestDetailWidget(*new HSpecDetailWidgetPrivate, parent),
    ui(new Ui::HSpecDetailWidget)
{
    ui->setupUi(this);
    refreshWidget();
    setWindowTitle(tr("光谱数据"));
}

HSpecDetailWidget::~HSpecDetailWidget()
{
    qDebug() << __func__;
    delete ui;
}

void HSpecDetailWidget::initialize(QVariantMap /*param*/)
{

}

QString HSpecDetailWidget::typeName()
{
    return "HDetailWidgetSpec";
}

void HSpecDetailWidget::refreshWidget()
{
    Q_D(HSpecDetailWidget);

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

HE_GUI_END_NAMESPACE
