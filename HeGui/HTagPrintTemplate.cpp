#include "HTagPrintTemplate_p.h"
#include <QtGui/QPainter>
#include <QtPrintSupport/QPrinter>

HE_BEGIN_NAMESPACE

HTagPrintTemplatePrivate::HTagPrintTemplatePrivate()
{
    prefix = "TagPrintTemplate";
}

HTagPrintTemplate::HTagPrintTemplate(QObject *parent) :
    HAbstractPrintTemplate(*new HTagPrintTemplatePrivate, parent)
{
    init();
}

HTagPrintTemplate::HTagPrintTemplate(HTagPrintTemplatePrivate &p, QObject *parent) :
    HAbstractPrintTemplate(p, parent)
{
}

HTagPrintTemplate::~HTagPrintTemplate() = default;

QString HTagPrintTemplate::typeName()
{
    return "HTagPrintTemplate";
}

bool HTagPrintTemplate::printPages(QPrinter *printer)
{
    Q_D(HTagPrintTemplate);

    auto margins = d->params.value("PageMargins").toRect();
    printer->setPageSizeMM(d->params.value("PageSize").toSize());
    printer->setPageMargins(margins.left(), margins.top(), margins.right(), margins.bottom(), QPrinter::Millimeter);

    QPainter painter(printer);
    int i;
    QVector<double> x,y;
    auto gap = 4.0;
    auto pen = QPen(Qt::black, 1);
    auto rect = painter.viewport();
    for (i = 0; i <= 2; i++)
        x.append(rect.left() + i * rect.width() / 2.0);
    for (i = 0; i <= 9; i++)
        y.append(rect.top() + i * rect.height() / 9.0);

    painter.setFont(QFont("宋体", 8));
    painter.setPen(pen);
    painter.drawRoundedRect(rect, 4, 4);
    for (i = 3; i <= 8; i++)
        painter.drawLine(x[0], y[i], x[2], y[i]);
    painter.drawLine(x[1], y[3], x[1], y[9]);
    drawText(&painter, x[0] + gap, y[0], x[2] - gap, y[1], tr("测试时间:%1").arg(toString("[测量日期时间]")));
    drawText(&painter, x[0] + gap, y[1], x[2] - gap, y[2], tr("产品型号:%1 产品编号:%2").arg(toString("[产品型号]"), toString("[样品编号]")));
    drawText(&painter, x[0] + gap, y[2], x[2] - gap, y[3], tr("设备型号:SL2000"));
    drawText(&painter, x[0] + gap, y[3], x[1] - gap, y[4], tr("BIN:%1").arg(toString("[分级]")));
    drawText(&painter, x[0] + gap, y[4], x[1] - gap, y[5], tr("CIEX:%1").arg(toString("[色坐标x]")));
    drawText(&painter, x[0] + gap, y[5], x[1] - gap, y[6], tr("VF:%1V").arg(toString("[实测电压]")));
    drawText(&painter, x[0] + gap, y[6], x[1] - gap, y[7], tr("IR:%1uA").arg(toString("[反向漏流]")));
    drawText(&painter, x[0] + gap, y[7], x[1] - gap, y[8], tr("Φe:%1mW").arg(toString("[光功率]")));
    drawText(&painter, x[0] + gap, y[8], x[1] - gap, y[9], tr("P:%1W").arg(toString("[电功率]")));
    drawText(&painter, x[1] + gap, y[3], x[2] - gap, y[4], tr("Tc:%1K").arg(toString("[色温]")));
    drawText(&painter, x[1] + gap, y[4], x[2] - gap, y[5], tr("CIEY:%1").arg(toString("[色坐标y]")));
    drawText(&painter, x[1] + gap, y[5], x[2] - gap, y[6], tr("IF:%1mA").arg(toString("[实测电流]")));
    drawText(&painter, x[1] + gap, y[6], x[2] - gap, y[7], tr("Φ:%1lm").arg(toString("[光通量]")));
    drawText(&painter, x[1] + gap, y[7], x[2] - gap, y[8], tr("Ra:%1").arg(toString("[显色指数Ra]")));
    drawText(&painter, x[1] + gap, y[8], x[2] - gap, y[9], tr("R9:%1").arg(toString("[显色指数R9]")));
    return true;
}

void HTagPrintTemplate::drawText(QPainter *painter, double x1, double y1, double x2, double y2, QString text)
{
    painter->drawText(QRectF(QPointF(x1, y1), QPointF(x2, y2)), Qt::AlignLeft | Qt::AlignVCenter, text);
}

void HTagPrintTemplate::init()
{
    Q_D(HTagPrintTemplate);
    d->types = QStringList() << "[测量日期时间]" << "[产品型号]" << "[样品编号]" << "[分级]"
                             << "[色坐标x]" << "[色坐标y]" << "[色温]" << "[光通量]" << "[光功率]" << "[显色指数Ra]" << "[显色指数R9]"
                             << "[实测电压]" << "[实测电流]" << "[电功率]" << "[反向漏流]";
    d->params.insert("PageSize",        QSize(50, 50));
    d->params.insert("PageMargins",     QRect(2, 2, 2, 2));
}

HE_END_NAMESPACE
