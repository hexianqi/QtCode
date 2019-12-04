#include "HAbstractSqlPrint_p.h"
#include "ISqlTableModel.h"
#include "HSql.h"
#include "HSqlPainterHelper.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include "HeData/IExcelStream.h"
#include <QtCore/QPointF>
#include <QtCore/QDateTime>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QApplication>
#include <QtGui/QScreen>
#include <QtGui/QPainter>
#include <QtSql/QSqlRecord>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>

HE_SQL_BEGIN_NAMESPACE

HAbstractSqlPrintPrivate::HAbstractSqlPrintPrivate()
{
    excelStream = HAppContext::getContextPointer<IDataFactory>("IDataFactory")->createExcelStream("HExcelStream");
}

HAbstractSqlPrint::HAbstractSqlPrint(QObject *parent) :
    ISqlPrint(parent),
    d_ptr(new HAbstractSqlPrintPrivate)
{
}

HAbstractSqlPrint::HAbstractSqlPrint(HAbstractSqlPrintPrivate &p, QObject *parent) :
    ISqlPrint(parent),
    d_ptr(&p)
{
}

HAbstractSqlPrint::~HAbstractSqlPrint()
{
}

void HAbstractSqlPrint::setModel(ISqlTableModel *p)
{
    if (d_ptr->model == p)
        return;
    d_ptr->model = p;
}

void HAbstractSqlPrint::setFieldExportExcel(QStringList value)
{
    if (d_ptr->fieldExportExcels == value)
        return;
    d_ptr->fieldExportExcels = value;
}

void HAbstractSqlPrint::exportExcel()
{
    if (!isValid())
        return;
    d_ptr->excelStream->setWriteContent(textForExcel());
    d_ptr->excelStream->saveAsFile();
}

void HAbstractSqlPrint::exportExcel(int index, int count)
{
    if (!d_ptr->model->isValid(index))
        return;

    auto max = d_ptr->model->rowCount() - index;
    count = count == -1 ? max : qBound(0, count, max);
    d_ptr->excelStream->setWriteContent(textForExcel(index, count));
    d_ptr->excelStream->saveAsFile();
}

void HAbstractSqlPrint::exportPdf()
{
    if (!isValid())
        return;

    QString fileName;
    fileName = QFileDialog::getSaveFileName(nullptr, QString(), ".", tr("PDF files (*.pdf)"));
    if (fileName.isEmpty())
        return;

    QPrinter printer;
    printer.setOutputFileName(fileName);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printPages(&printer);
}

void HAbstractSqlPrint::print()
{
    if (!isValid())
        return;

    QPrinter printer;
    QPrintDialog dialog(&printer);
    if (dialog.exec())
        printPages(&printer);
}

void HAbstractSqlPrint::printPreview()
{
    if (!isValid())
        return;

    QPrinter printer;
    auto size = QApplication::primaryScreen()->availableSize();
    size.rwidth() /= 2;
    QPrintPreviewDialog dialog(&printer, nullptr, Qt::Dialog | Qt::WindowTitleHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    connect(&dialog, &QPrintPreviewDialog::paintRequested, this, &HAbstractSqlPrint::printPages);
    dialog.resize(size);
    dialog.exec();
}

bool HAbstractSqlPrint::isValid()
{
    return d_ptr->model->isValid(d_ptr->model->currentRow());
}

QVariant HAbstractSqlPrint::recordValue(QString field, int index)
{
    if (index < 0)
        index = d_ptr->model->currentRow();

    auto r = d_ptr->model->record(index);
    if (r.contains(field))
        return r.value(field);
    if (field == "TestDateTime")
        return QDateTime(r.value("TestDate").toDate(), r.value("TestTime").toTime());
    if (field == "Date")
        return r.value("TestDateTime").toDateTime().date();
    if (field == "Time")
        return r.value("TestDateTime").toDateTime().time();
    if (field == "CC_xy")
        return QPointF(r.value("CC_x").toDouble(), r.value("CC_y").toDouble());
    if (field == "CC_uv")
        return QPointF(r.value("CC_u").toDouble(), r.value("CC_v").toDouble());
    if (field == "CC_uvp")
        return QPointF(r.value("CC_up").toDouble(), r.value("CC_vp").toDouble());
    return QVariant();
}

QString HAbstractSqlPrint::toString(QString field, int index)
{
    return HSql::toString(field, recordValue(field, index));
}

QString HAbstractSqlPrint::toWhole(QString field, int index)
{
    return HSql::toCaption(field) + ": " + toString(field, index) + " " + HSql::toUnit(field);
}

QPolygonF HAbstractSqlPrint::toPolygonF(QString field, int index)
{
    QPolygonF poly;
    auto list = recordValue(field, index).toString().split(",", QString::SkipEmptyParts);
    if (list.isEmpty())
        return poly;
    for (auto t : list)
    {
        auto l = t.split(":", QString::SkipEmptyParts);
        if (l.size() < 2)
            continue;
        poly << QPointF(l[0].toDouble(), l[1].toDouble());
    }
    return poly;
}

QString HAbstractSqlPrint::textForExcel(int index, int count)
{
    auto text = HSql::toCaptionUnit(d_ptr->fieldExportExcels).join("\t") + "\n";
    for (int i = 0; i < count; i++)
    {
        QStringList list;
        for (auto f : d_ptr->fieldExportExcels)
            list << toString(f, index + i);
        text += list.join("\t") + "\n";
    }
    return text;
}

void HAbstractSqlPrint::printPages(QPrinter *printer)
{
    printer->setPageMargins(13, 13, 5, 5, QPrinter::Millimeter);
    QPainter painter(printer);
    for (int i = 0; i < pageCount(); i++)
    {
        paintPage(&painter, i);
        if (i + 1 < pageCount())
            printer->newPage();
    }
}

double HAbstractSqlPrint::paintHeader(QPainter *painter, QString text)
{
    painter->setFont(QFont("宋体", 12));
    HSqlPainterHelper::drawText(painter, 20, 0, text);
    painter->drawLine(0, 25, painter->viewport().width(), 25);
    return 40;
}

double HAbstractSqlPrint::paintFooter(QPainter *painter, QString text)
{
    painter->setFont(QFont(tr("宋体"), 8));
    auto y = painter->viewport().height() - painter->fontMetrics().lineSpacing() - 10;
    painter->drawLine(0, y, painter->viewport().width(), y);
    HSqlPainterHelper::drawText(painter, 0, y, text, Qt::AlignCenter);
    return y - 5;
}

double HAbstractSqlPrint::paintTitle(QPainter *painter, QString text, double y)
{
    painter->setFont(QFont(tr("宋体"), 16, QFont::Bold));
    return HSqlPainterHelper::drawText(painter, 0, y, text, Qt::AlignHCenter | Qt::TextWordWrap).y() + 10;
}

HE_SQL_END_NAMESPACE
