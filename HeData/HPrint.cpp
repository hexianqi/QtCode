#include "HPrint_p.h"
#include "IPrintTemplate.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtGui/QScreen>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>

HE_BEGIN_NAMESPACE

HPrint::HPrint(QObject *parent) :
    QObject(parent),
    d_ptr(new HPrintPrivate)
{
}

HPrint::HPrint(HPrintPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HPrint::~HPrint() = default;

void HPrint::initialize(QVariantMap /*param*/)
{

}

QString HPrint::typeName()
{
    return "HPrint";
}

IPrintTemplate *HPrint::printTemplate()
{
    return d_ptr->printTemplate;
}

void HPrint::setPrintTemplate(IPrintTemplate *p)
{
    if (d_ptr->printTemplate == p)
        return;
    d_ptr->printTemplate = p;
}

bool HPrint::print()
{
    if (!isValid())
        return false;

    QPrinter printer;
    QPrintDialog dialog(&printer);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    return printPages(&printer);
}

bool HPrint::printPreview()
{
    if (!isValid())
        return false;

    QPrinter printer;
    auto size = QApplication::primaryScreen()->availableSize();
    size.rwidth() /= 2;
    QPrintPreviewDialog dialog(&printer, nullptr, Qt::Dialog | Qt::WindowTitleHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    connect(&dialog, &QPrintPreviewDialog::paintRequested, this, &HPrint::printPages);
    dialog.resize(size);
    dialog.exec();
    return true;
}

bool HPrint::printPdf()
{
    if (!isValid())
        return false;

    auto fileName = QFileDialog::getSaveFileName(nullptr, QString(), ".", tr("PDF files (*.pdf)"));
    if (fileName.isEmpty())
        return false;

    QPrinter printer;
    printer.setOutputFileName(fileName);
    printer.setOutputFormat(QPrinter::PdfFormat);
    return printPages(&printer);
}

bool HPrint::isValid()
{
    return d_ptr->printTemplate != nullptr;
}

bool HPrint::printPages(QPrinter *p)
{
    return d_ptr->printTemplate->printPages(p);
}

HE_END_NAMESPACE
